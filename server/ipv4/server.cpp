Server.cpp
#include "server.h"
// client:192.168.157.131
// client:fe80::a00c:cc2c:11ce:f779
// server:192.168.157.130
// server:fe80::20c:29ff:fe01:eaa1
int main(){

    TCP::tcp_server server("192.168.157.130",1253);
    int action=server.init();
    
    return 0;
}