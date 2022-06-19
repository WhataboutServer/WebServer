#pragma once

#include <string>
#include <map>
#include <iostream>

#include <sys/socket.h>	//socket()
#include <arpa/inet.h>	//inet_addr()
#include <cstring>		//bzero()
#include <unistd.h>		//close()

#include <sys/event.h>	//kqueue kevent

// #include "location.hpp"
#include "connected_client.hpp"
#include "Response.hpp"
#include "Request.hpp"

class Server
{
protected:
	// attributes
	int const							&kqueue_fd;
	// configuration parameters
	std::map<int, std::string>			error_pages;
	size_t								client_body_size;
	std::map<std::string,Location>		locations;

public:
	// default constructor
	Server(int const &kqueue_fd);
	// copy constructor
	Server(Server const &other);
	// assign operator oveload
	Server &operator=(Server const &other);

	// destructor
	~Server();

	// getters
	int const	&getKqueueFd() const;

	// initialization
	void addLocation(std::string path, Location location);

	// communication
	// void prepareResponse(ConnectedClient &client, void *default_server);
	void prepareResponse(ConnectedClient &client, const Request &request);

};
