#include "../inc/Request.hpp"

Request::Request(std::string request, Config config)
{
    parse(request, config);
}

Request::~Request()
{
}

void Request::parse(std::string request, Config config)
{
    std::istringstream stream(request);
    std::string line;

    std::getline(stream, line);
    std::istringstream requestLine(line);
    requestLine >> method >> path;

    while (std::getline(stream, line) && !line.empty()) {
        auto delimiterPos = line.find(':');
        if (delimiterPos == std::string::npos)
            break;
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        _headers[key] = value;
    }

    std::string body;
    while (std::getline(stream, line)) {
        body += line + "\n";
    }
    if (body.find('{') == std::string::npos || body.find('}') == std::string::npos)
    {
        status = 0;
        return;
    }
    body = body.substr(body.find_first_of('{') + 1);
    body = body.substr(0, body.find_last_of('}'));


    bool comma = false;
    for (int i = 0; i < body.length(); i++)
    {
        if (comma == true)
        {
            if (isspace(body[i]))
                body.erase(i, 1);
            else
                comma = false;
        }
        if (body[i] == '\"')
        {
            body.erase(i, 1);
        }
        if (body[i] == ',')
            comma = true;
    }

    std::istringstream bodyStream(body);
    while (std::getline(bodyStream, line, ',')) {
        auto delimiterPos = line.find(':');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            if (!key.empty() && !value.empty()) {
                _jsonfield[key] = value;
            }
        }
    }

    if (_jsonfield.find("name") == _jsonfield.end() || 
        (path == config.getCreateRoute() && _jsonfield.find("age") == _jsonfield.end()))
    {
        status = 0;
        return;
    }

    if (config.getEnforceJSONFormat())
    {
        if (path == config.getCreateRoute())
        {
            if (_jsonfield.size() != 2) {
                status = 0;
                return;
            }
        }
        if (path == config.getSearchRoute())
        {
            if (_jsonfield.size() != 1) {
                status = 0;
                return;
            }
        }
    }
    status = 1;
}

std::string Request::getHeader(std::string key)
{
    if (_headers.find(key) == _headers.end())
        return "";
    return _headers[key];
}

std::string Request::getJsonField(std::string field)
{
    if (_jsonfield.find(field) == _jsonfield.end())
        return "";
    return _jsonfield[field];
}

std::string Request::getMethod()
{
    return method;
}

std::string Request::getPath()
{
    return path;
}

int Request::getStatus()
{
    return status;
}