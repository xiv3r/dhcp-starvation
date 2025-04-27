# $${\color{orange}Installation}$$
- $${\color{cyan}dependencies}$$
```
sudo apt update
sudo apt install macchanger isc-dhcp-client bc -y
```
- $${\color{cyan}download}$$
```
wget -o dhcp https://raw.githubusercontent.com/xiv3r/dhcp-starvation/refs/heads/main/kali/dhcp && chmod 700 dhcp
```
- $${\color{cyan}run}$$
```
bash dhcp -i wlan0 -g 192.168.1.1 -s 192.168.1.1/24
```
<img src="https://github.com/xiv3r/dhcp-starvation/blob/main/kali/images/Screenshot_2025_0427_085922.png">

<img src="https://github.com/xiv3r/dhcp-starvation/blob/main/kali/images/Screenshot_2025_0427_085944.png">
