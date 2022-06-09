
#include "socket.hpp"

// listening constructor
Socket::Socket(Server &server)
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		//TODO handle errors
		// perror("ERROR\nSocket: socket");
	}
	if (bind(fd, (struct sockaddr *)&server.getAddress(), sizeof(server.getAddress())) < 0)
	{
		//TODO handle errors
		// perror("ERROR\nSocket: bind");
	}
	if (listen(fd, server.getBacklog()) == -1)
	{
		//TODO handle errors
		// perror("ERROR\nSocket: listen");
	}
}

// connected constructor
Socket::Socket(ConnectedClient &newClient)
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
	EV_SET(&event, fd, EVFILT_READ, EV_ADD, 0, 0, (void *)&newClient);
	if (kevent(newClient.getKqueueFd(), &event, 1, nullptr, 0, nullptr) == -1)
	{
		//TODO handle error
		// perror("ERROR\nSocket: adding connectedFd to kqueue with kevent()")
	}
}

// destructor
Socket::~Socket()
{
	if (fd != -1)
		close(fd);
}

// getter
int Socket::getFd() const { return fd; }
