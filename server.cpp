#include "server.hpp"

// getters
struct sockaddr_in const	&Server::getAddress() const { return server_addr; }
unsigned short const		Server::getBacklog() const { return backlog; }
int const					Server::getListeningFd() const { return socket->getFd(); }
//int const					Server::getKqueueFd() const { return cluster.getKqueueFd(); }

// constructor
Server::Server(bool default_server)://, std::string content):
default_server(default_server)
{
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

void	init_config(std::string config_file){
/* if aprire config_file ok
		if passa a parse_config_file(fd) ok
			return
	else
		exception
			if aprire default conf ok
				if passa a parse_config_file(fd) ok
					return
		exit(1)
*/
}

int		parse_config_file(std::string config_file){
	std::ifstream file(config_file);
	if (file.is_open())
	{
		std::string line;
		int i = 0;
		while (std::getline(file, line))
		{
			if (line.compare("server") >= 0)
			{
				servers_conf.resize(i + 1);
				while (std::getline(file, line))
				{
					std::stringstream sline(line);
					if (line.compare("}") >= 0)
						break;
					sline >> ws;
					std::string key;
					while (std::getline(sline, key, ' '))
					{
						std::string value;
						sline >> ws;
						if (std::getline(sline, value))
							// servers_conf[i].insert(pair<string, string>(key, value));
					}
				}
				i++;
			}
		}
		file.close();
}

// destructor
Server::~Server()
{
	for (std::vector<ConnectedClient *>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		(*it)->~ConnectedClient();
		delete *it;
	}
}

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
