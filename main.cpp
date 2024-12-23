#include "Store.h"
#include <windows.h>

inline void Menu() {
    cout<<"     ROCK the SHOP\n1. Gestiunea angajatilor\n2. Gestiunea produselor\n"
        <<"3. Gestiunea comenzilor\n4. Rapoarte\n5. Iesire\n\nOptiunea dvs. este: ";
}

int main()
{  
    Store s;

    while(true)
    {
        system("cls");
        Menu();
        string option;
        getline(cin, option);;

        try {
            switch(stoi(option)) {
                case 1: {
                    // gestiune angajati
                    break;
                }
                case 2: {
                    // gestiune produse
                    break;
                }
                case 3: {
                    // gestiune comenzi
                    break;
                }
                case 4: {
                    // rapoarte
                    break;
                }
                case 5: {
                    cout<<"Pa-pa!\n";
                    break;
                }
                default: cout<<"Optiune invalida!\n";
            }
        } catch(const exception& e) { cout<<"optiune_invalida: !! optiunea aleasa nu exista !!\n";}

        system("pause");
    }

    return 0;
}