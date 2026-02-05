#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>

class InetAddress;

class Socket
{
public:
    Socket();
    explicit Socket(int);
    Socket(const Socket&)=delete;
    Socket& operator=(const Socket&)=delete;
    ~Socket();

    void bind(InetAddress *);
    void listen();
    // void connect();
    int accept(InetAddress *);
    void setnonblocking();
    int getFd();

private:
    int fd;
};
#endif