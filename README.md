# IP_communication
IPv4和IPv6客户端和服务端互操作


## 网络环境


VMware Workstation Pro16
Ubuntu20.04

Client IP:

ipv4: 192.168.157.131

ipv6: fe80::a00c:cc2c:11ce:f779

Server IP:

Ipv4:192.168.157.130

Ipv6:fe80::20c:29ff:fe01:eaa1

Server Port:1253

wireshark(sudo)
## 过程

### 创建两台虚拟机
网络模式使用桥接模式

参考: [网络模式](https://blog.csdn.net/CleverCode/article/details/45934233)
### ipv4客户端向ipv6服务端socket通信

### ipv6客户端向ipv4服务端socket通信


### IPV4和IPV6客户端区别

IPV6 环境下客户端 Socket 编程与 IPV4 的区别主要在 socket 、connect 两个函数的使用上，其余的 read、write 等函数的使用都与 IPV4 一样。

socket() 的函数原型为 int socket(int domain, int type, int protocol)，两者的区别在第一个参数的使用上，IPV4 为 AF_INET，IPV6 为 AF_INET6。

connect() 的函数原型为 int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)，两者的区别在第二个和第三个的使用上，尤其是第二个参数的结构体，而该结构体参数则需要使用函数 getaddrinfo() 来获得，以实现兼容。

### 使用到的命令
if config 查看虚拟机ip地址

netstart  查看网络环境

ping 检查两台虚拟机的网络连接情况

手动配置ip地址：
sudo dhclient ens33(网卡设备）->获取ip

sudo ifconfig ens33 ->查看ip

