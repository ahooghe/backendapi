#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>

class Response
{
    public:
        Response();
        ~Response();
        
        void setBody(std::string body);
        void setHeader(std::string key, std::string value);
        void setStatusCode(int code);

        Response &operator=(const Response &other);

        std::string getResponse();



    private:
        std::string body;
        std::string headers;
        int statusCode;
};

#endif // RESPONSE_HPP