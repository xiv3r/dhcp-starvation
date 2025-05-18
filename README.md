# $${\color{cyan}DHCP- Starvation- Tool}$$
dhcp starvation tool is a powerful tool that can starve all dhcp pool leading to all clients unable to obtain the ip from the dhcp server.

# $${\color{cyan}Requirements}$$
- g++/gcc compiler
- Termux

<details><summary></summary>
  
# $${\color{cyan}Screenshots}$$

-----
<img src="https://github.com/xiv3r/dhcp-starvation/blob/main/image/Screenshot_2025_0427_062659.png">

-----
<img src="https://github.com/xiv3r/dhcp-starvation/blob/main/image/Screenshot_2025_0427_062719.png">

-----
<img src="https://github.com/xiv3r/dhcp-starvation/blob/main/image/Screenshot_2025_0427_062743.png">
</img></details>

# $${\color{cyan}Installation}$$

- $${\color{magenta}install- package}$$
```
pkg update
pkg install wget git g++ gcc -y
```
- $${\color{magenta}clone- the- repo}$$
```
git clone https://github.com/xiv3r/dhcp-starvation.git
cd dhcp-starvation
```
- $${\color{magenta}compiling}$$
```
g++ starv.cpp -o starv
```
- $${\color{magenta}run}$$
> add interface "`./starv -i wlan0`"
```
./starv
```
</details>
