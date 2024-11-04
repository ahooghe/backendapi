#include "../inc/Server.hpp"
#include "../inc/Config.hpp"
#include <iostream>
#include <csignal>

// Global server pointer to be used in the signal handler
Server* globalServerPtr = nullptr;

// Signal handler function
void signalHandler(int signum)
{
    if (globalServerPtr)
    {
        std::cout << "\nCTRL+C was pressed. Stopping the server..." << std::endl;
        globalServerPtr->stop();
    }
    exit(signum);
}

int main(int argc, char **argv)
{
    Config config;
    if (argc >= 2)
        config.parseFile(argv[1]);

    // Print the configured data
    std::cout << "API Settings" << std::endl;
    std::cout << "===================" << std::endl;
    std::cout << "Port: " << config.getPort() << std::endl;
    std::cout << "SQL File: " << config.getSQLFile() << std::endl;
    std::cout << "SQL Password: " << config.getSQLPass() << std::endl;
    std::cout << "Create Route: " << config.getCreateRoute() << std::endl;
    std::cout << "Search Route: " << config.getSearchRoute() << std::endl;
    std::cout << "Max Age Enabled: " << (config.getMaxAgeEnabled() ? "true" : "false") << std::endl;
    std::cout << "Max Age: " << config.getMaxAge() << std::endl;
    std::cout << "Enforce JSON Format: " << (config.getEnforceJSONFormat() ? "true" : "false") << std::endl;
    std::cout << "===================" << std::endl;

    Server server(config);
    globalServerPtr = &server;

    // Register signal handler for SIGINT
    signal(SIGINT, signalHandler);

    
    try
    {
        server.start(config.getPort());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return (0);
}