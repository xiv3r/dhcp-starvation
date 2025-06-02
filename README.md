# TERMUX DHCP Starvation Tool
A DHCP starvation tool is a powerful network attack tool that floods a DHCP server with fake DHCP requests, exhausting all available IP addresses in the DHCP pool. This prevents legitimate clients from obtaining an IP address, leading to network disruptions or a complete denial of service (DoS) for affected devices.

# Requirements
- g++ gcc clang compiler
- Termux App

# Screenshots
<details><summary></summary>
  
-----
<img src="https://github.com/xiv3r/dhcp-starvation/blob/main/images/Screenshot_2025_0521_205230.png">

-----
<img src="https://github.com/xiv3r/dhcp-starvation/blob/main/images/Screenshot_2025_0521_205159.png">

</img></details>

# Auto Install
```
pkg update && pkg install wget -y && wget -qO- https://raw.githubusercontent.com/xiv3r/dhcp-starvation/refs/heads/main/auto | bash && cd dhcp-starvation
```

# Manual Installation

- install package
```
pkg update
pkg install wget git clang -y
```
- clone the repo
```
git clone https://github.com/xiv3r/dhcp-starvation.git
cd dhcp-starvation
```
- compiling
```
g++ fuck.cpp -o fuck
```
- run
> add interface "`./fuck -i wlan0`"
```
./fuck
```

# Impact

Disconnect and Reconnect on gateway 192.168.1.1/24

`Connecting...`

`Obtaining IP...`

`No IP Allocation...`
</details>
