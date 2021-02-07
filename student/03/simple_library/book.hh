#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include "date.hh"

using namespace std;

class Book
{

public:
    //Constructor
    Book(const string& author, const string& title);
    void print() const;
    void loan(Date date);
    void give_back();
    void renew();


private:
    string author_;
    string title_;
    bool available_;
    Date loan_date_;
    Date return_date_;
};

#endif // BOOK_HH
