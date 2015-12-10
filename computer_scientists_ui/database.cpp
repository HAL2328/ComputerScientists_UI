#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <QString>
#include <QDate>
#include "database.h"
#include <fstream> 
#include <sstream>
#include "constants.h"

using namespace std;

Database::Database()
{
}

Database::Database(vector<Scientist>& d)
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
void Database::sort_name()
{
    sort(data.begin(), data.end(), name_order);
}

void Database::sort_birth()
{
    sort(data.begin(), data.end(), birth_order);
}

void Database::sort_death()
{
    sort(data.begin(), data.end(), death_order);
}

void Database::sort_gender()
{
    sort(data.begin(), data.end(), gender_order);
}

void Database::reverse_order()
{
    reverse(data.begin(), data.end());
}

// Les upplýsingar frá notanda
void Database::read_input()
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
    getline(cin, temp.first_name);
    cout << "Input last name: ";
    getline(cin, temp.last_name);

    do
    {
        cout << "Input gender (M/F): ";
        getline(cin, line);
        cgender = line[0];
        switch(tolower(cgender))
        {
            case 'm':
                temp.gender = true;
                valid = true;
                break;
            case 'f':
                temp.gender = false;
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
    temp.birth = in_date;

    do
    {
        cout << "Is this person living (y/n)?" << endl;
        getline(cin, line);
        answer = line[0];
        switch (tolower(answer))
        {
            case 'y':
                deceased = false;
                temp.living = true;
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
            else if (in_date < temp.birth) // fæðing ekki eftir dauða
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
    temp.death = in_date;
    data.push_back(temp);
}

void Database::read_file(string filename)
{
    Scientist temp;
    ifstream in_file;
    string line;
    char g;
    QDate birth, death;
    QString date, format;
    format = "d.M.yyyy";
    in_file.open(filename.c_str());
    if (in_file.fail())
    {
        cout << "Unable to open file" << endl;
    }
    else
    {
        cout << "File read." << endl;
    }
    while (getline(in_file, line))
    {
        temp.first_name = line;
        getline(in_file, line);
        temp.last_name = line;
        getline(in_file, line);
        date = QString::fromStdString(line);
        temp.birth = QDate::fromString(date, format);
        getline(in_file, line);
        date = QString::fromStdString(line);
        temp.death = QDate::fromString(date, format);
        // sé einstaklingur lifandi er dagsetning á forminu 0.0.0
        if (!temp.death.isValid())
        {
            temp.living = true;
        }
        else
        {
            temp.living = false;
        }
        getline(in_file, line);
        g = line[0];
        if (g == 'M' || g == 'm')
        {
            temp.gender = 1;
        }
        else
            temp.gender = 0;
        data.push_back(temp);
    }
    in_file.close();
}

void Database::print_to_file(string filename)
{
    ofstream out_file;
    out_file.open(filename.c_str());

    for (unsigned int i = 0; i < size(); i++)
    {
        out_file << data[i].get_first()<< endl;
        out_file << data[i].get_last() << endl;
        out_file << data[i].get_birth().day() << "." << data[i].get_birth().month();
        out_file << "." << data[i].get_birth().year() << endl;
        if (!living)
        {
            out_file << data[i].get_death().day() << "." << data[i].get_death().month() << ".";
            out_file << data[i].get_death().year() << endl;
        }
        else
        {
            out_file << "0.0.0" << endl;
        }
        if (data[i].get_gender())
            out_file << "M" << endl;
        else
            out_file << "F" << endl;
    }
    out_file.close();
}

unsigned int Database::size()
{
    return data.size();
}

ostream& operator << (ostream& out, Database d)
{
    for (unsigned int i = 0; i < d.size(); i++)
    {
        out << d.data[i]; // notar overload << virkjann í Scientist
    }
    return out;
}
