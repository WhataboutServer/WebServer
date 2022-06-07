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
void Location::setValues(std::ifstream & file)
{
	std::stringstream parse_line;
	std::string key;
	std::string line_red;

	while (std::getline(file, line_red))
	{
		parse_line.clear();
		parse_line.str(line_red);
		parse_line >> std::ws;
		std::getline(parse_line, key, ' ');
		if (key.compare("}") == 0)
			break;
		else if (key.compare("#") != 0)
			std::cout << line_red << std::endl;
	}
}