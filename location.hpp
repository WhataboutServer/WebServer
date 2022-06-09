#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

class Location
{
private:
	// attributes
	std::string					path;
	std::string					root;
	std::vector<std::string>	allowed_methods;
	struct	Redirection
	{
		std::string	location;
		int			status_code;
	}							redirection;
public:
	// constructor
	Location();

	// destructor
	~Location();

	// getters
	std::string const	&getPath() const;
	std::string const	&getRoot() const;
	bool				isMethodAllowed(const std::string & method) const;
	Redirection const	&getRedirection() const;

	void setValues(std::ifstream & file);
};