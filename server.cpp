
#include "socket.hpp"
// getters
struct sockaddr_in const	&Server::getAddress() const { return server_addr; }
// unsigned short const		Server::getBacklog() const { return backlog; }
// int const					Server::getListeningFd() const { return socket->getFd(); }
//int const					Server::getKqueueFd() const { return cluster.getKqueueFd(); }

// constructor
Server::Server(const std::string & config_file)//, std::string content):
{
	// this->socket = nullptr;
	if (config_file.empty())
		parse_config_file(DEF_CONF);
	else
		parse_config_file(config_file);
	//TODO parse content and initialize server

	
/* 	int sockfd;
	struct sockaddr_in my_addr;

	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(this->port);     // short, network byte order
	my_addr.sin_addr.s_addr = inet_addr("10.12.110.57");
	memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

	bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr); */
	
}

void	Server::check_config()
{
	// if (this->port < 1 || this->port > 65535)
		// throw ConfigError();
	if (this->names.empty())
		this->names.push_back("server");
	if (this->error_pages.empty())
		this->error_pages.insert(std::pair<int, std::string>(404, "error_page/404.html")); //TODO vedere se eliminare
}

void Server::keyAssignation(const std::string & key, std::stringstream & sline)
{
	if (key == "client_body_size")
		sline >> client_body_size;
	else if (key == "listen")
	{
		std::string value;
		int	port;
		sline >> value;
		std::stringstream tmp(value);
		if (value.find(':') != std::string::npos)
		{
			std::getline(tmp, value, ':');
			server_addr.sin_addr.s_addr = inet_addr(value.c_str());
			tmp >> port;
			server_addr.sin_port = htons(port);
		}
		else if (value.find_first_not_of("0123456789;") != std::string::npos)
		{
			size_t pos;
			if ((pos = value.find(';')) != std::string::npos)
				server_addr.sin_addr.s_addr = inet_addr(value.substr(0, pos).c_str());
			else
				server_addr.sin_addr.s_addr = inet_addr(value.c_str());
			server_addr.sin_port = htons(80);
		}
		else if (!value.empty())
		{
			server_addr.sin_addr.s_addr = INADDR_ANY;
			tmp >> port;
			server_addr.sin_port = htons(port);
		}
		else
		{
			server_addr.sin_addr.s_addr = INADDR_ANY;
			server_addr.sin_port = htons(80);
		}
	}
	else if (key == "error_page")
	{
		size_t pos;
		int code;
		std::string path;
		sline >> code >> path;
		if (!path.empty())
		{
			if ((pos = path.find(';')) != std::string::npos)
				error_pages.insert(std::pair<int, std::string>(code, path.substr(0, pos)));
			else
				error_pages.insert(std::pair<int, std::string>(code, path));
		}
	}
	else if (key == "server_name")
	{
		std::string name;
		size_t pos;
		while (sline.good())
		{
			sline >> name;
			if (name == "#")
				return ;
			if ((pos = name.find(';')) != std::string::npos)
			{
				names.push_back(name.substr(0, pos));
				break;
			}
			else
				names.push_back(name);
		}
	}
	return ;
}

void	Server::parse_config_file(const std::string & config_file)
{
	int ck = 0;
	std::ifstream file(config_file);

	if (!config_file == DEF_CONF && !file.is_open())
		exit(1);
	else if (config_file == DEF_CONF && !file.is_open())
	{
		file.close();
		ck = 1;
		file.open(DEF_CONF);
		if (!file.is_open())
			exit(1);
	}

	std::string line_red;
	std::string key;
	std::stringstream parse_line;
	bool on_server_block;

	while (std::getline(file, line_red))
	{
		parse_line.clear();
		parse_line.str(line_red);
		parse_line >> key;

		if (key == "server")
		{
			on_server_block = true;
		}
		else if (key == "}")
		{
			on_server_block = false;
			try
			{
				check_config();
			}
			catch (ConfigError & e)
			{
				if (config_file == DEF_CONF && !ck)
				{
					std::cout << e.what(config_file) << std::endl;
					std::cout << "The default configuration file \"default.conf\" is used instead" << std::endl;
					this->parse_config_file(DEF_CONF);
				}
				else
					exit(1);
			}
		}
		else if (on_server_block)
		{
			if (key == "location")
			{
				Location nw;
				nw.setValues(file);
				locations.push_back(nw);
			}
			else
				keyAssignation(key, parse_line);
		}
	}
	file.close();
}

// destructor
Server::~Server()
{
	/*if (socket)
		delete socket;
	for (std::vector<ConnectedClient *>::iterator it = clients.begin(); it != clients.end(); ++it)
		delete *it;*/
}
/*
// start listening
void Server::startListening()
{
	socket = new Socket(*this);
}

// connect to client
void Server::connectToClient()
{
	ConnectedClient *newClient = new ConnectedClient(*this);
	clients.push_back(newClient);
}

// communicate with client
void Server::getRequest(ConnectedClient &client)
{
	int read_bytes = recv(client.getConnectedFd(), client.getBuf(), BUFFER_SIZE, 0);
	if (read_bytes == -1)
	{
		//TODO handle error
		// perror("ERROR\nServer: readFromClient: recv");
	}
	client.getMessage() += client.getBuf();
	bzero(client.getBuf(), BUFFER_SIZE);
	if (read_bytes < BUFFER_SIZE)
		giveResponse(client);
}

void Server::giveResponse(ConnectedClient &client)
{
	std::cout << client.getMessage() << std::endl;	//DEBUG
	//TODO parse request - client.getMessage() - and create response
}
*/

std::ostream& operator<<(std::ostream & out, const Server& m)
{
	out << "Server parsed parameters" << std::endl;

	out << "\tclient_body_size: " << m.client_body_size << std::endl;

	out << "\taddres: " << inet_ntoa(m.server_addr.sin_addr) << std::endl;
	out << "\tport: " << ntohs(m.server_addr.sin_port) << std::endl;
	// out << "\tport: " << m.port << std::endl;

	out << "\tnames:";
	std::vector<std::string>::const_iterator it_names = m.names.begin();
	while (it_names != m.names.end())
	{
		out << " [" << *it_names << "];";
		++it_names;
	}	
	out << std::endl;

	out << "\tlocation:";
	std::vector<Location>::const_iterator it_locations = m.locations.begin();
	while (it_locations != m.locations.end())
	{
		out << " [" << it_locations->getPath() << "];";
		++it_locations;
	}	
	out << std::endl;

	std::map<int, std::string>::const_iterator it_err = m.error_pages.begin();
	while (it_err != m.error_pages.end())
	{
		out << "\terror_page: " << it_err->first << " " << it_err->second << std::endl;
		++it_err;
	}	
	return out;
}