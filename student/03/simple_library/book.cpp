#include "book.hh"
#include <string>
#include <iostream>

using namespace std;

Book::Book(const string& author, const string& title):
    author_(author), title_(title), available_(true), loan_date_(Date()), return_date_(Date())
{

}

void Book::print() const
{
    cout << author_ << " : " << title_ << endl;
    if (available_)
        cout << "- available" << endl;
    else
    {
        cout << "- loaned: ";
        loan_date_.print();
        cout << "- to be returned: ";
        return_date_.print();
    }
}

void Book::loan(Date date)
{
    if (!available_)
    {
        cout << "Already loaned: cannot be loaned" << endl;
        return;
    }
    available_ = false;
    loan_date_ = date;
    date.advance(28);
    return_date_ = date;
}

void Book::give_back()
{
    available_ = true;
}

void Book::renew()
{
    if (available_)
        cout << "Not loaned: cannot be renewed" << endl;
    else
        return_date_.advance(28);
}
