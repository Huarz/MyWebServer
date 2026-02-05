#include "EventLoop.h"

#include <vector>

#include "Channel.h"
#include "Epoll.h"

EventLoop::EventLoop():ep(new Epoll()),quit(false){}
EventLoop::~EventLoop(){
    delete ep;
    ep=nullptr;
}
void EventLoop::loop(){
    while(!quit){
        std::vector<Channel*> chs;
        for(auto it =chs.begin();it!=chs.end();++it){
            (*it)->handleEvent();
        }
    }
}
void EventLoop::updateChannel(Channel *ch){
    ep->updateChannel(ch);
}