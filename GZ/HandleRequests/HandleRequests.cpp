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
	int result;
	totalBuffer.clear();
	while((result = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		totalBuffer.append(buffer, result);
	}
	if (result == -1)
	{
		printErrMsg("Reading from File");
	}
	em.unmonitor(fd);
}
void HandleRequests::onWriteEvent(int fd, int type)
{
	(void)type;
	write(fd, buffer, BUFFER_SIZE);
	em.unmonitor(fd);
}
void HandleRequests::onCloseEvent(int fd, int type)
{
	(void)type;
	close(fd);
	em.unmonitor(fd);
}

HandleRequests::HandleRequests(const HandleRequests& copy): em(copy.em), webconfMap(copy.webconfMap)
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

/*
examples:

GET /test/demo_form.php?name1=value1&name2=value2

*/