#ifndef MINI_WEB_SERVER_MINI_WEB_SERVER_H
#define MINI_WEB_SERVER_MINI_WEB_SERVER_H 1

/**
 * Core Program class
 */
class MiniWebServer
{
public:
    /**
     * Configuration State for the MiniWebServer
     */
    class ConfigState 
    {

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

private:
    /// configuration state 
    ConfigState mConfigState;

};

#endif
