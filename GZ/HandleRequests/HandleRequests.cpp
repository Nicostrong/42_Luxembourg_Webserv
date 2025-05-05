#include "HandleRequests.hpp"

void printErrMsg(std::string msg)
{
	std::cerr << "Error " << msg << "\n";
}

HandleRequests::HandleRequests(EventMonitoring& ref): em(ref)
{
	return;
}

HandleRequests::HandleRequests(const HandleRequests& copy): HttpRequest(), em(copy.em), webconfMap(copy.webconfMap)
{

}

HandleRequests& HandleRequests::operator=(const HandleRequests& copy)
{
	if (this != &copy)
	{
		this->em = copy.em;
		this->webconfMap = copy.webconfMap;
	}
	return (*this);
}

HandleRequests::~HandleRequests()
{
	
}

const std::string& HandleRequests::getMethod()
{
	return this->_method;
}
const std::string& HandleRequests::getURI()
{
	return this->_uri;
}
const std::string& HandleRequests::getHttpVersion()
{
	return this->_httpVersion;
}
const std::string& HandleRequests::getBody()
{
	return this->_body;
}

bool HandleRequests::checkMethod(Server server)
{
	return (server.checkMethod(_uri, _method));
}

bool HandleRequests::checkUri(Server server)
{
	return (server.checkUri(_uri));
}

/*
examples:

GET /test/demo_form.php?name1=value1&name2=value2

*/