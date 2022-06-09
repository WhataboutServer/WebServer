#include "../../Response.hpp"
#include "../../Request.hpp"

int main()
{
	HTTP_Request q("GET pages/page.html HTTP/1.0\r\n");
	HTTP_Response a(q);
	std::cout << a;
	return 0;
}