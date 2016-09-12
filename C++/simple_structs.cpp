#include <iostream>
#include <cstring>

using namespace std;

struct Person
{
    char name[20];
    int id;
};

int main()
{
    int x, y, z;
    cout<<"Enter 2 numbers: ";
    cin >> x >> y;
    z = x + y;
    cout<<"The result of addition is "<<z<<endl;

    struct Person p =
    {
        "Naveen R Iyer",
        213
    };

    struct Person p1;
    memcpy(p1.name, "Nitin", sizeof("Nitin"));
    p1.id = 74;

    cout << "Printing p and p1 data..." << endl << "Check it out !! :P\n";
    cout << p.name << "\t" << p.id << "\n";
    cout << p1.name << "\t" << p1.id << "\n";
    return 0;
}
