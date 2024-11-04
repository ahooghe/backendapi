#include "../inc/Router.hpp"

Router::Router() {}

Router::~Router() {}

void Router::addRoute(const std::string& method, const std::string& path, Handler handler)
{
    std::string key = method + ":" + path;
    routes[key] = handler;
}

Router::Handler Router::getHandler(const std::string& method, const std::string& path) const
{
    std::string key = method + ":" + path;
    auto it = routes.find(key);
    if (it != routes.end())
    {
        return it->second;
    }
    return Handler();
}