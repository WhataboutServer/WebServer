// https://www.jmarshall.com/easy/http/#whatis

#include "Request.hpp"

HTTP_Request::HTTP_Request(const string & raw_request)
{
	stringstream file(raw_request);
	string line;
	getline(file, line, '\r');

	stringstream firts_line(line);
	firts_line >> method >> path >> version;

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
				message = key;
		}
	}
}

HTTP_Request::~HTTP_Request() {}

const std::string & HTTP_Request::getVersion() const { return version; }
const std::string & HTTP_Request::getMethod() const { return method; }
const std::string & HTTP_Request::getPath() const { return path; }

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