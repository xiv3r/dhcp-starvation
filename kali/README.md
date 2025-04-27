# $${\color{orange}Installation}$$
> dependencies
```
sudo apt update
sudo apt install macchanger isc-dhcp-client bc -y
```
> download
```
wget -o dhcp && chmod 700 dhcp
```
> run
```
bash dhcp -i wlan0 -g 192.168.1.1 -s 192.168.1.1/24
```
