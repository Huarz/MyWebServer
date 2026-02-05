#include "Socket.h"

#include <fcntl.h>
#include <unistd.h>

#include "util.h"
#include "InetAddress.h"

Socket::Socket() : fd(socket(AF_INET, SOCK_STREAM, 0))
{
    errif(fd == -1, "socket create error");
}
Socket::Socket(int _fd) : fd(_fd)
{
    errif(fd == -1, "socket create error");
}
Socket::~Socket()
{
    close(fd);
}
void Socket::bind(InetAddress *addr)
{
    errif(::bind(fd, (sockaddr *)&addr->addr, addr->addr_len) == -1, "socket bind error");
}
void Socket::listen()
{
    errif(::listen(fd, SOMAXCONN) == -1, "socket listen error");
}
// void connect();
int Socket::accept(InetAddress *peerAddr)
{
    int clnt_sockfd = ::accept(fd, (sockaddr *)&peerAddr->addr, &peerAddr->addr_len);
    errif(clnt_sockfd == -1, "socket accept error");
    return clnt_sockfd;
}
void Socket::setnonblocking()
{
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}
int Socket::getFd()
{
    return fd;
}
