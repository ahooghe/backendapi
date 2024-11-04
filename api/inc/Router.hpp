#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <string>
#include <map>
#include <functional>

#include "Handlers.hpp"
#include "Request.hpp"
#include "DataStore.hpp"

class Router
{
    public:
        using Handler = std::function<Response(const Request&, DataStore&)>;

        Router();
        ~Router();
        void addRoute(const std::string& method, const std::string& path, Handler handler);
        Handler getHandler(const std::string& method, const std::string& path) const;

    private:
        std::map<std::string, Handler> routes;
};

#endif // ROUTER_HPP