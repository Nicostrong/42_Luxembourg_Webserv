#include "HandleRequests.hpp"

void printErrMsg(std::string msg)
{
	std::cerr << "Error " << msg << "\n";
}

HandleRequests::HandleRequests(EventMonitoring& ref): em(ref)
{
	return;
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

void HandleRequests::passFdMonitoring(int fd)
{
	em.monitor(fd, POLLIN, 0, *this);
}
void HandleRequests::onReadEvent(int fd, int type)
{
	(void)type;
	//char buffer[1024];
	int result = read(fd, buffer, BUFFER_SIZE);
	if (result == -1)
	{
		printErrMsg("Reading from File");
	}
}
void HandleRequests::onWriteEvent(int fd, int type)
{
	(void)type;
	write(fd, buffer, BUFFER_SIZE);
}
void HandleRequests::onCloseEvent(int fd, int type)
{
	(void)type;
	close(fd);
}

/*
examples:

GET /test/demo_form.php?name1=value1&name2=value2

*/