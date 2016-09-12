#include <iostream>

void recurse(int depth = 0)
{
    if (depth >= 10)
        return;
    std::cout << depth << ", ";
    recurse(depth+1);
}

int main(int argc, char **argv)
{
    recurse();
	return 0;
}
