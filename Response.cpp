// https://www.jmarshall.com/easy/http/#whatis

#include "Response.hpp"
#include "Request.hpp"

HTTP_Response::HTTP_Response(const HTTP_Request & request)
	: message(), response()
{
	version = request.getVersion();
	if (request.getMethod() == "GET")
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

HTTP_Response::~HTTP_Response() {}

string HTTP_Response::getResponse() { return response; }

ostream& operator<<(ostream & out, const HTTP_Response& m)
{
	out << "HTTP Response:" << endl;
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