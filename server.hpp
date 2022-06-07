#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

//*#include "cluster.hpp"
//#include "location.hpp"
//#include "connected_client.hpp"
//#include "socket.hpp"

//______from Cluster_______//
#include <sys/event.h>	//kqueue kevent
//_________________________//
//______EXTRA______//
#include <string>
//_________________//

#define BUFFER_SIZE BUFSIZ

#define DEF_CONF "conf/default.conf"
#define N_EVENTS 1000
#define BACKLOG_SIZE 128

// class Cluster
// {
// 	private:
// 		// attributes
// 		std::vector<Server>					servers;
// 		int									kqueue_fd;
// 		struct kevent						event;
// 		struct kevent						triggered_events[N_EVENTS];
// 		class ConfigError: public std::exception
// 		{
// 			const char *what(std::string str) const throw()
// 			{
// 				return (("WARNING\n" + str + " is not a valid configuration file. " + \
// 				"The default configuration file \"default.conf\" is used instead").c_str());
// 			}
// 		};
// 	public:
// 		// constructor
// 		Cluster(std::string config_file);

// 		// destructor
// 		~Cluster();

// 		// getters
// 		int const			getKqueueFd() const;

// 		// run
// 		void run();

// 	private:
// 		// private methods
// 		std::vector<Server>	&getServers();
// 		void	parse_config_file(int conf_fd);

// };


//__________KEVENT_REFERENCE__________//
    //  struct kevent {
	//      uintptr_t ident;	     /*	identifier for this event */
	//      short     filter;	     /*	filter for event */
	//      u_short   flags;	     /*	action flags for kqueue	*/
	//      u_int     fflags;	     /*	filter flag value */
	//      intptr_t  data;	     /*	filter data value */
	//      void      *udata;	     /*	opaque user data identifier */
    //  };
//___________________________________//

class Server// : public Base
{
	private:
		// attributes
		//Cluster	const						&cluster;
		//_______from Cluster_______//
		// int									kqueue_fd; //kqueue per kernel event
		// struct kevent						event; // vedi reference up
		//struct kevent						triggered_events[N_EVENTS]; //????
		//_________________________//


		std::vector<std::string>			names; // domini
		// struct sockaddr_in					server_addr; // definisce la arte del socket CONTROLLARE
		int									port;
		// bool								default_server; //???
		std::map<int, std::string>			error_pages; // mapppa per errori
		size_t								client_body_size; // max len body
		// std::vector<Location>				locations; // vettore per path

		// std::vector<ConnectedClient *>		clients; // client connessi CONTROLLARE
		// unsigned short						backlog; //??? 

	//____dbalducc______//
		// Socket	*socket;
		
		void	init_config(const std::string & config_file); // vedere se usare direttamente costruttore
		void	parse_config_file(const std::string & config_file);
		void	keyAssignation(const std::string & key, std::stringstream & sline);


	public:
		// getters
		// struct sockaddr_in const	&getAddress() const;
		// unsigned short const		getBacklog() const;
		// int const					getListeningFd() const;
		//int const					getKqueueFd() const;

		// constructor
		Server(const std::string & config_file);

		// destructor
		~Server();

		// start listening
		// void startListening();

		// connect to client
		// void connectToClient();

		// communicate with client
		// void getRequest(ConnectedClient &client);
		// void giveResponse(ConnectedClient &client);
		friend std::ostream& operator<<(std::ostream & out, const Server& m);
};