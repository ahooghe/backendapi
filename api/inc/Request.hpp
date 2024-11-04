#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <map>
#include <sstream>

#include "Config.hpp"

class Request
{
    public:
        Request(std::string request, Config config);
        ~Request();

        std::string getHeader(std::string key);
        std::string getJsonField(std::string field);
        std::string getMethod();
        std::string getPath();
        int getStatus();

    private:
        int status;
        std::map<std::string, std::string> _headers;
        std::map<std::string, std::string> _jsonfield;
        std::string method;
        std::string path;

        void parse(std::string request, Config config);

};

#endif // REQUEST_HPP
