#include "HandleRequests.hpp"

void HandleRequests::ExecuteRequest()
{
	std::cout << "[debug] Executing requests.\n";
}

bool HandleRequests::checkMethod()
{
	std::string methods[] = {"GET", "POST", "DELETE"};
	int i = 0;
	while(i < 3)
	{
		if (methods[i] == this->_method)
		{
			return true;
		}
		i++
	} 
	return false;
}
bool HandleRequests::checkUri()
{
	return true;
}
bool HandleRequests::checkHttpVersion()
{
	std::string test = _httpVersion;
	test.erase(0, test.find("//"));

	std::string versions[] = {"1.1", "2.0", "2.1"};
	int i = 0;
	while(i < 3)
	{
		if (versions[i] == this->_method)
		{
			return true;
		}
		i++
	}
	return false;
}
bool HandleRequests::checkBody()
{
	return true;
}

void HandleRequests::concatResult()
{
	return;
}