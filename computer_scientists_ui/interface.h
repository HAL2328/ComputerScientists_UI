#ifndef INTERFACE_H
#define INTERFACE_H

#include "constants.h"
#include "scientist_service.h"
#include "computer_service.h"
#include <iostream>
#include <string>


using namespace std;

class Interface
{
public:
    Interface();

    // Keyrir forritið, og birtir main menu
    void start_menu();

    // Birtingarmöguleikar fyrir lista af scientists/tölvum
    bool list_menu();
    void computer_list_menu();

    void clear_screen();

    /* Birtir valmöguleika fyrir leit, keyrir leit eftir input
     * frá notanda og sendir niðurstöður áfram þar sem unnið er
     * úr þeim
     */
    bool search_menu();
    void computer_search_menu();

    /* Birtir leitarniðurstöður og tekur við input um
     * hvernig á að vinna úr þeim
     */
    void found_menu(vector<Scientist> found);
    void found_computers_menu(vector<Computers> found);

    /* Birtir edit-möguleika, og leyfir notanda að vinna
     * úr þeim
     */
    void edit_menu(int edit_id);
    void edit_computers(int edit_id);

    void print_header();
    void print_header_computers();

    // Val um að setja inn/taka út tengingu tölvu við scientist
    void connect_scientist(int computer_id);
    void remove_connection(int comp_id);

    // spyr notanda í hvaða átt hann vill raða
    bool asc_desc();

    // Föll til að eyða tölvu/scientist
    bool edit_remove();
    bool edit_remove_comp();
private:
    Scientist_service scientist_service;
    Computer_service computer_service;
};


#endif // INTERFACE_H
