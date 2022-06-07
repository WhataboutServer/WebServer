#include "location.hpp"

// constructor
Location::Location() {}

// destructor
Location::~Location() {}

// getters
std::string const &Location::getPath() const { return path; }
std::string const &Location::getRoot() const { return root; }

bool Location::isMethodAllowed(const std::string & method) const
{
	for (std::vector<std::string>::const_iterator it = allowed_methods.begin(); it != allowed_methods.end(); ++it)
	{
		if (!it->compare(method.c_str()))
			return true;
	}
	return false;
}
Location::Redirection const	&Location::getRedirection() const { return redirection; }

// methods
void Location::setValues(std::stringstream & sline)
{
	std::string name;
	while (std::getline(sline, name))
		std::cout << name << std::endl;
	
	// std::string name;
	// sline >> std::ws;
	// if (std::getline(sline, name))
	// 	path = name;
}