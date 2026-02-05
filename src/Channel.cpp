#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop*_loop, int _fd) :loop(_loop), fd(_fd), events(0), revents(0) {}
Channel::~Channel() {}

void Channel::enableReading()
{
    events |= EPOLLIN | EPOLLET;
    loop->updateChannel(this);
}
void Channel::handleEvent() { callback(); }
int Channel::getFd() { return fd; }
uint32_t Channel::getEvents() { return events; }
uint32_t Channel::getRevents() { return revents; }
bool Channel::getInEpoll() { return inEpoll; }
void Channel::setInEpoll() { inEpoll = true; }
void Channel::setRevents(uint32_t ev) { revents = ev; }
void Channel::setCallback(std::function<void()> cb) { callback = cb; }