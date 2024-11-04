#include "../inc/Response.hpp"

Response::Response()
{
}

Response::~Response()
{
}

void Response::setBody(std::string body)
{
    this->body = body;
}

void Response::setHeader(std::string key, std::string value)
{
    headers += key + ": " + value + "\r\n";
}

void Response::setStatusCode(int code)
{
    statusCode = code;
}

Response &Response::operator=(const Response &other)
{
    body = other.body;
    headers = other.headers;
    statusCode = other.statusCode;
    return *this;
}

std::string Response::getResponse()
{
    std::string response = "HTTP/1.1 " + std::to_string(statusCode) + "\r\n";
    response += headers;
    response += "\r\n";
    response += body;
    return response;
}