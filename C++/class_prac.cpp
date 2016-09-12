#include <iostream>
#include <stdint.h>
#include <bitset>
//#include "NRIheader.h"


class nriglobal
{
private:
    char email[100];
    long phnum;
protected:
    char name[50];
    char degree[5];
    long int UFID;


protected:
    void getstudentPERSONALinfo(long int UFID)
    {
        std::cout << "Enter student email:\n";
        std::cin >> email;
        std::cout << "Enter student phnum:\n";
        std::cin >> phnum;
    }

    void showstudentPERSONALinfo(long int UFID)
    {
        std::cout << "Student email:\t" << email << std::endl;
        std::cout << "Student phnum:\t" << phnum << std::endl;
    }

public:
    void getstudentinfo(long int UFID)
    {
        std::cout << "Enter student name:\n";
        std::cin >> name;
        std::cout << "Enter student degree:\n";
        std::cin >> degree;
    }

    void showstudentinfo(long int UFID)
    {
        std::cout << "Student name:\t" << name << std::endl;
        std::cout << "Student degree:\t" << degree << std::endl;
    }

}obj1;

class nriglobal_child : public nriglobal
{
public:
    void childgetstudentPERSONALinfo(long int UFID)
    {
        getstudentPERSONALinfo(UFID);
    }

    void childshowstudentPERSONALinfo(long int UFID)
    {
        showstudentPERSONALinfo(UFID);
    }
};

int main()
{

    class nriglobal_child_of_child : public nriglobal_child
    {
    public:
        void child_of_childgetstudentPERSONALinfo(long int UFID)
        {
            childgetstudentPERSONALinfo(UFID);
        }

        void child_of_childshowstudentPERSONALinfo(long int UFID)
        {
            childshowstudentPERSONALinfo(UFID);
        }
    };


    nriglobal obj2;
    nriglobal_child obj3;
    obj2.getstudentinfo(60116379);
    obj3.childgetstudentPERSONALinfo(60116379);

    std::cout << "\n\n------------ Student info are as follows:\n";
    obj2.showstudentinfo(60116379);
    obj3.childshowstudentPERSONALinfo(60116379);

    nriglobal_child_of_child obj4;
    obj4.child_of_childgetstudentPERSONALinfo(60116379);
    obj4.child_of_childshowstudentPERSONALinfo(60116379);
}
