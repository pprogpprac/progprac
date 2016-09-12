#include <iostream>

/*
Black       0;30     Dark Gray     1;30
Blue        0;34     Light Blue    1;34
Green       0;32     Light Green   1;32
Cyan        0;36     Light Cyan    1;36
Red         0;31     Light Red     1;31
Purple      0;35     Light Purple  1;35
Brown       0;33     Yellow        1;33
Light Gray  0;37     White         1;37
*/


int main()
{
    const std::string green("\033[1;32m");
    const std::string yellow("\033[1;33m");
    const std::string cyan("\033[0;36m");
    const std::string magenta("\033[0;35m");
    const std::string reset("\033[0m");
    const std::string red("\033[1;31m");
    const std::string black("\033[1;30m");

    std::cout << yellow << "yellow !\n";
    std::cout << green << "green !\n";
    std::cout << cyan << "cyan !\n";
    std::cout << magenta << "magenta !\n";
    std::cout << red << "red !\n";
    std::cout << black << "black !\n";
    std::cout << reset << "reset !\n";

    return 0;

}
