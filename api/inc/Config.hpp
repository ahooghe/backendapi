#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>

class Config
{
    public:
        Config();
        ~Config();

        void parseFile(std::string file);

        void setSQLPass(std::string pass);
        void setSQLFile(std::string file);
        void setCreateRoute(std::string route);
        void setSearchRoute(std::string route);

        void setMaxAgeEnabled(bool enabled);
        void setEnforceJSONFormat(bool enforce);

        void setPort(int port);
        void setMaxAge(int age);

        std::string getSQLPass() const;
        std::string getSQLFile() const;
        std::string getCreateRoute() const;
        std::string getSearchRoute() const;

        bool getMaxAgeEnabled() const;
        bool getEnforceJSONFormat() const;

        int getPort() const;
        int getMaxAge() const;

        Config &operator=(const Config &src);

    private:
        std::string SQLPass;
        std::string SQLFile;
        std::string CreateRoute;
        std::string SearchRoute;
        bool maxAgeEnabled;
        bool enforceJSONFormat;
        int port;
        int maxAge;
};


#endif