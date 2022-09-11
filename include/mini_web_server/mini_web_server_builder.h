#ifndef MINI_WEB_SERVER_MINI_WEB_SERVER_BUILDER_H
#define MINI_WEB_SERVER_MINI_WEB_SERVER_BUILDER_H 1

#include <memory>

class MiniWebServer;

/**
 * A Builder of MiniWebServer
 */
class MiniWebServerBuilder
{
    public:
    /**
     * Creates and instance of MiniWebServer based on current builder state
     * \returns a new MiniWebServer
     */
    std::unique_ptr<MiniWebServer> Make();
};


#endif
