#include <iostream>

#include "../../server.hpp"

int main(int argc, char **argv)
{
	Server server(argc < 2 ? std::string() : argv[1]);
	std::cout << server;
}
