// https://www.jmarshall.com/easy/http/#whatis

#include "Response.hpp"
#include "Request.hpp"
#include <filesystem>

Response::Response(const Request & request)
	: message(), response()
{
	Cgi cgi;
	version = request.getVersion();
	size_t lenght = 0;
	if (request.getMethod() == "GET")
	{
		std::string path = request.getPath();
		std::cout << "PATH: "<< path << std::endl;
		std::cout << "pwd PATH: "<< get_working_path() << std::endl;
		path.erase(0, 1);
		//____dbalducc___test___for___CGI//
		if (path.find(".php") && check_file_exist(get_working_path() + "/" + path))
		{
			message = cgi.run_cgi(path);
			lenght = message.length();
			response_status_code = "200";
			reason_phrase = "OK";
			headers.insert(pair<string, string>("Content-Length", to_string(lenght)));
		}
		//______________________________//
		//____dbalducc___test___for___CGI//
		else{
		//______________________________//
			ifstream file(path);
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
				file.open("error_pages/404.html");
				if (file.is_open())
				{
					string line;
					while(getline(file, line))
					{
						lenght += line.length();
						message += line + "\r\n";
					}
				}
				response_status_code = "404";
				reason_phrase = "File Not Found";
				headers.insert(pair<string, string>("Content-Length", to_string(lenght)));
			}
		//____dbalducc___test___for___CGI//
		}
		//______________________________//
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

Response::~Response() {}

string Response::getResponse() { return response; }

ostream& operator<<(ostream & out, const Response& m)
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