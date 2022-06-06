#pragma once

#include <string>
#include <vector>

#include "cluster.hpp"
#include "location.hpp"
#include "base.hpp"
#include "connected_client.hpp"
#include "socket.hpp"

//______from Cluster_______//
#include <sys/event.h>	//kqueue kevent
//_________________________//


#define BUFFER_SIZE BUFSIZ

#define DEF_CONF "/conf/default.conf"
#define N_EVENTS 1000
#define BACKLOG_SIZE 128

class Cluster
{
	private:
		// attributes
		std::vector<Server>					servers;
		int									kqueue_fd;
		struct kevent						event;
		struct kevent						triggered_events[N_EVENTS];
		class ConfigError: public std::exception
		{
			const char *what(std::string str) const throw()
			{
				return (("WARNING\n" + str + " is not a valid configuration file. " + \
				"The default configuration file \"default.conf\" is used instead").c_str());
			}
		};
	public:
		// constructor
		Cluster(std::string config_file);

		// destructor
		~Cluster();

		// getters
		int const			getKqueueFd() const;

		// run
		void run();

	private:
		// private methods
		std::vector<Server>	&getServers();
		void	parse_config_file(int conf_fd);

};

class Server : public Base
{
	private:
		// attributes
		//Cluster	const						&cluster;
		//_______from Cluster_______//
		struct kevent						event;
		struct kevent						triggered_events[N_EVENTS];
		//_________________________//


		std::vector<std::string>			names;
		struct sockaddr_in					server_addr;
		bool								default_server;
		std::map<int, std::string>			error_pages;
		size_t								client_body_size;
		std::vector<Location>				locations;

		std::vector<ConnectedClient *>		clients;
		unsigned short						backlog;

	public:
		// getters
		struct sockaddr_in const	&getAddress() const;
		unsigned short const		getBacklog() const;
		int const					getListeningFd() const;
		//int const					getKqueueFd() const;

		// constructor
		Server(bool default_server);

		// destructor
		~Server()
		{
			for (std::vector<ConnectedClient *>::iterator it = clients.begin(); it != clients.end(); ++it)
			{
				(*it)->~ConnectedClient();
				delete *it;
			}
		}

		// start listening
		void startListening();

		// connect to client
		void connectToClient();

		// communicate with client
		void getRequest(ConnectedClient &client);
		void giveResponse(ConnectedClient &client);

};
