#include <iostream>
using namespace std;

int main()
{
    int count;
    cout << "How many numbers would you like to have? ";
    cin >> count;

    for(int i=1;i<=count;i++)
    {
        if (!(i % 3))
            cout << "zip" << (!(i%7) ? " boing" : "") << endl;
        else if (!(i % 7))
            cout << "boing" << endl;
        else
            cout << i << endl;
    }

    return 0;
}
