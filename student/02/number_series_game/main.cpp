#include <iostream>
using namespace std;

int main()
{
    int count;
    cout << "How many numbers would you like to have? ";
    cin >> count;

    for(int i=1;i<=count;i++)
        cout << i << endl;

    return 0;
}
