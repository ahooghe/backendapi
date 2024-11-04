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

    if (method == "OPTIONS")
        return;
    if (method == "GET" && path.find('?') != std::string::npos && path.find('=') != std::string::npos)
    {
        try 
        {
            size_t namePos = path.find("name=");
            if (namePos != std::string::npos) 
            {
                std::string name = path.substr(namePos + 5);
                size_t ampersandPos = name.find('&');
                if (ampersandPos != std::string::npos) 
                    name = name.substr(0, ampersandPos);
                _jsonfield["name"] = name;
                status = 1;
                path = path.substr(0, path.find('?'));
                return;
            }
        } 
        catch (const std::exception& e) 
        {
            status = 0;
            path = path.substr(0, path.find('?'));
            return;
        }
    }
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

    if (_jsonfield.find("name") == _jsonfield.end() || _jsonfield.find("age") == _jsonfield.end())
    {
        status = 0;
        return;
    }

    if (config.getEnforceJSONFormat())
    {
        if (_jsonfield.size() != 2) {
            status = 0;
            return;
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