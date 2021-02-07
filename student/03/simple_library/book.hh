#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include "date.hh"

using namespace std;

class Book
{

public:
    //Constructor
    Book(const string& Author, const string& Title);
    void print();
    void loan(const Date& date);
    void give_back();
    void renew();


private:
    string Author_;
    string Title_;
};

#endif // BOOK_HH
