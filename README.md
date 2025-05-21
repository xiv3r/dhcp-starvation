# $${\color{cyan}TERMUX- DHCP- Starvation- Tool}$$
A DHCP starvation tool is a powerful network attack tool that floods a DHCP server with fake DHCP requests, exhausting all available IP addresses in the DHCP pool. This prevents legitimate clients from obtaining an IP address, leading to network disruptions or a complete denial of service (DoS) for affected devices.

# $${\color{cyan}Requirements}$$
- g++/gcc compiler
- Termux

  
# $${\color{cyan}Screenshots}$$
<details><summary></summary>
  
-----
<img src="https://github.com/xiv3r/dhcp-starvation/blob/main/images/Screenshot_2025_0521_205230.png">

-----
<img src="https://github.com/xiv3r/dhcp-starvation/blob/main/images/Screenshot_2025_0521_205159.png">

</img></details>

# $${\color{cyan}Auto- Install}$$
```
pkg update && pkg install wget -y && wget -qO- https://raw.githubusercontent.com/xiv3r/dhcp-starvation/refs/heads/main/auto | bash && cd dhcp-starvation
```

# $${\color{cyan} Manual- Installation}$$

- $${\color{magenta}install- package}$$
```
pkg update
pkg install wget git clang -y
```
- $${\color{magenta}clone- the- repo}$$
```
git clone https://github.com/xiv3r/dhcp-starvation.git
cd dhcp-starvation
```
- $${\color{magenta}compiling}$$
```
g++ fuck.cpp -o fuck
```
- $${\color{magenta}run}$$
> add interface "`./fuck -i wlan0`"
```
./fuck
```
</details>
