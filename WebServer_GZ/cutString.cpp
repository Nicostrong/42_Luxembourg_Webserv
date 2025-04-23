#include <iostream>

void CutString(std::string test)
{
	std::string firstpart, secondpart;
	std::size_t start = test.find_first_not_of(" ");
	test = test.substr(start, test.size());
	std::size_t end = test.find(" ");
	firstpart = test.substr(0, end);
	secondpart = test.substr(end, test.size());
	start = secondpart.find_first_not_of(" ");
	secondpart = secondpart.substr(start, secondpart.size());
	end = secondpart.find(" ");
	secondpart = secondpart.substr(0, end);
	std::cout << firstpart << "." << "\n";
	std::cout << secondpart << "." << "\n";
}

int main()
{
	std::string test = " client_max_body_size    5M; ";
	CutString(test);	
	return 0;
}