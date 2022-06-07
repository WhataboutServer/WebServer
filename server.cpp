#include "server.hpp"
/*
// getters
struct sockaddr_in const	&Server::getAddress() const { return server_addr; }
unsigned short const		Server::getBacklog() const { return backlog; }
int const					Server::getListeningFd() const { return socket->getFd(); }
//int const					Server::getKqueueFd() const { return cluster.getKqueueFd(); }
*/
// constructor
Server::Server(const std::string & config_file)//, std::string content):
{
	// this->socket = nullptr;
	if (config_file.empty())
		parse_config_file(DEF_CONF);
	else
		parse_config_file(config_file);
	//TODO parse content and initialize server

	/*
	int sockfd;
	struct sockaddr_in my_addr;

	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);     // short, network byte order
	my_addr.sin_addr.s_addr = inet_addr("10.12.110.57");
	memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

	bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr);
	*/
}

int	Server::check_config()
{
	if (this->port < 1 || this->port > 65535)
		return 1;
	if (this->names.empty())
		this->names.push_back("server");
	if (this->error_pages.empty())
		this->error_pages.insert(std::pair<int, std::string>(404, "error_page/404.html")); //TODO vedere se eliminare
}

void Server::keyAssignation(const std::string & key, std::stringstream & sline)
{
	if (key.compare("client_body_size") == 0)
	{
		std::string value;
		sline >> std::ws;
		if (std::getline(sline, value))
		{
			std::stringstream tmp(value);
			tmp >> client_body_size;
		}
	}
	else if (key.compare("listen") == 0)
	{
		std::string value;
		sline >> std::ws;
		if (std::getline(sline, value))
		{
			std::stringstream tmp(value);
			tmp >> port;
		}
	}
	else if (key.compare("error_page") == 0)
	{
		std::string code_s;
		sline >> std::ws;
		if (std::getline(sline, code_s, ' '))
		{
			std::stringstream tmp(code_s);
			int code;
			tmp >> code;
			std::string path;
			sline >> std::ws;
			if (std::getline(sline, path))
				error_pages.insert(std::pair<int, std::string>(code, path));
		}
	}
	else if (key.compare("server_name") == 0)
	{
		std::string name;
		sline >> std::ws;
		while (std::getline(sline, name, ' '))
		{
			if (name.compare("#") == 0)
				return ;
			names.push_back(name);
		}
	}
	else if (key.compare("location") == 0) {}
	return ;
}

void	Server::parse_config_file(const std::string & config_file)
{
	std::ifstream file(config_file);
	if (!file.is_open())
	{
		file.open(DEF_CONF);
		if (!file.is_open())
			return ;			// throw ;
	}
	std::string line_red;
	std::string key;
	std::stringstream parse_line;
	bool on_server_block;
	while (std::getline(file, line_red))
	{
		parse_line.clear();
		parse_line.str(line_red);
		std::getline(parse_line, key, ' ');

		if (key.compare("server") == 0)
			on_server_block = true;
		else if (key.compare("}") == 0){
			on_server_block = false;
			check_config();
		}
		if (on_server_block)
		{
			parse_line.clear();
			parse_line.str(line_red);
			parse_line >> std::ws;
			if (std::getline(parse_line, key, ' '))
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

	out << "\tport: " << m.port << std::endl;

	out << "\tnames:";
	std::vector<std::string>::const_iterator it_names = m.names.begin();
	while (it_names != m.names.end())
	{
		out << " [" << *it_names << "];";
		++it_names;
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