#include "interface.h"
#include <stdlib.h>



Interface::Interface()
{
}

/* Bool breytan quit er false á meðan ekki er búið að velja quit möguleikann
 * Exit bool breytan tekur gildi úr föllunum fyrir undirvalmyndir, þau skila
 * false ef ekki er búið að velja exit inni í þeim, og þær undirvalmyndir keyra
 * þá aftur.
 */
void Interface::start_menu()
{
    int selection = 0;
    bool quit, exit;
    // tempbreyta til að prófa útprent
    vector<Computers> temp;


    do
    {
        cout << endl;
        cout << "\n- Main menu ";
        cout << constants::MENU_DELIMITER << endl;
        cout << "1. Add Scientists to list\t";
        cout << "4. Display list of computers\t";
        cout << "0. Quit" << endl;
        cout << "2. Display list of scientists\t";
        cout << "5. Add computer" << endl;
        cout << "3. Search scientists\t\t";
        cout << "6. Search computers" << endl;

        cout << endl;
        cout << constants::SELECTION_PROMPT;
        cin >> selection;

        switch (selection)
        {
        case 1:
            clear_screen();
            scientist_service.read_input();
            clear_screen();
            break;
        case 2:
            clear_screen();
            do
            {
                exit = list_menu();
            } while (!exit);
            quit = false;
            break;
        case 3:
            clear_screen();
            do
            {
                exit = search_menu();
            } while (!exit);
            quit = false;
            break;
        case 4:
            clear_screen();
            computer_list_menu();
            quit = false;
            break;
        case 5:
            clear_screen();
            computer_service.read_input();
            clear_screen();
            quit = false;
            break;
        case 6:
            clear_screen();
            computer_search_menu();
            quit = false;
        break;
        case 0:
            quit = true;
            break;
        default:
            clear_screen();
            cout << endl;
            cout << selection << " is not a valid menu item.\n";
            quit = false;
            break;
        }
    } while (!quit);
}

bool Interface::list_menu()
{
    bool exit = false;
    bool asc;
    int select;
    vector<Scientist> data;

    cout << "\n- List of scientists ";
    cout << constants::MENU_DELIMITER << endl;
    cout << "1. Sort list by name\t\t";
    cout << "4. Sort list by gender\t";
    cout << "0. Main menu" << endl;
    cout << "2. Sort list by date of birth\t";
    cout << "5. Remove/delete entry" << endl;
    cout << "3. Sort list by date of death" << endl;
    cout << constants::SELECTION_PROMPT;
    cin >> select;
    switch(select)
    {
        case 1:
            clear_screen();
            asc = asc_desc();
            if (asc)
            {
                data = scientist_service.sort("lastname, firstname");
            }
            else
                data = scientist_service.sort("lastname DESC, firstname DESC");
            break;
        case 2:
        clear_screen();
            if ( (asc = asc_desc()) )
            {
            data = scientist_service.sort("birth");
            }
            else
                data = scientist_service.sort("birth DESC");

            break;
        case 3:
        clear_screen();
            if ((asc = asc_desc()))
            {
            data = scientist_service.sort("death");
            }
            else
                data = scientist_service.sort("death DESC");

            break;
        case 4:
        clear_screen();
            if ((asc = asc_desc()))
            {
            data = scientist_service.sort("gender");
            }
            else
                data = scientist_service.sort("gender DESC");

            break;
        case 5:
        clear_screen();
             edit_remove();
        case 0:
        clear_screen();
            exit = true;
            break;
        default:
        clear_screen();
            cout << select << " is not a valid menu item." << endl;
            break;
    }
    if (!exit)
    {
        print_header();
        for (unsigned int i = 0; i < data.size(); i++)
        {
            cout << data[i];
            vector<string> connected = scientist_service.connected_computers(data[i].get_id());
            if (!connected.empty())
            {
                cout << "\tDesigned: ";
                for (int j = 0; j < (int) connected.size(); j++)
                {
                    cout << connected[j];
                    if (j < ((int) connected.size()) - 2)
                    {
                        cout << ", ";
                    }
                    else if (j == ((int) connected.size()) - 2)
                    {
                        cout << " & ";
                    }
                }
                cout << endl;
            }
        }
    }
    return exit;
}

void Interface::computer_list_menu()
{
    bool exit = false;
    do
    {
        bool asc;
        int select;
        vector<Computers> data;
        cout << "\n- List of computers ";
        cout << constants::MENU_DELIMITER << endl;
        cout << "1. Sort list by name\t\t";
        cout << "3. Sort list by type\t\t";
        cout << "0. Main menu" << endl;
        cout << "2. Sort list by date built\t";
        cout << "4. Remove/delete entry" << endl;


        cout << endl;
        cout << constants::SELECTION_PROMPT;
        cin >> select;

        switch(select)
        {
            case 1:
                clear_screen();
                asc = asc_desc();
                if (asc)
                {
                    data = computer_service.sort("name");
                }
                else
                    data = computer_service.sort("name DESC");
                break;
            case 2:
                clear_screen();
                if ( (asc = asc_desc()) )
                {
                data = computer_service.sort("built_year");
                }
                else
                    data = computer_service.sort("built_year DESC");
                break;
            case 3:
                clear_screen();
                if ((asc = asc_desc()))
                {
                data = computer_service.sort("type");
                }
                else
                    data = computer_service.sort("type DESC");
                break;
            case 4:
                clear_screen();
                edit_remove_comp();                                                      //kallað á remove
            case 0:
                clear_screen();
                exit = true;
                break;
            default:
                clear_screen();
                cout << select << " is not a valid menu item." << endl;
                break;
        }
        if (!exit)
        {
            print_header_computers();
            for (unsigned int i = 0; i < data.size(); i++)
            {
                vector<string> connected = computer_service.connected_scientists(data[i].get_id());
                cout << data[i];
                cout << "\tDesigned by: ";
                for (int j = 0; j < (int) connected.size(); j++)
                {
                    cout << connected[j];
                    if (j < ((int) connected.size()) - 2)
                    {
                        cout << ", ";
                    }
                    else if (j == ((int) connected.size()) - 2)
                    {
                        cout << " & ";
                    }
                }
                cout << endl;
            }
        }
    } while (!exit);
}

bool Interface::search_menu()
{
    int select;
    string name, line;
    bool found;
    bool exit = false;
    QDate sdate;
    QString date, name_search;
    vector<int> found_index;
    vector<Scientist> found_scientists;

    cout << "\n- Search menu ";
    cout << constants::MENU_DELIMITER << endl;
    cout << "1. Search by first name\t\t";
    cout << "3. Search by date of birth\t";
    cout << "0. Main menu" << endl;
    cout << "2. Search by last name\t\t";
    cout << "4. Search by date of death" << endl;
    cout << "Enter selection: ";
    cout << endl;
    cin >> select;
    switch (select)
    {
        case 1:
            clear_screen();
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            name_search = QString::fromStdString(name);
            found_scientists = scientist_service.search(name_search, "firstname");

            if (!found_scientists.empty())
            {
                found = true;
            }
            else
                found = false;
            exit = true;
            break;
        case 2:
            clear_screen();
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            name_search = QString::fromStdString(name);
            found_scientists = scientist_service.search(name_search, "lastname");
            if (!found_scientists.empty())
            {
                found = true;
            }
            else
                found = false;
                exit = true;
            break;
        case 3:
            clear_screen();
            cout << "Enter date of birth 'yyyy-mm-dd' (month/day optional): ";
            cin.ignore();
            getline(cin, line);
            date = QString::fromStdString(line);
            found_scientists = scientist_service.search(date, "birth");
            if (!found_scientists.empty())
            {
                found = true;
            }
            else
            {
                found = false;
            }
            exit = true;
            break;
        case 4:
            clear_screen();
            cout << "Enter date of death 'yyyy-mm-dd' (month/day optional): ";
            cin.ignore();
            getline(cin, line);
            date = QString::fromStdString(line);
            found_scientists = scientist_service.search(date, "death");
            if (!found_scientists.empty())
            {
                found = true;

            }
            else
            {
                found = false;
            }
            exit = true;
            break;
        case 0:
            clear_screen();
            exit = true;
            found = true;
            return exit;
        default:
            clear_screen();
            cout << constants::SELECTION_NOT_VALID << endl;
            found = false;
            break;
    }
    if (found)
    {
        found_menu(found_scientists);
        exit = false;
    }
    if (!found && exit) // Val löglegt en ekkert fundið
    {
        cout << "No entries found." << endl;
        exit = false;
        char adding;
        bool legal_choice;
        do
        {
            cout << "Do you wish to add this person to the list of computer scientists(y/n)? " << endl;
            getline(cin, line);
            adding = line[0];
            if (tolower(adding) == 'y')
            {
                scientist_service.read_input();
                clear_screen();
                exit = true;
                legal_choice = true;
            }
            else if (adding == 'n' || adding == 'N')
            {
                exit = true;
                legal_choice = true;
            }
            else
            {
                cout << constants::SELECTION_NOT_VALID << endl;
                legal_choice = false;
            }
            } while (!legal_choice);
    }
    return exit;
}

void Interface::computer_search_menu()
{
    bool exit = false;
    do
    {
        int select;
        string name;
        int year, type;
        QString search_term;
        vector<Computers> found_computers;

        cout << "\n- Search computer ";
        cout << constants::MENU_DELIMITER << endl;
        cout << "1. Search by name\t\t";
        cout << "3. Search by type\t\t";
        cout << "0. Main menu" << endl;
        cout << "2. Search by year built" << endl;
        cout << endl;
        cout << constants::SELECTION_PROMPT;
        cin >> select;
        switch (select)
        {
            case 1:
                clear_screen();
                cout << "Enter name: ";
                cin.ignore();
                getline (cin, name);
                search_term = QString::fromStdString(name);
                found_computers = computer_service.search("name", search_term);
            break;
            case 2:
                clear_screen();
                cout << "Enter year: ";
                cin >> year;
                search_term = QString::number(year);
                found_computers = computer_service.search("built_year", search_term);
            break;
            case 3:
                clear_screen();
                cout << "Choose search term." << endl;
                cout << "(1 for mechanical, 2 for transistor, 3 for electronic): ";
                cin >> type;
                search_term = QString::number(type);
                found_computers = computer_service.search("type", search_term);
            break;
            case 0:
                clear_screen();
                exit = true;
            break;
            default:
                clear_screen();
                cout << constants::SELECTION_NOT_VALID;
            break;
        }
        if (!found_computers.empty())
        {
           found_computers_menu(found_computers);
        }
        else
        {
            cout << "No entries found. Search again?" << endl;
        }
    } while (!exit);
}

void Interface::found_menu(vector<Scientist> found)
{
    int select;
    bool valid;
    cout << constants::FOUND << endl;
    cout << constants::MENU_DELIMITER << endl;
    print_header();
    for (unsigned int i = 0; i < found.size(); i++)
    {
        cout << "Entry " << i + 1 << ":" << endl;
        cout << found[i];
        vector<string> connected = scientist_service.connected_computers(found[i].get_id());
        if (!connected.empty())
        {
            cout << "\tDesigned: ";
        for (int j = 0; j < (int) connected.size(); j++)
        {
            cout << connected[j];
            if (j < ((int) connected.size()) - 2)
            {
                cout << ", ";
            }
            else if (j == ((int) connected.size()) - 2)
            {
                cout << " & ";
            }
        }
        cout << endl;
        }
        cout << endl;
    }
    cout << "\n- Edit/remove ";
    cout << constants::MENU_DELIMITER << endl;
    cout << "1. Edit entry\t\t\t";
    cout << "2. Remove entry\t\t\t";
    cout << "0. Search menu" << endl;
    cout << endl;
    cout << constants::SELECTION_PROMPT;
    cin >> select;
    switch (select)
    {
        case 1:
            do
            {
                cout << "Choice entry to edit (0 to cancel): ";
                cin >> select;
                clear_screen();
                if(select > 0 && select <= (int) found.size())
                {
                    edit_menu(found[select - 1].get_id());
                    valid = true;
                }
                else if (select == 0)
                {
                    valid = true;
                }
                else
                {
                    cout << constants::SELECTION_NOT_VALID << endl;
                    valid = false;
                }
            } while (!valid);
            break;
        case 2:
            do
            {
                cout << "Choose entry to delete (0 to cancel): ";
                cin >> select;
                clear_screen();
                if (select > 0 && select <= (int) found.size())
                {
                    valid = true;
                    scientist_service.edit_entry("active", "0", found[select - 1].get_id());
                }
                else if (select == 0)
                {
                    valid = true;
                }
                else
                    valid = false;
            } while (!valid);
            break;
        case 0:
            clear_screen();
            valid = true;
            break;
        default:
            clear_screen();
            valid = false;
            break;
    }
    if (!valid)
    {
        cout << constants::SELECTION_NOT_VALID << endl;
        found_menu(found);
    }
}

void Interface::found_computers_menu(vector<Computers> found)
{
    int select;
    bool valid;
    cout << constants::FOUND << endl;
    cout << constants::MENU_DELIMITER << endl;
    for (unsigned int i = 0; i < found.size(); i++)
    {
        cout << "Entry " << i + 1 << ":" << endl;
        cout << found[i];
        vector<string> connected = computer_service.connected_scientists(found[i].get_id());
        cout << "\tDesigned by: ";
        for (int j = 0; j < (int) connected.size(); j++)
        {
            cout << connected[j];
            if (j < ((int) connected.size()) - 2)
            {
                cout << ", ";
            }
            else if (j == ((int) connected.size()) - 2)
            {
                cout << " & ";
            }
        }
        cout << endl;
    }
    cout << "\n- Edit/remove ";
    cout << constants::MENU_DELIMITER << endl;
    cout << "1. Edit entry\t\t\t";
    cout << "2. Remove entry\t\t\t";
    cout << "0. Search menu" << endl;
    cout << constants::SELECTION_PROMPT;
    cin >> select;
    switch (select)
    {
        case 1:
            do
            {
                cout << "Choose entry to edit (0 to cancel): ";
                cin >> select;
                if(select > 0 && select <= (int) found.size())
                {
                    edit_computers(found[select - 1].get_id());
                    valid = true;
                }
                else if (select == 0)
                {
                    valid = true;
                }
                else
                {
                    cout << constants::SELECTION_NOT_VALID << endl;
                    valid = false;
                }
            } while (!valid);
            break;
        case 2:
            do
            {
                cout << "Choose entry to delete (0 to cancel): ";
                cin >> select;
                if (select > 0 && select <= (int) found.size())
                {
                    valid = true;
                    computer_service.delete_id(found[select - 1].get_id());
                }
                else if (select == 0)
                {
                    valid = true;
                }
                else
                {
                    valid = false;
                    cout << constants::SELECTION_NOT_VALID << endl;
                }
            } while (!valid);
            break;
        case 0:
            clear_screen();
            valid = true;
            break;
        default:
            clear_screen();
            valid = false;
            break;
    }
    if (!valid)
    {
        cout << constants::SELECTION_NOT_VALID << endl;
        found_computers_menu(found);
    }
}


void Interface::edit_menu(int edit_id)
{
    int select;
    string line, n;
    char g;
    QString date, name;
    QDate b, d, current;
    current = QDate::currentDate();
    bool exit = false;
    cout << "\n- Edit scientist ";
    cout << constants::MENU_DELIMITER << endl;
    cout << scientist_service.find_from_id(edit_id);
    cout << "1. Edit first name" << endl;
    cout << "2. Edit last name" << endl;
    cout << "3. Edit gender" << endl;
    cout << "4. Edit date of birth" << endl;
    cout << "5. Edit date of death" << endl;
    cout << "0. Search menu" << endl;
    cout << endl;
    cout << constants::SELECTION_PROMPT;
    cin >> select;
    switch (select)
    {
        case 1:
            clear_screen();
            cout << "Enter new first name: ";
            cin.ignore();
            getline(cin, n);
            scientist_service.edit_entry("firstname", QString::fromStdString(n), edit_id);
            break;
        case 2:
            clear_screen();
            cout << "Enter new last name: ";
            cin.ignore();
            getline(cin, n);
            scientist_service.edit_entry("lastname", QString::fromStdString(n), edit_id);
            break;
        case 3:
            clear_screen();
            cout << "Enter gender: ";
            cin.ignore();
            getline(cin, line);
            g = line[0];
            if (g == 'm' || g == 'M')
            {
                scientist_service.edit_entry("gender", "1", edit_id);
            }

            else if (g == 'f' || g == 'F')
                scientist_service.edit_entry("gender", "0", edit_id);
            else
                cout << "Not a valid gender." << endl;
            break;
        case 4:
            clear_screen();
            cout << "Enter date of birth (dd/mm/yyyy): ";
            cin.ignore();
            getline(cin, line);
            date = QString::fromStdString(line); // breytir inputinu í QString
            b = QDate::fromString(date, constants::DATE_FORMAT); // breytir inputi í QDate
            date = b.toString(constants::IMPORT_DATE_FORMAT);
            if (!b.isValid())
            {
                cout << "Not a valid date." << endl;
            }
            else if (b > scientist_service.find_from_id(edit_id).get_death())
                cout << "Date of birth after date of death. Please correct." << endl;
            else if (current < b)
            {
                cout << "Date of birth after current date. Please correct." << endl;
            }
            else
            {
                scientist_service.edit_entry("birth", date, edit_id);
            }
            break;
        case 5:
            clear_screen();
            cout << "Enter date of death (dd/mm/yyyy): ";
            cin.ignore();
            getline(cin, line);
            date = QString::fromStdString(line); // breytir inputinu í QString
            d = QDate::fromString(date, constants::DATE_FORMAT); // breytir inputi í QDate
            date = d.toString(constants::IMPORT_DATE_FORMAT);

            if (!d.isValid())
            {
                cout << "Not a valid date." << endl;
            }
            else if (d < scientist_service.find_from_id(edit_id).get_birth())
                cout << "Date of death before date of birth. Please correct." << endl;
            else if (current < d)
            {
                cout << "Date of death after current date. Please correct." << endl;
            }
            else
            {
                scientist_service.edit_entry("death", date, edit_id);
            }
            break;
        case 0:
            clear_screen();
            exit = true;
            break;
        default:
            clear_screen();
            cout << constants::SELECTION_NOT_VALID << endl;
            break;
    }
    if (!exit)
    {
        edit_menu(edit_id);
    }
}

void Interface::edit_computers(int edit_id)
{
    int select;
    string line;
    bool exit = false;
    int type;
    QString search_term;
    vector<Scientist> temp;

    cout << "\n- Edit computer ";
    cout << constants::MENU_DELIMITER << endl;
    cout << "1. Edit name" << endl;
    cout << "2. Edit year built" << endl;
    cout << "3. Edit type" << endl;
    cout << "4. Add scientist connection" << endl;
    cout << "5. Remove scientist connection" << endl;
    cout << "0. Search menu" << endl;
    cout << constants::SELECTION_PROMPT;
    cin >> select;
    switch (select)
    {
        case 1:
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, line);
            computer_service.edit_entry("name", QString::fromStdString(line), edit_id);
            break;
        case 2:
            cout << "Enter year: ";
            cin.ignore();
            getline(cin, line);
            computer_service.edit_entry("built_year", QString::fromStdString(line), edit_id);
            break;
        case 3:
            cout << "Enter type." << endl;
            cout << "(1 for mechanical, 2 for transistor, 3 for electronic): ";
            cin >> type;
            if (type == 1)
            {
                computer_service.edit_entry("type", "1", edit_id);
            }

            else if (type == 2)
            {
                computer_service.edit_entry("type", "2", edit_id);
            }
            else if (type == 3)
            {
                computer_service.edit_entry("type", "3", edit_id);
            }
            else
                cout << "Not a valid type." << endl;
            break;
        case 4:
            connect_scientist(edit_id);
            break;
        case 5:
            remove_connection(edit_id);
            break;
        case 0:
            clear_screen();
            exit = true;
            break;
        default:
            clear_screen();
            cout << constants::SELECTION_NOT_VALID << endl;
            break;
    }
    if (!exit)
    {
        edit_computers(edit_id);
    }
}

void Interface::print_header()
{
    cout << "Name" << string(constants::MAX_NAME_LENGTH , ' ') << "Gender\tDoB\t\tDoD\n";
    cout << constants::MENU_DELIMITER << endl;
}

void Interface::print_header_computers()
{

    cout << "Name" << string(constants::MAX_COMP_NAME_LENGTH - 4, ' ') << "Year\t\tType\n";      //-4 vegna "name" í header
    cout << constants::MENU_DELIMITER << endl;
}

bool Interface::asc_desc()
{
    bool asc, valid;
    string command;
    do
    {
        cout << "\n- Asc-/Descending ";
        cout << constants::MENU_DELIMITER;
        int command = 0;
        cout << "\n1. Ascending\t";
        cout << "2. Descending" << endl;
        cout << constants::SELECTION_PROMPT;
        cin >> command;
        cout << endl;

        switch (command)                    //Val fyrir Ascending/Descending
        {
            case 1:
                clear_screen();
                asc = true;
                valid = true;
            break;

            case 2:
                clear_screen();
                asc = false;
                valid = true;
            break;

            default:
                clear_screen();
                cout << constants::SELECTION_NOT_VALID << endl;
                valid = false;

        }
    } while (!valid);
    return asc;
}


void Interface::connect_scientist(int computer_id)
{
    string line;
    QString search_term;
    int scientist_id;
    int index;
    bool valid = true;
    cout << "Enter last name of the scientist to connect: ";
    cin >> line;
    search_term = QString::fromStdString(line);
    vector<Scientist> temp = scientist_service.search(search_term, "lastname");
    cout << constants::FOUND;
    for (unsigned int i = 0; i < (temp.size()); i++)
    {
        cout << "Entry " << i + 1 << ": " << temp[0].get_last() << endl;
    }
    do
    {
        cout << endl << "Choose scientist to connect: ";
        cin >> index;
        if(index < 0 || index > (int) temp.size())
        {
            cout << constants::SELECTION_NOT_VALID << endl;
            valid = false;
        }
        else
        {
            valid = true;
            scientist_id = temp[index - 1].get_id();
        }
    } while (!valid);
    computer_service.add_connection(scientist_id, computer_id);
}

void Interface::remove_connection(int comp_id)
{
    vector<Scientist> temp;
    int select, scientist_id;
    temp = computer_service.connected_sci(comp_id);
    cout << "Connected scientists: " << endl;
    for (unsigned int i = 0; i < temp.size(); i++)
    {
        cout << i + 1 << ". " << temp[i].get_last() << endl;
    }
    cout << "Select connection to remove: ";
    cin >> select;
    scientist_id = temp[select - 1].get_id();
    computer_service.remove_connection(scientist_id, comp_id);
}

void Interface::clear_screen()
{
    #ifdef _WIN32
        system("CLS");
    #else
        system("CLEAR");
    #endif

}

bool Interface::edit_remove()
{
    vector <Scientist> d;
    int remove;
    int counter = 1;
    int id_del;
    cout << "Id  ";

    print_header();
    d = scientist_service.sort("lastname, firstname");
    for(unsigned long i = 0; i < d.size(); i++)
    {
        cout << counter++;
        if (counter < 11)
            cout << "   ";
        else (cout << "  ");
        cout << d[i];
    }
    cout << endl;
    cout << "Choose the ID of the scientist you wish to remove from the list (0 to cancel): ";
    cin >> remove;
    if(remove <= 0)
    {
        cout << endl;
        cout << "No scientist has the ID-number: " << remove << endl;
        return false;
    }
    else
    {
        id_del = d[remove - 1].get_id();
        scientist_service.delete_id(id_del);
        cout << "Entry removed." << endl;
        return true;
    }
    return true;
}

bool Interface::edit_remove_comp()
{
    vector <Computers> d;
    int remove;
    int counter = 1;
    int id_del;
    cout << "Id  ";

    print_header_computers();
    d = computer_service.sort("name");
    for(unsigned long i = 0; i < d.size(); i++)
    {
        cout << counter++;
        if (counter < 11)
            cout << "   ";
        else (cout << "  ");
        cout << d[i];
    }
    cout << endl;
    cout << "Choose the ID of the computer you wish to remove from the list (0 to cancel): ";
    cin >> remove;
    if(remove <= 0)
    {
        cout << endl;
        cout << "No scientist has the ID-number: " << remove << endl;
        return false;
    }
    else
    {
        id_del = d[remove - 1].get_id();
        computer_service.delete_id(id_del);
        cout << "Entry removed." << endl;
        return true;
    }
    return true;
}
