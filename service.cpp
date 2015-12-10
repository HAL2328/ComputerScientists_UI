#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <QString>
#include <QDate>
#include "service.h"
#include <fstream> 
#include <sstream>


using namespace std;

Service::Service()
{
}

Service::Service(vector<Scientist>& d)
{
    for (unsigned int i = 0; i < d.size(); i++)
    {
        data.push_back(d[i]);
    }
}

// Nokkur föll sem gera samanburð á tveimur elementum, skila true ef í réttri röð
bool name_order(Scientist n1, Scientist n2)
{
    bool order = false;
    if (n1.get_last() < n2.get_last())
    {
        order = true;
    }
    else if (n1.get_last() == n2.get_last() && n1.get_first() <= n2.get_first())
    {
        order = true;
    }
    return order;
}

bool birth_order(Scientist n1, Scientist n2)
{
    bool b = false;
    if (n1.get_birth() < n2.get_birth())
    {
        b = true;
    }
    return b;
}

bool death_order(Scientist n1, Scientist n2)
{
    bool d = false;
    if (n1.get_death() < n2.get_death())
    {
        d = true;
    }
    return d;
}

bool gender_order(Scientist n1, Scientist n2)
{
    bool g = false;
    if (n1.get_gender() < n2.get_gender())
    {
        g = true;
    }
    return g;
}



// Sort föll úr C++ library
vector<Scientist> Service::sort_name(bool asc)
{
    QString command;
    if (asc)
        command = "SELECT * FROM scientists ORDER BY lastname, firstname";
    else
        command = "SELECT * FROM scientists ORDER BY lastname DESC, firstname DESC";
    vector<Scientist> temp = scientist_repo.open_scientist_db(command);
    return temp;
}


vector<Scientist> Service::sort_birth(bool asc)
{
    QString command;
    if (asc)
        command = "SELECT * FROM scientists ORDER BY birth";
    else
        command = "SELECT * FROM scientists ORDER BY birth DESC";
    vector<Scientist> temp = scientist_repo.open_scientist_db(command);
    return temp;
}

vector<Scientist> Service::sort_death(bool asc)
{
    // Sorterar með alive fyrst til að lifandi raðist með nýlega látnum
    QString command;
    if (asc)
        command = "SELECT * FROM scientists ORDER BY alive, death";
    else
        command = "SELECT * FROM scientists ORDER BY alive DESC, death DESC";
    vector<Scientist> temp = scientist_repo.open_scientist_db(command);
    return temp;
}

vector<Scientist> Service::sort_gender(bool asc)
{
    QString command;
    if (asc)
        command = "SELECT * FROM scientists ORDER BY gender";
    else
        command = "SELECT * FROM scientists ORDER BY gender DESC";
    vector<Scientist> temp = scientist_repo.open_scientist_db(command);
    return temp;
}

vector<Scientist> Service::search(QString search_arg, QString column)
{
    QString command = QString(constants::SEARCH_SCIENTIST_TEMPLATE.arg(column).arg(search_arg));
    vector<Scientist> temp = scientist_repo.open_scientist_db(command);
    return temp;
}

void Service::reverse_order()
{
    reverse(data.begin(), data.end());
}

void Service::load_file(string file)
{
    data = scientist_repo.read_file(file);
}

bool Service::search_first(vector<int>& found_i, string n)
{
    bool found = false;
    for (unsigned int i = 0; i < data.size(); i++)
    {
        if (n == data[i].get_first())
        {
            found = true;
            found_i.push_back(i);
        }
    }
    return found;
}

bool Service::search_last(vector<int>& found_i, string n)
{
    bool found = false;
    for (unsigned int i = 0; i < data.size(); i++)
    {
        if (n == data[i].get_last())
        {
            found = true;
            found_i.push_back(i);
        }
    }
    return found;
}

bool Service::search_birth(vector<int>& found_i, QDate b)
{
    bool found = false;
    for (unsigned int i = 0; i < data.size(); i++)
    {
        if (b == data[i].get_birth())
        {
            found = true;
            found_i.push_back(i);
        }
    }
    return found;
}


bool Service::search_death(vector<int>& found_i, QDate d)
{
    bool found = false;
    for (unsigned int i = 0; i < data.size(); i++)
    {
        if (d == data[i].get_death())
        {
            found = true;
            found_i.push_back(i);
        }
    }
    return found;
}


// Les upplýsingar frá notanda
void Service::read_input()
{
    Scientist temp;
    char cgender, answer;
    string line;
    QDate in_date, current;
    current = QDate::currentDate(); // sækir daginn í dag í system-klukkuna
    QString date;
    bool valid_date, deceased, valid;
    cout << "Input first name(s): ";
    cin.ignore();                //varð að setja ignore til að miðjunafnið fari með. Ingvi
    getline(cin, line);
    temp.set_first(line);
    cout << "Input last name: ";
    getline(cin, line);
    temp.set_last(line);

    do
    {
        cout << "Input gender (M/F): ";
        getline(cin, line);
        cgender = line[0];
        switch(tolower(cgender))
        {
            case 'm':
                temp.set_gender(true);
                valid = true;
                break;
            case 'f':
                temp.set_gender(false);
                valid = true;
                break;
            default:
                cout << "Invalid gender. Please correct." << endl;
                break;
        }
    } while (!valid);
    do
    {
        cout << "Input date of birth (dd/mm/yyyy): ";
        getline(cin, line);
        date = QString::fromStdString(line);    // breytir innlestri í QString
        in_date = QDate::fromString(date, constants::DATE_FORMAT);  // innlestur => dags.
        valid_date = in_date.isValid();
        if(!valid_date)
        {
            cout << "Date is not valid." << endl;
        }
        else if (current < in_date)
        {
            cout << "Date of birth after current date. Please correct" << endl;
            valid_date = false;
        }
    } while (!valid_date);
    temp.set_birth(in_date);

    do
    {
        cout << "Is this person living (y/n)?" << endl;
        getline(cin, line);
        answer = line[0];
        switch (tolower(answer))
        {
            case 'y':
                deceased = false;
                temp.set_living(true);
            break;
            case 'n':
                deceased = true;
            break;
            default:
            break;
        }
    } while ( !(tolower(answer) == 'y' || tolower(answer) == 'n'));
    if (deceased)
    {
        cin.ignore();  // grípur newline á undan
        do
        {
            cout << "Input date of death (dd/mm/yyyy): ";
            getline(cin, line);
            date = QString::fromStdString(line); // breytir innlestri í QString
            in_date = QDate::fromString(date, constants::DATE_FORMAT); // breytir innlestri í dags.
            valid_date = in_date.isValid();  // testar hvort dagsetning sé gild
            if(!valid_date)
            {
                cout << "Date is not valid." << endl;
            }
            else if (in_date < temp.get_birth()) // fæðing ekki eftir dauða
            {
                cout << "Date of death before date of birth. Please correct." << endl;
                valid_date = false;
            }
            else if (current < in_date)
            {
                cout << "Date of death after today's date. Please correct." << endl;
                valid_date = false;
            }
        } while (!valid_date);
    }
    if (!deceased)
    {
        in_date.setDate(0, 0, 0);
    }
    temp.set_death(in_date);
    data.push_back(temp);
}

void Service::save_file(string filename)
{
    scientist_repo.print_to_file(filename, data);
}

unsigned int Service::size()
{
    return data.size();
}

ostream& operator << (ostream& out, Service d)
{
    for (unsigned int i = 0; i < d.size(); i++)
    {
        out << d.data[i]; // notar overload << virkjann í Scientist
    }
    return out;
}

