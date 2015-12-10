#include "computer_service.h"

Computer_service::Computer_service()
{
}

vector<Computers> Computer_service::sort(QString sort_order)
{
    QString command = QString(constants::COMPUTERS_ORDER.arg(sort_order));
    return computer_repo.open_computer_db(command);
}

vector<Computers> Computer_service::search(QString column, QString search_arg)
{
    QString command = QString(constants::COMPUTERS_SEARCH.arg(column).arg(search_arg));
    return computer_repo.open_computer_db(command);
}

void Computer_service::edit_entry (QString column, QString argument, int id)
{
    QString command = QString(constants::COMPUTERS_EDIT.arg(column).arg(argument).arg(id));
    computer_repo.edit_remove(command);
}

Computers Computer_service::from_id(int id)
{
    QString command = QString(constants::COMPUTER_FROM_ID.arg(id));
    return computer_repo.open_computer_db(command)[0];
}

void Computer_service::delete_id(int id)
{
    QString command = QString(constants::DELETE_COMPUTER.arg(id));
    computer_repo.edit_remove(command);
}

vector<string> Computer_service::connected_scientists(int id)
{
    QString command = QString(constants::SCIENTIST_JOIN.arg(id));
    vector<string> scientist_names = computer_repo.connected(command, "lastname");
    return scientist_names;
}

void Computer_service::add_connection(int sci_id, int comp_id)
{
    QString command = QString(constants::ADD_CONNECTION.arg(sci_id).arg(comp_id));
    computer_repo.edit_remove(command);
}

void Computer_service::read_input()
{
    string name;
    bool built = false;
    int year, ct;
    char test;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Was the computer built (y/n)?";
    cin >> test;
    if (test == 'y' || test == 'Y')
    {
        cout << "Enter year built: ";
        cin >> year;
        built = true;
    }
    else
    {
        year = 0;
    }
    cout << "Enter computer type (1 for mechanical, 2 for transistor, 3 for electronic): ";
    cin >> ct;
    Computers temp(name, year, built, ct);
    computer_repo.add_computer(temp);
}

vector<Scientist> Computer_service::connected_sci(int id)
{
    QString command = QString(constants::CONNECTED_SCIENTIST_ID.arg(id));
    return computer_repo.connected_to_delete(command);
}

void Computer_service::remove_connection(int scient_id, int comp_id)
{
    QString command = QString(constants::DELETE_CONNECTION.arg(scient_id).arg(comp_id));
    computer_repo.edit_remove(command);
}
