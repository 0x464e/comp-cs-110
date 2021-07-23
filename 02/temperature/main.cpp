#include <iostream>

using namespace std;

int main()
{
    int temperature;
    cout << "Enter a temperature: ";
    cin >> temperature;

    cout << temperature << " degrees Celsius is " << temperature * 1.8 + 32 << " degrees Fahrenheit" << endl;
    cout << temperature << " degrees Fahrenheit is " << (temperature - 32) / 1.8 << " degrees Celsius" << endl;


    return 0;
}
