#include "Epoll.h"

#include<unistd.h>
#include <string.h>

#include "util.h"

#define MAX_EVNETS 1000

Epoll::Epoll():epfd(epoll_create1(0)),events(nullptr){
    errif(epfd==-1,"Epoll create error");
    events = new epoll_event[MAX_EVNETS];
    bzero(events,sizeof(*events)*MAX_EVNETS);
}

Epoll::~Epoll(){
    if(epfd!=-1){
        close(epfd);
        epfd=-1;
    }
    delete[]events;
    events=nullptr;
}

void Epoll::addFd(int fd,uint32_t opt){
    struct epoll_event ev;
    bzero(&ev,sizeof(ev));
    ev.data.fd=fd;
    ev.events=opt;
    errif(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev)==-1,"epoll add evnet error");
}

std::vector<epoll_event> Epoll::poll(int timeout){
    std::vector<epoll_event> activeEvents;
    int nfds =epoll_wait(epfd,events,MAX_EVNETS,timeout);
    errif(nfds==-1,"epoll wait error");
    for(int i=0;i<nfds;++i){
        activeEvents.push_back(events[i]);
    }
    return activeEvents;
}