/* Introducing Vectors in C++ !

Sources:
http://www.cprogramming.com/tutorial/stl/vector.html
http://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4027/C-Tutorial-A-Beginners-Guide-to-stdvector-Part-1.htm

Let's take a look at several functions provided by the vector class:
unsigned int size();            Returns the number of elements in a vector
push_back(type element);        Adds an element to the end of a vector
bool empty();                   Returns true if the vector is empty
void clear();                   Erases all elements of the vector
type at(int n);                 Returns the element at index n, with bounds checking
begin
end
set
.
.
.
and much more...

also, there are several basic operators defined for the vector class:

=           Assignment replaces a vector's contents with the contents of another
==          An element by element comparison of two vectors
[]          Random access to an element of a vector (usage is similar to that
            of the operator with arrays.) Keep in mind that it does not provide
            bounds checking.

*/

#include <iostream>
#include <vector>

//using namespace std;
int main()
{
    /*
    vector <int> example;         //Vector to store integers
    example.push_back(3);         //Add 3 onto the vector
    example.push_back(10);        //Add 10 to the end
    example.push_back(33);        //Add 33 to the end
    for(int x=0; x<example.size(); x++)
    {
        cout<<example[x]<<" ";    //Should output: 3 10 33
    }
    if(!example.empty())          //Checks if empty
        example.clear();          //Clears vector
    vector <int> another_vector;  //Creates another vector to store integers
    another_vector.push_back(10); //Adds to end of vector
    example.push_back(10);        //Same
    if(example==another_vector)   //To show testing equality
    {
        example.push_back(20);
    }
    for(int y=0; y<example.size(); y++)
    {
        cout<<example[y]<<" ";    //Should output 10 20
    }
    */

    int arr[17];
    std::vector <int> varr;

    std::cout << "sizeof(arr) = " << sizeof(arr) << "\n";
    std::cout << "sizeof(varr) = " << sizeof(varr) << "\n";


    int i = 0;
    for(i = 0; i < sizeof(arr)/sizeof(int); i++)
    {
        arr[i] = i * 3;
        varr.push_back(i * 3);
    }

    std::cout << "sizeof(arr) = " << sizeof(arr) << "\n";
    std::cout << "sizeof(varr) = " << sizeof(varr) << "\n";

    std::cout << "arr[] = \n";
    for(i = 0; i < sizeof(arr)/sizeof(int); i++)
    {
        std::cout << arr[i] << ",";
    }

    std::cout << "\nvarr[] = \n";

    for(i = 0; i < varr.size(); i++)
    {
        std::cout << varr[i] << ",";
    }
    return 0;
}
