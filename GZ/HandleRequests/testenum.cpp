#include <iostream>

/*
class MyClass
{
    private:
        enum myenum
        {
            OK = 200
        };
    public:
        void printEnum(){
            myenum enum1;
            std::cout << "[debug enum]:" << enum1["OK"] << "\n";}
};
*/
enum HttpBase
{
    OK = 200,
    ERROR = 500
};

int main()
{
    HttpBase tmp = OK;
    std::cout << tmp << "\n";
    enum HttpBase test1 = OK;
    enum HttpBase test2 = ERROR;
    std::cout << test1 << "\n";
    std::cout << test2 << "\n";
    
    return 0;
}