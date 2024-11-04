#include "../inc/Server.hpp"

Server::Server(Config config): conf(config)
{
    data.init(config.getSQLPass(), config.getSQLFile());
    Handlers handlers;
    router.addRoute("POST", config.getCreateRoute(),
            [this, &handlers](const Request& request, DataStore& store) -> Response {
            return handlers.createPersonHandler(request, store, conf);
        });
    router.addRoute("GET", config.getSearchRoute(), 
        [this, &handlers](const Request& request, DataStore& store) -> Response {
            return handlers.searchPersonHandler(request, store, conf);
        });
}

Server::~Server()
{
    stop();
}

void Server::start(int port)
{
    this->port = port;

    int serverSocket = _init();

    FD_ZERO(&current);
    FD_SET(serverSocket, &current);

    while (running)
    {
        readfd = current;
        writefd = current;

        if (select(FD_SETSIZE, &readfd, &writefd, NULL, NULL) < 0)
            throw std::runtime_error("Server error. Please reboot.");
        
        for (int i = 0; i < FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, &readfd))
            {
                if (i == serverSocket)
                {
                    socklen_t socklen = sizeof(this->sockaddr);
                    int clientfd = accept(i, (struct sockaddr *)&this->sockaddr, &socklen);
                    if (clientfd < 0)
                    {
                        std::cerr << "Accept error: " << strerror(errno) << std::endl;
                        continue;
                    }

                    FD_SET(clientfd, &current);
                }
                else
                {
                    std::vector<char> buffer(1024);
                    int bytes;
                    std::string requestData;

                    while ((bytes = recv(i, buffer.data(), buffer.size(), 0)) > 0)
                    {
                        requestData.append(buffer.data(), bytes);
                        if (bytes < buffer.size())
                            break;
                    }
                    if (requestData.empty())
                    {
                        close(i);
                        FD_CLR(i, &current);
                    }
                    else
                    {
                        Request request(requestData, conf);
                        routeRequest(request, i);
						close(i);
                        FD_CLR(i, &current);
                    
                    }

                }
                break;
            }
        }
    }

    close(serverSocket);
    for (int i = 0; i < FD_SETSIZE; i++)
    {
        if (FD_ISSET(i, &current))
        {
            close(i);
        }
    }

}

int Server::_init()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
        throw std::runtime_error("Failed to create socket");

    int sockOpt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &sockOpt, sizeof(sockOpt)) < 0)
    {
        close(serverSocket);
        throw std::runtime_error("Failed to set socket options");
    }

    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(this->port);

    this->sockaddr = serverAddr;
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        close(serverSocket);
        throw std::runtime_error("Failed to bind socket");
    }

    if (listen(serverSocket, SOMAXCONN) < 0)
    {
        close(serverSocket);
        throw std::runtime_error("Failed to listen on socket");
    }

    int flags = fcntl(serverSocket, F_GETFL, 0);
    if (flags < 0)
    {
        close(serverSocket);
        throw std::runtime_error("Failed to get socket flags");
    }

    if (fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        close(serverSocket);
        throw std::runtime_error("Failed to set socket flags");
    }

    return serverSocket;
}

void Server::routeRequest(Request request, int fd)
{
    Response response;
    if (request.getStatus() == 1)
    {
        std::string method = request.getMethod();
        std::string path = request.getPath();

        auto handler = router.getHandler(method, path);
        if (handler)
            response = handler(request, data);
        else
        {
            response.setStatusCode(404);
            response.setHeader("Content-Type", "application/json");
            response.setBody("{\"error\": \"Not Found\", \"message\": \"The HTTP method or URI path is incorrect.\"}");
        }
    }
    else
    {
        response.setStatusCode(404);
        response.setHeader("Content-Type", "application/json");
        response.setBody("{\"error\": \"Not Found\", \"message\": \"The HTTP request is invalid.\"}");
    }
    send(fd, response.getResponse().c_str(), response.getResponse().size(), 0);
}

void Server::stop()
{
    running = false;
}