#ifndef MINI_WEB_SERVER_CONNECTION_H
#define MINI_WEB_SERVER_CONNECTION_H 1

#include <iostream>
#include <cstdint>

class Connection
{
    public:
        Connection();

        ~Connection();

        /** not copyable */
        Connection(const Connection&)=delete;

        /** not copyable */
        Connection& operator=(const Connection&)=delete;

        /**
         * Reads bytes from buffer
         * \param buffer buffer to write
         * \param buffer buffer size
         * \returns number of bits read or a negative value for error
         */
        std::int64_t Read(char* buffer, size_t buffer_size);

        /**
         * tries to write the buffer to the connection.\
         * \param buffer buffer to write
         * \param buffer buffer size
         * \returns number of bytes written or a negative value for error
         */
        std::int64_t Write(char* buffer, size_t buffer_size);

    private:

        int mSocket; 
};

#endif
