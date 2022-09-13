#ifndef MINI_WEB_SERVER_LISTENER_H
#define MINI_WEB_SERVER_LISTENER_H 1

#include <cstdint>
#include <string>
#include <memory>

#include "mini_web_server/connection.h"

/**
 * Listens on a socket
 */
class Listener
{
    public:
        /**
         * \param address to listen on
         * \param port to listen on
         */
        Listener(const std::string& address, const std::int16_t port);

        /**
         * closes the socket if needed
         */
        ~Listener();

        /** not copyable */
        Listener(const Listener&)=delete;

        /** not copyable */
        Listener& operator=(const Listener&)=delete;

        /**
         * Accepts an incoming connection
         * \returns the new connection or nullptr if no new connection
         */
        std::unique_ptr<Connection> Accept();
    private:
        /// socket being listened
        int mSocket{0};
};

#endif
