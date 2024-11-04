#include "../inc/Config.hpp"

Config::Config()
{
    //set all variables to default value
    SQLPass = "password";
    SQLFile = "data.db";
    CreateRoute = "/create";
    SearchRoute = "/search";
    maxAgeEnabled = false;
    enforceJSONFormat = false;
    port = 8080;
    maxAge = 100;
}

Config::~Config()
{
}

void Config::parseFile(std::string file)
{
    std::ifstream configFile(file);
    if (!configFile.is_open())
        throw std::runtime_error("Failed to open config file.");

    std::string line;
    while (std::getline(configFile, line))
    {
        std::istringstream lineStream(line);
        std::string key;
        std::string value;
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos)
        {
            key = line.substr(0, delimiterPos);
            value = line.substr(delimiterPos + 1);
        }

        if (key == "SQLPass")
            setSQLPass(value);
        else if (key == "SQLFile")
            setSQLFile(value);
        else if (key == "CreateRoute")
            setCreateRoute(value);
        else if (key == "SearchRoute")
            setSearchRoute(value);
        else if (key == "MaxAgeEnabled")
            setMaxAgeEnabled(value == "true");
        else if (key == "EnforceJSONFormat")
            setEnforceJSONFormat(value == "true");
        else if (key == "Port")
            setPort(std::stoi(value));
        else if (key == "MaxAge")
            setMaxAge(std::stoi(value));
    }
}

void Config::setSQLPass(std::string pass)
{
    SQLPass = pass;
}

void Config::setSQLFile(std::string file)
{
    SQLFile = file;
}

void Config::setCreateRoute(std::string route)
{
    CreateRoute = route;
}

void Config::setSearchRoute(std::string route)
{
    SearchRoute = route;
}

void Config::setMaxAgeEnabled(bool enabled)
{
    maxAgeEnabled = enabled;
}

void Config::setEnforceJSONFormat(bool enforce)
{
    enforceJSONFormat = enforce;
}

void Config::setPort(int port)
{
    this->port = port;
}

void Config::setMaxAge(int age)
{
    maxAge = age;
}

std::string Config::getSQLPass() const
{
    return SQLPass;
}

std::string Config::getSQLFile() const
{
    return SQLFile;
}

std::string Config::getCreateRoute() const
{
    return CreateRoute;
}

std::string Config::getSearchRoute() const
{
    return SearchRoute;
}

bool Config::getMaxAgeEnabled() const
{
    return maxAgeEnabled;
}

bool Config::getEnforceJSONFormat() const
{
    return enforceJSONFormat;
}

int Config::getPort() const
{
    return port;
}

int Config::getMaxAge() const
{
    return maxAge;
}

Config &Config::operator=(const Config &src)
{
    SQLPass = src.getSQLPass();
    SQLFile = src.getSQLFile();
    CreateRoute = src.getCreateRoute();
    SearchRoute = src.getSearchRoute();
    maxAgeEnabled = src.getMaxAgeEnabled();
    enforceJSONFormat = src.getEnforceJSONFormat();
    port = src.getPort();
    maxAge = src.getMaxAge();
    return *this;
}