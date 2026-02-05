#include "Acceptor.h"

#include "EventLoop.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Socket.h"

Acceptor::Acceptor(EventLoop *_loop) : loop(_loop)
{
    Socket *serv_sock = new Socket();
    InetAddress *serv_addr = new InetAddress("127.0.0.1", 8888);
    serv_sock->bind(serv_addr);
    serv_sock->listen();
    serv_sock->setnonblocking();

    Channel *servChannel = new Channel(loop, serv_sock->getFd());
    std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this);
    servChannel->setCallback(cb);
    servChannel->enableReading();
}
Acceptor::~Acceptor()
{
    delete sock;
    delete addr;
    delete acceptChannel;
}
void Acceptor::acceptConnection()
{
    newConnectionCallback(sock);
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket *)>_cb)
{
    newConnectionCallback = _cb;
}