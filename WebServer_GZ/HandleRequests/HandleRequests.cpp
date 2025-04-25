#include "HandleRequests.hpp"

void HandleRequests::LoadParsing()
{
	HandleConfig hc("../HandleConfig/webserv.config");
	Server server1(hc.getNicoMap());
	server = server;
}

void HandleRequests::ExecuteRequest()
{
	std::cout << "[debug] Executing requests.\n";
}

bool HandleRequests::checkMethod(Server server)
{	
	return (server.checkMethod(this->_method));
}
bool HandleRequests::checkUri(Server server)
{
	return (server.checkUri(this->_uri));
}
bool HandleRequests::checkHttpVersion(Server server)
{
	return (server.checkHttpVersion(this->_httpVersion));
}
bool HandleRequests::checkBody(Server server)
{
	return (server.checkBody(this->_body));
}

void HandleRequests::Get()
{
	std::cout << "[debug]Executing Get Request...\n";
}

void HandleRequests::Post()
{
	std::cout << "[debug]Executing Post Request...\n";
}

void HandleRequests::Delete()
{
	std::cout << "[debug]Executing Delete Request...\n";
}

void HandleRequests::chooseMethod(Server server)
{
	/*if (!checkMethod(server) || !checkUri(server) || !checkHttpVersion(server) || !checkBody(server))
	{
		std::cerr << "Error: Bad Input./n";
		return;
	}*/
	if (_method == "GET")
	{
		Get();
	}
	if (_method == "POST")
	{
		Post();
	}
	if (_method == "DELETE")
	{
		Delete();
	}
	return;
}



/*
examples:

GET /test/demo_form.php?name1=value1&name2=value2

*/