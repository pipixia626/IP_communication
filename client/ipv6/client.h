
#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include<netdb.h> 
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
            addrinfo hints;//server address
            const char* clientname;
            const char*service;
            in_port_t port;//server 
            sockaddr_in server_addr; // server address struct
            sockaddr_in client_addr; // client address struct
      public:

        tcp_client(std::string address,uint16_t port){
            
            this->clientname=address.c_str();
            this->port = htons(port);
            this->service=std::to_string(port).c_str();
            //std::cout<<"client"<<"   port   "<<port<<"   addr   "<<address<<std::endl;
        }
         //初始化
        int init(){
             //socket()
            client_fd=socket(AF_INET6,SOCK_STREAM,0);
            
            if(client_fd<0){
                std::cerr<<"Client: socket falid"<<std::endl;
                return -1;
            }
            
            hints.ai_family=AF_INET6;
            hints.ai_flags=AI_V4MAPPED|AI_ALL;

            addrinfo*res;
            auto result=getaddrinfo(clientname,service,&hints,&res);
            if(res==nullptr||result!=0){
                std::cerr<<"get failed"<<std::endl;
            }

             //connect()

             //连接失败
            if (connect(client_fd,res->ai_addr,res->ai_addrlen)<0) {
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