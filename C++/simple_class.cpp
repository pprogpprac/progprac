#include <iostream>
//#include <cstring>

//using namespace std;

class Person
{
    public:
    int age;
    char name[20];
};

int main()
{
    Person p[2];

    std::cout << "Enter name and age of the person 1:\n";
    std::cin >> p[0].name  >> p[0].age;

    std::cout << "Enter name and age of the person 2:\n";
    std::cin >> p[1].name  >> p[1].age;

    std::cout << "\nPrinting the entire list !\n";
    std::cout << "\n<------------- List starts here ! ------------>\n\n";
    std::cout << "__NAME__\t|\t__AGE__\n";
    std::cout << p[0].name << "\t|\t" << p[0].age << "\n";
    std::cout << p[1].name << "\t|\t" << p[1].age;
    std::cout << "\n<------------- List  ends  here ! ------------>\n\n";
    return 0;
}
