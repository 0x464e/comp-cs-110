#include <iostream>
#include <string>
using namespace std;

int main()
{
    string enc_key;
    cout << "Enter the encryption key: ";
    cin >> enc_key;

    if (enc_key.length() != 26)
    {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }

    string used_chars;
    bool dupe_chars = false;

    for (size_t i = 0; i < enc_key.length(); i++)
    {
        char c = enc_key[i];
        if ('a' > c || 'z' < c)
        {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
        if(!dupe_chars)
        {
            if(used_chars.find(c)!=string::npos)
                    dupe_chars = true;
            used_chars += c;
        }
    }

    if (dupe_chars)
    {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    }

    string inp_string;
    cout << "Enter the text to be encrypted: ";
    cin >> inp_string;

    for (size_t i = 0; i < inp_string.length(); i++)
    {
        char c = inp_string[i];
        if ('a' > c || 'z' < c)
        {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }

    string enc_string;
    for(size_t i = 0; i < inp_string.length(); i++)
        enc_string += enc_key[inp_string[i] % 97];


    cout << "Encrypted text: " << enc_string << endl;

    return EXIT_SUCCESS;
}
