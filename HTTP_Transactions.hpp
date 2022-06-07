// https://www.jmarshall.com/easy/http/#whatis
#ifndef HTTP_HPP
# define HTTP_HPP

#include <iostream>
#include <string>
#include <sstream>
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

		HTTP_Request(const string & raw_request)
		{
			stringstream file(raw_request);
			string line;
			getline(file, line);

			// getting first line: method path version
			stringstream firts_line(line);
			string intermediate;
			getline(firts_line, method, ' ');
			getline(firts_line, path, ' ');
			getline(firts_line, version);

			// get all the headers
			// P.S. the last line could be a message
			while (getline(file, line))
			{
				stringstream sline(line);
				string key;
				while (getline(sline, key, ':'))
				{
					string value;
					sline >> ws;
					if (getline(sline, value))
						headers.insert(pair<string, string>(key, value));
					else
					{
						message = key;
						break;
					}
				}
			}
		}

		~HTTP_Request() {};

		friend ostream& operator<<(ostream & out, const HTTP_Request& m);
};

ostream& operator<<(ostream & out, const HTTP_Request& m)
{
	out << "HTTP Request:" << endl;
	out << "\tMethod: " << m.method << endl;
	out << "\tPath: " << m.path << endl;
	out << "\tVersion: " << m.version << endl;
	out << "\tHeaders: " << endl;
	unordered_map<string, string>::const_iterator it = m.headers.begin();
	while (it != m.headers.end())
	{
		cout << "\t\t" << it->first << ": " << it->second << endl;
		++it;
	}
	out << "\tMessage: " << m.message << endl;
	return out;
}

class HTTP_Response
{
	private:
		string	HTTP_version;
		string	response_status_code;
		string	reason_phrase;
		unordered_map<string, string>	headers;
		string	message;

		string response;

		HTTP_Response(const HTTP_Response &);
		HTTP_Response& operator=(const HTTP_Response &);

	public:

		HTTP_Response(const string & v, const string & c, const string & p)
			: HTTP_version(v), response_status_code(c), reason_phrase(p)
		{
			response = HTTP_version + " " + response_status_code + " " + reason_phrase + "\r\n";
		}
		string getResponse() { return response; }
		~HTTP_Response() {};
		friend ostream& operator<<(ostream & out, const HTTP_Response& m);

};

ostream& operator<<(ostream & out, const HTTP_Response& m)
{
	out << "HTTP Response:" << endl;
	out << "\tMethod: " << m.HTTP_version << endl;
	out << "\tPath: " << m.response_status_code << endl;
	out << "\tVersion: " << m.reason_phrase << endl;
	out << "\tHeaders: " << endl;
	unordered_map<string, string>::const_iterator it = m.headers.begin();
	while (it != m.headers.end())
	{
		out << "\t\t" << it->first << ": " << it->second << endl;
		++it;
	}
	out << "\tMessage: " << m.message << endl;
	out << "\tResponse: " << m.response << endl;
	return out;
}

#endif
