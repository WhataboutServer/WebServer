// https://www.jmarshall.com/easy/http/#whatis
#ifndef HTTP_HPP
# define HTTP_HPP

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

		HTTP_Request(const string & raw_request)
		{
			stringstream file(raw_request);
			string line;
			getline(file, line, '\r');

			// getting first line: method path version
			stringstream firts_line(line);
			// string intermediate;
			// getline(firts_line, method, ' ');
			// getline(firts_line, path, ' ');
			// getline(firts_line, version);
			firts_line >> method >> path >> version;

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

		const std::string & getVersion() const { return version; }
		const std::string & getMethod() const { return method; }
		const std::string & getPath() const { return path; }

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

/*
TODO
Request:
	- header:	host (mandatory)
				from
				user-agent
Response:
	- header:	Server
				date
				Last-Modified

*/

class HTTP_Response
{
	private:
		string							version;
		string							response_status_code;
		string							reason_phrase;
		unordered_map<string, string>	headers;
		string							message;
		string							response;

		HTTP_Response(const HTTP_Response &);
		HTTP_Response& operator=(const HTTP_Response &);

	public:

		HTTP_Response(const HTTP_Request & request)
			: message(), response()
		{
			version = request.getVersion();
			if (request.getMethod().compare("GET") == 0)
			{
				ifstream file(request.getPath());
				size_t lenght = 0;
				if (file.is_open())
				{
					string line;
					while(getline(file, line))
					{
						lenght += line.length();
						message += line + "\r\n";
					}
					response_status_code = "200";
					reason_phrase = "OK";
					headers.insert(pair<string, string>("Content-Length", to_string(lenght)));
				}
				else
				{
					response_status_code = "404";
					reason_phrase = "File Not Found";
				}
			}
			response += version + " " + response_status_code + " " + reason_phrase + "\r\n";
			unordered_map<string, string>::const_iterator it = headers.begin();
			while (it != headers.end())
			{
				response += it->first + ": " + it->second + "\r\n";
				++it;
			}
			response += "\r\n" + message;
		}
		string getResponse() { return response; }
		~HTTP_Response() {};
		friend ostream& operator<<(ostream & out, const HTTP_Response& m);
};

ostream& operator<<(ostream & out, const HTTP_Response& m)
{
	// out << "HTTP Response:" << endl;
	// out << "\tMethod: " << m.version << endl;
	// out << "\tPath: " << m.response_status_code << endl;
	// out << "\tVersion: " << m.reason_phrase << endl;
	// out << "\tHeaders: " << endl;
	// unordered_map<string, string>::const_iterator it = m.headers.begin();
	// while (it != m.headers.end())
	// {
	// 	out << "\t\t" << it->first << ": " << it->second << endl;
	// 	++it;
	// }
	// out << "\tMessage: " << m.message << endl;
	out << "Response: "<< endl << m.response << endl;
	return out;
}

#endif
