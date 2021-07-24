#include"client.h"
// client:192.168.157.131
// client:fe80::a00c:cc2c:11ce:f779
// server:192.168.157.130
// server:fe80::20c:29ff:fe01:eaa1
int main() {
    
    
    TCP::tcp_client client("192.168.157.130",1253);
    //init()
    int action=client.init();
    if(action ==-1){
        std::cerr<<"init falied"<<std::endl;
    }
    else
    {
    while (1) {

        std::string message;
        std::cin>>message;  
        if(message=="q"){
            client.close();//close
            return 0;
        }
        //send()
        client.send(message);
        //receive()
        message = client.receive();
        std::cout << "Client receive: " << message << std::endl;
        }
    }
}