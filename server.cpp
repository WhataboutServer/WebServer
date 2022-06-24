#include "server.hpp"

// constructor
Server::Server(int const &epollfd) : epollfd(epollfd)
{
	error_pages.insert(std::pair<int,std::string>(404, "./error_pages/404.html"));	//TODO aggiungi altre pagine di errore
	// std::cout << "+ un nuovo server e' stato creato" << std::endl;	//DEBUG
}

// destructor
Server::~Server()
{
	// std::cout << "- un server e' stato distrutto" << std::endl;		//DEBUG
}

// getters
int const	&Server::getKqueueFd() const { return epollfd; }

// ================================================================================================
// communication - prepareResponse old Version, funzionante
// ================================================================================================
/*
void Server::prepareResponse(ConnectedClient &client, void *default_server)
{
	//debug
	Server *ptr = (Server*)default_server;
	ptr = nullptr;
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << "\nServer:prepareResponse():\n\nTHE REQUEST FROM FD " << client.connected_fd << " IS: \"" << client.message << "\"" << std::endl;	//DEBUG
	client.message = std::string("HTTP/1.1 200 OK\r\n\r\n<html><body> <h> SONO UNA RESPONSE </h> </body> </html>");	//DEBUG
	//TODO prepare response based on specific server configuration; Request is client.message.

	// add connected_fd to kqueue for WRITE monitoring
	struct kevent event;
	bzero(&event, sizeof(event));
	EV_SET(&event, client.connected_fd, EVFILT_WRITE, EV_ADD, 0, 0, default_server);		// ident = connected_fd
	if (kevent(epollfd, &event, 1, nullptr, 0, nullptr) == -1)							// filter = WRITE
	{																						// udata = DefaultServer*
		//TODO handle error
		perror("ERROR\nServer.prepareResponse: kevent()");
		exit(EXIT_FAILURE);
	}
	std::cout << "\nThe event with ident = " << client.connected_fd << " and filter EVFILT_WRITE has been added to kqueue\n" << std::endl;
}
*/

// ================================================================================================
// communication - prepareResponse - MODIFIED Version, DA TESTARE
// ================================================================================================
void Server::prepareResponse(ConnectedClient &client, const Request & request)
{
	//debug
	// Server *ptr = (Server*)default_server;
	// ptr = nullptr;
	Response response(request);
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << "\nServer:prepareResponse():\n\nTHE REQUEST FROM FD " << client.connected_fd << " IS: \"" << request << "\"" << std::endl;	//DEBUG
	// client.message = std::string("HTTP/1.1 200 OK\r\n\r\n<html><body> <h> SONO UNA RESPONSE </h> </body> </html>");	//DEBUG
	client.message = response.getResponse();	//DEBUG
	//TODO prepare response based on specific server configuration; Request is client.message.

	// add connected_fd to kqueue for WRITE monitoring
	// struct kevent event;
	// bzero(&event, sizeof(event));
	// EV_SET(&event, client.connected_fd, EVFILT_WRITE, EV_ADD, 0, 0, this);		// ident = connected_fd
	// if (kevent(epollfd, &event, 1, nullptr, 0, nullptr) == -1)							// filter = WRITE
	// {																						// udata = DefaultServer*
	// 	//TODO handle error
	// 	perror("ERROR\nServer.prepareResponse: kevent()");
	// 	exit(EXIT_FAILURE);
	// }
	struct epoll_event ev;
	ev.events = EPOLLOUT;
	ev.data.fd = client.connected_fd;
	if(epoll_ctl(epollfd, EPOLL_CTL_ADD, client.connected_fd, &ev)<0)
	{
		printf("Failed to insert socket into epoll.\n");
	}

	std::cout << "\nThe event with ident = " << client.connected_fd << " and filter EVFILT_WRITE has been added to kqueue\n" << std::endl;
}

