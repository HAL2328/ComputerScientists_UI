#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <QString>
#include <QDate>
#include "scientist_service.h"
#include <fstream> 
#include <sstream>


using namespace std;

Scientist_service::Scientist_service()
{
}

vector<Scientist> Scientist_service::sort(QString order)
{
    QString command = QString(constants::SCIENTISTS_ORDER.arg(order));
    return scientist_repo.open_scientist_db(command);
}

vector<Scientist> Scientist_service::search(QString search_arg, QString column)
{
    QString command = QString(constants::SEARCH_SCIENTIST_TEMPLATE.arg(column).arg(search_arg));
    return scientist_repo.open_scientist_db(command);
}

Scientist Scientist_service::find_from_id(int scientist_id)
{
    QString command = QString(constants::SCIENTIST_FROM_ID.arg(scientist_id));
    return scientist_repo.open_scientist_db(command)[0];
}

void Scientist_service::edit_entry(QString column, QString insert, int id)
{
    QString command = QString(constants::SCIENTIST_EDIT.arg(column).arg(insert).arg(id));
    scientist_repo.edit_remove(command);
}

void Scientist_service::delete_id(int id)
{
    QString command = QString(constants::DELETE_SCIENTIST.arg(id));
    scientist_repo.edit_remove(command);
}

// Les upplýsingar frá notanda
void Scientist_service::read_input()
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
    scientist_repo.add_scientist(temp);
}

vector <string> Scientist_service::connected_computers(int id)
{
    QString command = QString(constants::COMPUTER_JOIN.arg(id));
    vector<string> scientist_names = scientist_repo.connected(command, "name");
    return scientist_names;
}

