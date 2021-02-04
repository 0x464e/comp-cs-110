#include <iostream>
#include <random>
#include <string>

using namespace std;


void produce_random_numbers(uint lower, uint upper, uint seed_value)
{
    static default_random_engine gen(seed_value);
    static uniform_int_distribution<int> distr(lower, upper);
    
    cout << "Your drawn random number is " << distr(gen) << endl;
}

int main()
{
    uint lower_bound, upper_bound, seed_value;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;
    cout << "Enter a seed value: ";
    cin >> seed_value;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    char c;
    for (;;)
    {
        produce_random_numbers(lower_bound, upper_bound, seed_value);
        cout << "Press c to continue or q to quit: ";
        cin >> c;
        if (c == 'q')
            break;
        cout << endl;
    }

    return EXIT_SUCCESS;
}
