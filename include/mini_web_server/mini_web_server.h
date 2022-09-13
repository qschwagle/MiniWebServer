#ifndef MINI_WEB_SERVER_MINI_WEB_SERVER_H
#define MINI_WEB_SERVER_MINI_WEB_SERVER_H 1

#include <string>
#include <cstdint>
#include <memory>
#include <unordered_map>

#include "mini_web_server/listener.h"
#include "mini_web_server/connection.h"

class MiniWebServer;

/**
 * A Builder of MiniWebServer
 *
 * Default address is loopback
 * Default port is 80
 */
class MiniWebServerBuilder
{
    public:

    /**
     * Constructor. Calls reset to initialize values
     */
    MiniWebServerBuilder() noexcept 
    {
        Reset();
    } 

    /**
     * Sets the value of the builder to default
     */
    void Reset() noexcept
    {
        mAddress = "127.0.0.1";
        mPort = 80;
    }

    /**
     * Set the builder address to be used later
     * \param address address for mini web server to listen on
     */
    void SetAddress(std::string address) noexcept { mAddress = address; }


    /**
     * set the port for web server to listen on
     * \param port port
     */
    void SetPort(std::int16_t port) noexcept { mPort = port; }

    /**
     * Set the directory path the server will be hosting
     * \param path path to directory
     */
    void SetDirectoryPath(std::string path) noexcept { mDirectoryPath = path; }

    const std::string& GetAddress() const noexcept { return mAddress; }
    const std::int16_t GetPort() const noexcept { return mPort; }
    const std::string& GetDirectoryPath() const noexcept { return mDirectoryPath; } 

    /**
     * Creates and instance of MiniWebServer based on current builder state
     * \returns a new MiniWebServer
     */
    std::unique_ptr<MiniWebServer> Make();

    private:
    /// default address loopback ( 127.0.0.1 )
    std::string mAddress;

    /// default port 80
    std::int16_t mPort;

    /// serving directory path
    std::string mDirectoryPath;
};

/**
 * Core Program class
 */
class MiniWebServer
{
public:
    /**
     * Configuration State for the MiniWebServer
     *
     */
    class ConfigState 
    {
        public:
            /** Get the Address 
             *  \returns address to listen on
             */
            const std::string& GetAddress() const noexcept { return mAddress; }

            /**
             * Get the port to listen on
             * \returns port to listen on
             */
            const std::int16_t GetPort() const noexcept { return mPort; }

            /**
             * Gets the directory path the server is hosting
             * \returns directory path
             */
            const std::string& GetDirectoryPath() const noexcept { return mDirectoryPath;  }

            /**
             * was this configuration state initilized?
             * \returns was this state initialized
             */
            bool WasInitialized() const noexcept { return mWasInitialized; }

        private:

        /// address to listen for ( default value is not valid )
        std::string mAddress{""};

        /// directory path
        std::string mDirectoryPath{""};

        /// port to listen on ( default value is not valid )
        short int mPort{0};

        /// was the config state properly initialized?
        bool mWasInitialized{false};

        friend MiniWebServerBuilder;
    };

    /**
     * Main Constructor for MiniWebServer.
     *
     * Initializes the object with the config state
     * \param config_state configuration state for the webserver
     */
    MiniWebServer(const ConfigState& config_state) : mConfigState(config_state)
    {
    }

    /**
     * initializes and runs the run loop for the server.
     * \returns the application exit code
     */
    int Run();

private:
    /**
     * Initializes the server, such as opening the listening socket.
     * \returns true on success. otherwise false
     */
    bool Init();

private:
    /// configuration state 
    ConfigState mConfigState;

    /// server listener
    std::unique_ptr<Listener> mListener{nullptr};

    /// active connections
    std::unordered_map<std::uint64_t, Connection> mConnections;
};

#endif
