// https://www.jmarshall.com/easy/http/#whatis
#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
using namespace std;

class HTTP_Request;

class HTTP_Response
{
	private:
		string							version;
		string							response_status_code;
		string							reason_phrase;
		unordered_map<string, string>	headers;
		string							message;
		string							response;

		HTTP_Response();
		HTTP_Response(const HTTP_Response &);
		HTTP_Response& operator=(const HTTP_Response &);

	public:

		HTTP_Response(const HTTP_Request & request);

		~HTTP_Response();

		string getResponse();
		friend ostream& operator<<(ostream & out, const HTTP_Response& m);
};

#endif
