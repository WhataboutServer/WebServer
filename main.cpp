#include <iostream>

#include "server.hpp"

int main(int argc, char **argv)
{
		std::string	config_file = argc < 2 ? std::string() : argv[1];
		Server server(config_file);
		std::cout << server;
}
