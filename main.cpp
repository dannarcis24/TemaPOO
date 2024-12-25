#include "Options.h"
#include <windows.h>
#include <fstream>

inline void error() 
{
    cout<<"Optiune invalida!\n";
    system("pause"); 
}

inline void Option1(Store& m, bool& exit) {
    while(true)
    {
        system("cls");
        cout<<"     ROCK the SHOP\nGESTIUNEA ANGAJATILOR\n 1. Adaugare angajat\n 2. Stergere angajat\n"
            <<" 3. Modificarea numelui de familie al unui angajat\n 4. Afisare informatiilor unui angajat\n"
            <<" 5. Afisare informatiilor despre toti angajatii\n 6. Inapoi\n 7. Iesire\n\nOptiunea dvs. este: ";

        string option;
        getline(cin, option);

        try {
            switch(stoi(option)) {
                case 1: {
                    addEmployee(m);
                    break;
                }
                case 2: {
                    try{ m.employeeDel(searchID());}
                    catch(const exception& e) { cout<<e.what();}
                    break;
                }
                case 3: {
                    m.employeeSet(searchID(), name());
                    break;
                }
                case 4: {
                    writeEmployee(m);
                    break;
                }
                case 5: {
                    writeEmployee(m, true);
                    break;
                }
                case 6: return;
                case 7: {
                    exit = true;
                    return;
                }
                default: error();
            }
        } catch(const exception&) { error();}
    }
}

inline void Option2(Store& m, bool& exit) {
    while(true)
    {
        system("cls");
         cout<<"     ROCK the SHOP\nGESTIUNEA PRODUSELOR\n 1. Adaugare produs\n 2. Stergere produs\n"
            <<" 3. Modificarea stocului unui produs\n 4. Afisare informatiilor unui produs\n"
            <<" 5. Afisare informatiilor despre toate produselor din stoc\n 6. Inapoi\n 7. Iesire\n\nOptiunea dvs. este: ";

        string option;
        getline(cin, option);;

        try {
            switch(stoi(option)) {
                case 1: {
                    addProduct(m);
                    break;
                }
                case 2: {
                    try{ m.productDel(searchID());}
                    catch(const exception& e) { cout<<e.what();}
                    break;
                }
                case 3: {
                    m.productSet(searchID(), number());
                    break;
                }
                case 4: {
                    writeProducts(m);
                    break;
                }
                case 5: {
                    writeProducts(m, true);
                    break;
                }
                case 6: return;
                case 7: {
                    exit = true;
                    return;
                }
                default: error();
            }
        } catch(const exception& e) { error();}
    }
}

int main()
{  
    Store m;

    while(true)
    {
        system("cls");
        cout<<"     ROCK the SHOP\n1. Gestiunea angajatilor\n2. Gestiunea produselor\n"
            <<"3. Gestiunea comenzilor\n4. Rapoarte\n5. Iesire\n\nOptiunea dvs. este: ";
        
        string option;
        getline(cin, option);;

        bool exit = false;
        try {
            switch(stoi(option)) {
                case 1: {
                    Option1(m, exit);
                    break;
                }
                case 2: {
                    Option2(m, exit);
                    break;
                }
                case 3: {
                    managementOrders(m);
                    system("pause");
                    break;
                }
                case 4: {
                    // Option4(m, exit);
                    break;
                }
                case 5: {
                    exit = true;
                    break;
                }
                default: error();
            }
        } catch(const exception&) { error();}

        if(exit)
        {
            cout<<"Magazinul a dat faliment! :(";
            return 0;
        }
    }
}