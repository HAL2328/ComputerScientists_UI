#ifndef COMPUTERS_H
#define COMPUTERS_H
#include "constants.h"

#include <vector>
#include <iostream>
#include "scientist.h"
using namespace std;

enum computer_type
{
    mechanical = 1,
    transistor,
    electronic
};

class Computers
{
public:
    Computers();
    Computers(string n, int y, bool b, int ct);
    Computers(string n, int y, bool b, int ct, int id);
    string get_name();
    int get_year();
    bool get_built();
    enum computer_type get_type();
    int get_id();
    void set_name(string n);
    void set_year(int y);
    void set_built(bool b);
    void set_type(enum computer_type ct);
    friend ostream& operator << (ostream& out, Computers comp);

private:
    string name;
    int year;
    bool built;
    enum computer_type comp_t;
    int id;
    vector<Scientist> connected_scientists;
};

#endif // COMPUTERS_H
