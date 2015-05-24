#include <iostream>
#include "testing.h"

using namespace std;

int main()
{
    if (testing())
        cout << "+";
    else
        cout << "-";
    return 0;
}
