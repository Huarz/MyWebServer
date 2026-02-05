#include "Server.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <vector>
#include <unistd.h>
#include <functional>

#include "InetAddress.h"
#include "Socket.h"
#include "Epoll.h"
#include "util.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Connection.h"

#define READ_BUFFER 1024

Server::Server(EventLoop *eventLoop) : loop(eventLoop)
{
    acceptor=new Acceptor(eventLoop);
    std::function<void(Socket*)> cb=std::bind(&Server::newConnection,this,std::placeholders::_1);
    acceptor->setNewConnectionCallback(cb);
}
Server::~Server() {
    delete acceptor;
}

void Server::deleteConnection(Socket*sock){
    Connection*conn=connections[sock->getFd()];
    connections.erase(sock->getFd());
    delete conn;
    conn=nullptr;
}
void Server::newConnection(Socket *sock)
{
    Connection*conn=new Connection(loop,sock);
    std::function<void(Socket*)>cb=std::bind(&Server::deleteConnection,this,std::placeholders::_1);
    conn->setDeleteConnectionCallback(cb);
    connections[sock->getFd()]=conn;
    // InetAddress *clnt_addr = new InetAddress();
    // Socket *clnt_sock = new Socket(serv_sock->accept(clnt_addr));
    // printf("new client fd %d! TP: %s Port: %d\n", clnt_sock->getFd(), inet_ntoa((clnt_addr->addr).sin_addr), ntohs((clnt_addr->addr).sin_port));
    // clnt_sock->setnonblocking();
    // Channel *clntChannel = new Channel(loop, clnt_sock->getFd());
    // std::function<void()> cb = std::bind(&Server::handleReadEvent,this,clnt_sock->getFd());
    // clntChannel->setCallback(cb);
    // clntChannel->enableReading();
}