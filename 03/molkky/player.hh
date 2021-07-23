#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

using namespace std;

class Player
{
public:
    //Constructor
    Player(const string& name);
    string get_name() const;
    void add_points(const int& pts);
    int get_points() const;
    bool has_won() const;

private:
    string name_;
    int points_;
};

#endif // PLAYER_HH
