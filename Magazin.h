#include "Comanda.h"

class Magazin {
    vector<Angajat*> angajati;
    priority_queue<Comanda> comenzi;

public:
    Magazin() = default;
    Magazin(vector<Angajat*>, priority_queue<Comanda>);
    Magazin(Angajat**, int, priority_queue<Comanda>);
};

// de facut verificare cu &in == &cin pentru toate citirile
// de terminat vector<Angahat*>, toate functiile necesare
// de terminat citirea pentru Comanda