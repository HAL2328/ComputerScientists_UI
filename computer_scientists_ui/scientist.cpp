#include <iostream>
#include "scientist.h"
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

Scientist::Scientist()
{
}

// Constructor með argumentum
Scientist::Scientist(string fn, string ln, bool g, QDate b, QDate d, bool l)
{
    first_name = fn;
    last_name = ln;
    gender = g;
    birth = b;
    death = d;
    living = l;
}

Scientist::Scientist(string fn, string ln, bool g, QDate b, QDate d, bool l, int id_num, bool act)
{
    first_name = fn;
    last_name = ln;
    gender = g;
    birth = b;
    death = d;
    living = l;
    id = id_num;
    active = act;
}

void Scientist::set_first(string n)
{
    first_name = n;
}

void Scientist::set_last(string n)
{
    last_name = n;
}

void Scientist::set_birth(QDate b)
{
    birth = b;
}

void Scientist::set_death(QDate d)
{
    death = d;
    if (death.isValid())
    {
        living = false;
    }
}

void Scientist::set_gender(bool g)
{
    gender = g;
}
void Scientist::set_living(bool a)
{
    living = a;
}

void Scientist::set_id(int idn)
{
    id = idn;
}

string Scientist::get_first()
{
    return first_name;
}
string Scientist::get_last()
{
    return last_name;
}
bool Scientist::get_gender()
{
    return gender;
}

QDate Scientist::get_birth()
{
    return birth;
}

QDate Scientist::get_death()
{
    return death;
}

bool Scientist::get_living()
{
    return living;
}

int Scientist::get_id()
{
    return id;
}

Scientist& Scientist::operator = (Scientist other)
{
    first_name = other.first_name;
    last_name = other.last_name;
    gender = other.gender;
    birth = other.birth;
    death = other.death;
    living = other.living;
    return *this;
}
// Operator overload til að prenta instance af klasanum
ostream& operator << (ostream& out, Scientist sc)
{
    int name_length = sc.first_name.size() + sc.last_name.size() +1;    //búa til pláss fyrir nafn

    out << sc.first_name << " " << sc.last_name;
    if (name_length < constants::MAX_NAME_LENGTH)  //Fyllir línuna ef nafnið er undir max_name_length
        {
            name_length = constants::MAX_NAME_LENGTH - name_length;
            out << string(name_length , ' ');
        }

    if (sc.gender)
    {

        out << "\tMale\t";
    }
    else
    {
        out << "\tFemale\t";
    }
    out << std::setfill('0') << std::setw(2) << sc.birth.day() << "/" << std::setfill('0') << std::setw(2) << sc.birth.month() << "/";
    out << sc.birth.year() << "\t";
    if (!sc.living)
    {
        out << std::setfill('0') << std::setw(2) << sc.death.day() << "/" << std::setfill('0') << std::setw(2) << sc.death.month() << "/";
        out << sc.death.year() << "\n";
    }
    else
    {
        out << sc.first_name << " is alive and well.\n";
    }
    return out;
}

void Scientist::add_computer(string n)
{
    computer_names.push_back(n);
}
