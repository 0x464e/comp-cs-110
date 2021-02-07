#include "player.hh"
#include <iostream>

Player::Player(const string &name):
    name_(name), points_(0)
{

}

string Player::get_name() const
{
    return name_;
}

void Player::add_points(const int& pts)
{
    points_ += pts;
    if (points_ > 50)
    {
        cout << name_ << " gets penalty points!" << endl;
        points_ = 25;
    }
}

int Player::get_points() const
{
    return points_;
}

bool Player::has_won() const
{
    return points_ == 50;
}
