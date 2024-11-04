#ifndef SERVER_HPP
#define SERVER_HPP

#include <unistd.h>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <strings.h>
#include <vector>
#include <string.h>

#include "Request.hpp"
#include "Router.hpp"
#include "Handlers.hpp"
#include "DataStore.hpp"
#include "Config.hpp"

class Server
{
	public:
		Server(Config config);
		~Server();
		void start(int port);
		void routeRequest(Request request, int fd);
		void stop();

	private:
		Router router;
		DataStore data;
		Config conf;
		int port;
		bool running;
		struct sockaddr_in sockaddr;
		fd_set current, readfd, writefd;

		int _init();
};

#endif // SERVER_HPP