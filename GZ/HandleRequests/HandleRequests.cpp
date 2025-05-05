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

const std::map<std::string, std::string>& HandleRequests::_getResponse(Server server)
{
	if (!_checkMethod(server) || !_checkUri(server))
	{
		response["status"] = "ERROR";
		return (response);
	}
	response["status"] = "SUCCESS";
	response["method"] = _getMethod();
	response["uri"] = _getUri();
	response["http"] = _getHttpVersion();
	response["body"] = _getBody();
	return (response);
}

const std::string& HandleRequests::_getMethod()
{
	return this->_method;
}
const std::string& HandleRequests::_getUri()
{
	return this->_uri;
}
const std::string& HandleRequests::_getHttpVersion()
{
	return this->_httpVersion;
}
const std::string& HandleRequests::_getBody()
{
	return this->_body;
}

bool HandleRequests::_checkMethod(Server server)
{
	return (server.checkMethod(_uri, _method));
}

bool HandleRequests::_checkUri(Server server)
{
	return (server.checkUri(_uri));
}

/*
examples:

GET /test/demo_form.php?name1=value1&name2=value2

*/