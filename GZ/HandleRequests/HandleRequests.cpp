#include "HandleRequests.hpp"

void printErrMsg(std::string msg)
{
	std::cerr << "Error " << msg << "\n";
}

HandleRequests::HandleRequests(EventMonitoring& ref): em(ref)
{
	return;
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
/*
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
}*/

void HandleRequests::onReadEvent(int fd, int type) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    RequestParser::ParseResult parse_result;

    while ((bytes_read = recv(fd, buffer, BUFFER_SIZE, 0)) > 0) {
        _request_data.append(buffer, bytes_read);
        parse_result = _parser.parse(_request_data, _current_request);
        
        if (parse_result == RequestParser::PARSE_COMPLETE) {
            _buildResponse(fd);
            break;
        } else if (parse_result == RequestParser::PARSE_ERROR) {
            _sendErrorResponse(fd, 400);
            break;
        }
    }

    if (bytes_read <= 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            _sendErrorResponse(fd, 500);
        }
        em.unmonitor(fd);
        close(fd);
    }
}
/*
void HandleRequests::onWriteEvent(int fd, int type)
{
	(void)type;
	write(fd, buffer, BUFFER_SIZE);
	em.unmonitor(fd);
}
*/

void HandleRequests::onWriteEvent(int fd, int type) {
    ssize_t bytes_sent = send(fd, _response_data.c_str() + _sent_bytes, 
                            _response_data.length() - _sent_bytes, 0);
    
    if (bytes_sent > 0) {
        _sent_bytes += bytes_sent;
        if (_sent_bytes >= _response_data.length()) {
            if (_current_request.headers["Connection"] == "keep-alive") {
                _resetConnection(fd);
            } else {
                em.unmonitor(fd);
                close(fd);
            }
        }
    } else {
        em.unmonitor(fd);
        close(fd);
    }
}
/*
void HandleRequests::onCloseEvent(int fd, int type)
{
	(void)type;
	close(fd);
	em.unmonitor(fd);
}*/

void HandleRequests::onCloseEvent(int fd, int type) {
    if (_cgi_active) {
        kill(_cgi_pid, SIGTERM);
        waitpid(_cgi_pid, NULL, 0);
    }
    close(fd);
    em.unmonitor(fd);
    _cleanRequestContext(fd);
}

ParseResult parse(std::string& raw, Request& req)
{

}

void HandleRequests::_buildResponse(int fd) {
    Response res;
    
    try {
        if (_current_request.method == "GET") {
            _handleGetRequest(res);
        } else if (_current_request.method == "POST") {
            _handlePostRequest(res);
        }
        
        res.headers["Content-Length"] = toString(res.content.size());
        res.headers["Connection"] = _keep_alive ? "keep-alive" : "close";
        
        _response_data = res.toString();
    } catch (const FileNotFoundException&) {
        _sendErrorResponse(fd, 404);
    }
}




/*
examples:

GET /test/demo_form.php?name1=value1&name2=value2

*/