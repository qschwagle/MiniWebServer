#include "mini_web_server/listener.h"

Listener::Listener(const std::string& address, const std::int16_t port)
{
}

Listener::~Listener()
{
}

std::unique_ptr<Connection> Listener::Accept()
{
    return nullptr;
}
