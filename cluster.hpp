#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <utility>		//pair
#include <sys/event.h>	//kqueue kevent
#include <fcntl.h>		//open()
#include <exception>
#include "server.hpp"

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
