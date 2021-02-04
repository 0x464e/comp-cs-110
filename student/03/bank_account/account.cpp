#include "account.hh"
#include <iostream>

using namespace std;

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit), balance_(0)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(int limit)
{

}

void Account::save_money(int amount)
{
    balance_ += amount;
}

void Account::take_money(int amount)
{

}

void Account::transfer_to(Account& account, int amount)
{

}

void Account::print() const
{
    cout << owner_ << " : " << iban_ << " :" << balance_ << " euros" << endl;
}
