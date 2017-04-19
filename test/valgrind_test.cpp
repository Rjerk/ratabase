#include <iostream>

void func(char* s)
{
    char* ss = s;
}

int main()
{
    char* s = "123";
    func(s);
    std::cout << s << std::endl;
}
