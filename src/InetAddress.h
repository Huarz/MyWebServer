#ifndef INETADDRESS
#define INETADDRESS
#include <arpa/inet.h>

class InetAddress
{
public:
    InetAddress();
    InetAddress(const char *ip, uint16_t port);
    ~InetAddress();
// todo 这里使用public是否太随意？
// private:
    struct sockaddr_in addr;
    //todo 这里面的addr_len是否太多余，声明为const好像也没有必要
    socklen_t addr_len;
};
#endif