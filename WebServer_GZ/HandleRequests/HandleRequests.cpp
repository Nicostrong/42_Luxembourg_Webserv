#include "HandleRequests.hpp"

HandleRequests::HandleRequests(const char *config)
{
	LoadParsing(config);
	//getMethodRules("error_page");
	getMethodRules("location / ");
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
	std::map<std::string, bool> rulesMap;
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
			{
				rules.erase(0, found);
			}
			std::string permission = rules;
			permission.erase(0, permission.find("{"));
			if (permission.find("deny") != std::string::npos || permission.find("allow") != std::string::npos)
			{
				std::string permissionDirection;
				if (permission.find("deny") != std::string::npos)
					permissionDirection = "DENY";
				if (permission.find("allow") != std::string::npos)
					permissionDirection = "ALLOW";
				permission.erase(0, permission.find("deny") + 4);
				if ((found = permission.find_first_not_of(" \t")) != std::string::npos)
					permission.erase(0, found);
				if ((found = permission.find_first_of(";")) != std::string::npos)
					permission.erase(found, permission.size());
				
				std::string permissionValue = permission;
				std::cout << "[debug] permission:" << permissionDirection << " " << permissionValue << "\n";
			}

			found = rules.find("{");
			if (found != std::string::npos)
				rules.erase(found - 1, rules.size());

			std::cout << "[debug] rules:" << rules << "\n";
			std::cout << "[debug] permission:" << permission << "\n";

			rulesMap["GET"] = (rules.find("GET") != std::string::npos);
			rulesMap["PUT"] = (rules.find("PUT") != std::string::npos);
			rulesMap["DELETE"] = (rules.find("DELETE") != std::string::npos);
			rulesMap["DENY"] = (rules.find("DENY") != std::string::npos);
			rulesMap["ALLOW"] = (rules.find("ALLOW") != std::string::npos);

			std::cout << "debugging getMethodRules map:" << it->first << "\n=======\n" << it->second << "\n--------\n";
			
			break;
		}
		++it;
	}
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