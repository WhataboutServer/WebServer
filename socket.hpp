#pragma once

#include <sys/socket.h>	//socket()
#include <arpa/inet.h>	//inet_addr()
#include <cstring>		//bzero()
#include <unistd.h>		//close()

#include "server.hpp"


class Socket
{
private:
	// attributes
	int	fd;

public:
	// listener constructor
	Socket(Server &server)
	{
		int opt = 0;
		this->fd = socket(AF_INET6, SOCK_STREAM, 0); // add ipv6 for ipv4/ipv6 connection
		if (fd < 0)
		{
			//TODO handle errors
			perror("ERROR\nSocket: can't create socket\n");
			exit(1);
		}
		if (setsockopt(fd, SOL_SOCKET, IPV6_V6ONLY, (char *)&opt, sizeof(opt)) < 0){ //remove ipv6 only
			perror("ERROR\nSocket: can't set option");
		}
		opt += 1;
		//set master socket to allow multiple connections , 
    	//this is just a good habit, it will work without this 
		if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0){ //remove ipv6 only
			perror("ERROR\nSocket: can't set option");
		}
		if (bind(fd, (struct sockaddr *)&server.getAddress(), sizeof(server.getAddress())) < 0)
		{
			//TODO handle errors
			// perror("ERROR\nSocket: bind");
		}
/* 		if (listen(fd, server.getBacklog()) == -1)
		{
			//TODO handle errors
			// perror("ERROR\nSocket: listen");
		} */
	}

	// connected constructor
/* 	Socket(ConnectedClient &newClient)
	{
		socklen_t socklen = sizeof(newClient.getAddress());
		newClient.getAddress().sin_family = AF_INET;
		fd = accept(newClient.getListeningFd(), (sockaddr *)&newClient.getAddress(), &socklen);
		if (fd == -1)
		{
			//TODO handle error
			// perror("ERROR\nSocket: accept")
		}
		struct kevent event;
		EV_SET(&event, newClient.getConnectedFd(), EVFILT_READ, EV_ADD, 0, 0, (void *)&newClient);
		if (kevent(newClient.getKqueueFd(), &event, 1, nullptr, 0, nullptr) == -1)
		{
			//TODO handle error
			// perror("ERROR\nSocket: adding connectedFd to kqueue with kevent()")
		}
	} */

	// destructor
	~Socket()
	{
		if (fd != -1)
			close(fd);
	}

	// getter
	int const getFd() const { return fd; }

};
