#ifndef TCP_SERVER_H
#define TCP_SERVER_H


#include<iostream>
#include<string>
#include<sys/socket.h>
#include<cstdlib>
#include<cstring>
#include<sys/unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAX_BUF 1024 // 一个buf的大小
#define LISTENQ 5 // 最多监听数量
#define SERV_PORT 1545 // 默认端口号
namespace TCP{

 class tcp_server{

       private:
        int listen_fd; // 监听的socket
        int connect_fd; // 连接的socket
        
        //通用网络地址结构
        sockaddr_in6 server_addr; // 服务端的addr ipv6
        sockaddr_in client_addr;//client:ipv4
        in_port_t _port; 
        in_addr_t _addr; 
      
        socklen_t addr_len; // 地址长度 :BSD套接字接口标准->accept用到的填充
        pid_t child_pid; // 子进程的pid
       
       public:
       
       //转化网络地址和端口
       tcp_server(std::string address, uint16_t port) {
            this->_port = htons(port);
            //to bind()
            server_addr.sin6_family = AF_INET6;
            server_addr.sin6_addr = in6addr_any;//ipv6 use any
            server_addr.sin6_port = this->_port;
            addr_len = sizeof(client_addr);
          //std::cout<<"port"<<port<std::endl;
        }
    
    int init(){
            std::cout << "Server process: " << getpid() << std::endl;
            // listen socket
            listen_fd = socket(AF_INET6, SOCK_STREAM, 0); // IPv6 byte TCP
            if (listen_fd < 0) {
                std::cerr << "Server: can not create listen socket" << std::endl;
                return -1;
            }
            // bind()
            if (bind(listen_fd, (sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
                std::cerr << "Server: can not bind socket" << std::endl;
                return -1;
            }
            // listen()
            if (listen(listen_fd, LISTENQ) < 0) { // listen socket(5)
                std::cerr << "Server: can not listen" << std::endl;
                return -1;
            }
            char addr[20];
            inet_ntop(AF_INET6, &server_addr.sin6_addr, addr, sizeof(addr));
            std::cout << "Server address: " << std::string(addr)
                      << " port: " << ntohs(server_addr.sin6_port) << std::endl;
            std::cout << "Server:server has started" << std::endl;
            while(1){
                std::cout << "Server is listening" << std::endl;
                
                // accept()
                connect_fd = accept(listen_fd, (sockaddr*) &client_addr, &addr_len);
                if (connect_fd > 0) {
                    std::cout << "Server connect:";
                    char addr[20];
                    inet_ntop(AF_INET, &client_addr.sin_addr, addr, sizeof(addr));
                    std::cout << " Client address: " << std::string(addr);
                    std::cout << " port: " << ntohs(client_addr.sin_port) << std::endl;

                    if ( (child_pid = fork()) == 0 ) { // child process
                        child_pid = getpid();
                        // close listen socket
                        close(listen_fd);
                        // send and receive
                        communicate(connect_fd);
                        exit(0);
                    }
                    // child process
                    std::cout << "Child process: " << child_pid << std::endl;
                    // close connect socket
                    close(connect_fd);
                } else {
                    std::cerr << "Server: accept error" << std::endl;
                }
            }
        std::cerr<<"some problems exits"<<std::endl;
        return 0;
    }
    private:
       void communicate(int sockfd) {
            getpeername(sockfd, (sockaddr*)&client_addr, &addr_len);
            char addr[20];
            size_t n;//frame n
            
            inet_ntop(AF_INET, &client_addr.sin_addr, addr, sizeof(addr));
            char buf[MAX_BUF];
            memset(buf, 0, sizeof(buf));

            while( (n = read(sockfd, buf, MAX_BUF)) > 0 ) {
                std::string message(buf);
                std::cout << "  Child process " << child_pid << " receive: " << message << std::endl;
                write(sockfd, buf, n);
                memset(buf, 0, sizeof(buf));
            }
            if (n == 0) {
                std::cout << "  Child process " << child_pid << ": client disconnect";
                std::cout << " address: " << std::string(addr);
                std::cout << " port: " << ntohs(client_addr.sin_port) << std::endl;
            } else if (n < 0)
                std::cerr << "read error" << std::endl;
        }
   
};
}
#endif //CP_SERVER_H