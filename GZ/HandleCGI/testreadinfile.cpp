#include <iostream>
#include <vector>
#include <fstream>

void	readInFile(std::vector<char>& receivedTxtBuffer)
{
    std::fstream _fBuff("dummyfile");
    std::string filecontent;
    while(getline(_fBuff, filecontent))
    {
        std::string::iterator it = filecontent.begin();
        for(std::string::iterator it = filecontent.begin(); it != filecontent.end(); ++it)
        {
            receivedTxtBuffer.push_back(*it);
        }
        receivedTxtBuffer.push_back('\n');
    }
    _fBuff.close();
}

int main()
{
    std::vector<char> receivedTxtBuffer;
    readInFile(receivedTxtBuffer);
    for(size_t i = 0; i < receivedTxtBuffer.size(); ++i)
    {
        std::cout << receivedTxtBuffer[i];
    }
    std::cout << "\n";
    return (0);
}