#ifndef SCIENTIST_SERVICE_H
#define SCIENTIST_SERVICE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "scientist.h"
#include "repository.h"

using namespace std;

class Scientist_service : public Scientist
{
public:
    Scientist_service();

    /* Tekur inn dálk til að raða eftir,
     * skilar röðuðum vektor af scientist
     */
    vector<Scientist> sort(QString order);

    // Tekur inn parametra fyrir leit, skilar vektor af scientist
    vector<Scientist> search(QString search_arg, QString column);

    // Sækir scientist eftir id númeri
    Scientist find_from_id(int scientist_id);

    /* Breytir entry í gagnagrunni. Column segir hvaða breytu skal
     * edita, insert geymir nýju upplýsingarnar, id segir hvaða scientist
     * á að breyta.
     */
    void edit_entry(QString column, QString insert, int id);

    // Les inn gögn frá notanda um nýjan scientist og skilar til grunnsins
    void read_input();

    /* Tekur id scientista og skilar vektor af nöfnum tölva sem tengjast
     * honum
     */
    vector <string> connected_computers(int id);
    friend class Interface;

    // Fær id scientista og eyðir viðkomandi scientist úr grunni
    void delete_id(int id);

private:
    Repository scientist_repo;
};

#endif // SCIENTIST_SERVICE_H
