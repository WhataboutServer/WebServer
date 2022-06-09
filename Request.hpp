// https://www.jmarshall.com/easy/http/#whatis
#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
using namespace std;

class HTTP_Request
{
	private:
		string	method;
		string	path;
		string	version;
		unordered_map<string, string>	headers;
		string	message;

		HTTP_Request();
		HTTP_Request(const HTTP_Request &);
		HTTP_Request& operator=(const HTTP_Request &);

	public:

		HTTP_Request(const string & raw_request);

		~HTTP_Request();

		const std::string & getVersion() const;
		const std::string & getMethod() const;
		const std::string & getPath() const;

		friend ostream& operator<<(ostream & out, const HTTP_Request& m);
};

#endif
