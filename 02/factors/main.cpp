#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int dividend;
    cout << "Enter a positive number: ";
    cin >> dividend;

    if (dividend <= 0)
    {
        cout << "Only positive numbers accepted" << endl;
        return 0;
    }

    int root = sqrt(dividend);
    int f1 = root;
    int f2 = root + (root*root!=dividend);

    for(;;)
        if (!(dividend % f1))
            break;
        else
            f1--;

    for(;;)
        if (!(dividend % f2))
            break;
        else
            f2++;

    cout << dividend << " = " << f1 << " * " << f2 << endl;
    return 0;
}
