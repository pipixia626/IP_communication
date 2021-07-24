
#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include<arpa/inet.h>
#include<cstdlib>
#include<iostream>
#include<string>
#include<cstring>
#include<sys/socket.h>
#include<sys/unistd.h>
#include<netinet/in.h>

#define MAX_BUF 1024
namespace TCP{

    class tcp_client{

      private:
            int client_fd;//socket
            in_addr_t addr;//server address
            in_port_t port;//server 
            sockaddr_in server_addr; // server address struct
            sockaddr_in client_addr; // client address struct
      public:

        tcp_client(std::string address,uint16_t port){
            in_addr addr;
            //trans string's ipinto net:32bit ip
            inet_aton(address.c_str(), &addr);
            this->addr = addr.s_addr;
            this->port = htons(port);
            //std::cout<<"client"<<"   port   "<<port<<"   addr   "<<address<<std::endl;
        }
         //初始化
        int init(){
             //socket()
            client_fd=socket(AF_INET,SOCK_STREAM,0);

            if(client_fd<0){
                std::cerr<<"Client: socket falid"<<std::endl;
                return -1;
            }
            
             //配置服务端的地址
            server_addr.sin_family = AF_INET;
            server_addr.sin_addr.s_addr = this->addr;
            server_addr.sin_port = this->port;
             //connect()

             //连接失败
            if (connect(client_fd, (sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
                std::cerr << " client connect to server falied" << std::endl;
                return -1;
            }
             //连接成功    
            else {
                std::cout<<"connect successed"<<std::endl;
                 return 0;
            }    
        return -1;
        }
    

         //send()
         int send(std::string str)const{
            return write(client_fd,str.c_str(),str.size());
        }
         //receieve()
         std::string receive()const{
            char str[MAX_BUF];
            memset(str, 0, sizeof(str));
            if (read(client_fd, str, MAX_BUF) == -1) {
               
                std::cerr << "Client:reveive failed " << std::endl;
            }
            std::string message(str);
            return message;
        }
        //close()
        int close(){
            std::cout << "Client: disconnect" << std::endl;
            return ::close(client_fd);
        }
    
    };
}
#endif //TCP_CLIENT_H