#include "HandleRequests.hpp"

HandleRequests::HandleRequests(const char *config)
{
	LoadParsing(config);
	getMethodRules("error_page");
}

HandleRequests::~HandleRequests()
{
	
}

void HandleRequests::LoadParsing(const char *config)
{
	HandleConfig hc(config);
}

const std::string& HandleRequests::getMethodRules(std::string type)
{
	bool GET;
	bool PUT;
	bool DELETE;
	bool DENY;
	bool ALLOW;
	bool ALL;
	std::size_t found;

	HandleConfig hc("webserv.conf");

	webconfMap = hc.getwebconfMap();
	std::map<std::string, std::string>::iterator it = webconfMap.begin();
	while(it != webconfMap.end())
	{
		found = it->first.find(type);
		if (found != std::string::npos)
		{
			std::string rules = it->second;
			found = rules.find("limit_except");
			if (found != std::string::npos)
				rules.erase(0, found);

			std::cout << "[debug] rules:" << rules << "\n";

			GET = rules.find("GET") != std::string::npos;
			PUT = rules.find("PUT") != std::string::npos;
			DELETE = rules.find("DELETE") != std::string::npos;
			DENY = rules.find("DENY") != std::string::npos;
			ALLOW = rules.find("ALLOW") != std::string::npos;
			ALL = rules.find("ALL") != std::string::npos;
			std::cout << "debugging getMethodRules map:" << it->first << "\n=======\n" << it->second << "\n--------\n";
		}
		//std::cout << "debugging getMethodRules map:" << it->first << "\n=======\n" << it->second << "\n--------\n";
		++it;
	}
/*
	hc.printwebconfMap();
	std::string rules = hc.getValue("error_page");
	std::cout << "[debug] doing getMethodRules: " << rules  << "size : " << rules.size() << "\n";
	std::cout << "[debug] map: " << webconfMap["error_page"] << "\n";
	rules = webconfMap[type];*/
	/*if (rules.size() > 0)
	{
		std::size_t found = rules.find("limit_except");
		if (found != std::string::npos)
			rules.erase(0, found);

		std::cout << "[debug] rules:" << rules << "\n";

		GET = rules.find("GET") != std::string::npos;
		PUT = rules.find("PUT") != std::string::npos;
		DELETE = rules.find("DELETE") != std::string::npos;
		DENY = rules.find("DENY") != std::string::npos;
		ALLOW = rules.find("ALLOW") != std::string::npos;
		ALL = rules.find("ALL") != std::string::npos;
	}*/
	return "DEBUG\n";
}

void HandleRequests::ExecuteRequest()
{
	std::cout << "[debug] Executing requests.\n";
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


/*
examples:

GET /test/demo_form.php?name1=value1&name2=value2

*/