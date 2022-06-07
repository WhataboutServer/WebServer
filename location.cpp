#include "location.hpp"

// constructor
Location::Location() {}

// destructor
Location::~Location() {}

// getters
std::string const &Location::getPath() const { return path; }
std::string const &Location::getRoot() const { return root; }

Location::Redirection const	&Location::getRedirection() const { return redirection; }

// methods
void Location::setValues()
{
	
}