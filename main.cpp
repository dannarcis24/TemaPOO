#include <iostream>
#include <string>

int main()
{
    bool a = static_cast<bool>("0");
    std::cout<<a<<'\n';
    a = static_cast<bool>("1");
    std::cout<<a<<'\n';
    a = static_cast<bool>("-2");
    std::cout<<a;
    return 0;
}