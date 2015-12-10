#include "computers.h"
#include <string>


Computers::Computers()
{
}

Computers::Computers(string n, int y, bool b, int ct)
{
    name = n;
    year = y;
    built = b;
    comp_t = static_cast<computer_type>(ct);
}

Computers::Computers(string n, int y, bool b, int ct, int id)
{
    name = n;
    year = y;
    built = b;
    comp_t = static_cast<computer_type>(ct);
    this->id = id;
}

string Computers::get_name()
{
    return name;
}

int Computers::get_year()
{
    return year;
}

bool Computers::get_built()
{
    return built;
}

enum computer_type Computers::get_type()
{
    return comp_t;
}

int Computers::get_id()
{
    return id;
}

void Computers::set_name(string n)
{
    name = n;
}

void Computers::set_year(int y)
{
    year = y;
}

void Computers::set_built(bool b)
{
    built = b;
}

void Computers::set_type(computer_type ct)
{
    comp_t = ct;
}

ostream& operator << (ostream& out, Computers comp)
{
    int comp_name_length = comp.name.size();    //búa til pláss fyrir nafn

    out << comp.name;
    //Fyllir línuna ef nafnið er undir max_name_length
    if (comp_name_length < constants::MAX_COMP_NAME_LENGTH )
        {
            out << string(constants::MAX_COMP_NAME_LENGTH - comp_name_length , ' ');
        }
    if (comp.built)
    {
        out << comp.year << "\t\t";
    }
    else
    {
        out << "Not built\t";
    }
    if (comp.comp_t == 1)
    {
        out << "Mechanical";
    }
    else if (comp.comp_t == 2)
    {
        out << "Transistor";
    }
    else
    {
        out << "Electronic";
    }
    out << endl;
    return out;
}
