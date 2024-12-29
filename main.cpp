#include "Options.h"
#include <windows.h>

inline void wait() {
    cout<<"Apasati ENTER pentru a continua...";
    cin.get();
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
            if(option.size() != 1)
                throw invalid_argument("optiune invalida\n");
            
            switch(stoi(option)) {
                case 1: {
                    addEmployee(m);
                    break;
                }
                case 2: {
                    try{ m.employeeDel(searchID());}
                    catch(const exception& e) { cout<<e.what();}
                    cout<<"Stergerea a fost efectuata cu succes!\n\n";
                    break;
                }
                case 3: {
                    try{ m.employeeSet(searchID(), name());}
                    catch(const exception& e) { cout<<e.what();}
                    cout<<"Modificarea a fost efectuata cu succes!\n\n";
                    break;
                }
                case 4: {
                    try{ writeEmployee(m);}
                    catch(const exception& e) { cout<<e.what();}
                    break;
                }
                case 5: {
                    try{ writeEmployee(m, true);}
                    catch(const exception& e) { cout<<e.what();}
                    break;
                }
                case 6: return;
                case 7: {
                    exit = true;
                    return;
                }
                default: throw invalid_argument("optiune invalida\n");
            }
        } catch(const exception& e) { cout<<e.what();}

        wait();
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
            if(option.size() != 1)
                throw invalid_argument("optiune invalida\n");
            
            switch(stoi(option)) {
                case 1: {
                    addProduct(m);
                    break;
                }
                case 2: {
                    try{ m.productDel(searchID());}
                    catch(const exception& e) { cout<<e.what();}
                    cout<<"Stergerea a fost efectuata cu succes!\n\n";
                    break;
                }
                case 3: {
                    try{ m.productSet(searchID(), number());}
                    catch(const exception& e) { cout<<e.what();}
                    cout<<"Modificarea a fost efectuata cu succes!\n\n";
                    break;
                }
                case 4: {
                    try{ writeProducts(m);}
                    catch(const exception& e) { cout<<e.what();}
                    break;
                }
                case 5: {
                    try{ writeProducts(m, true);}
                    catch(const exception& e) { cout<<e.what();}
                    break;
                }
                case 6: return;
                case 7: {
                    exit = true;
                    return;
                }
                default: throw invalid_argument("optiune invalida\n");
            }
        } catch(const exception& e) { cout<<e.what();}

        wait();
    }
}

inline void Option4(Store& m, bool& exit) {
    while(true)
    {
        system("cls");
         cout<<"     ROCK the SHOP\nGENEREAREA RAPOARTELOR\n 1. Angajatul cu cele mai multe comenzi procesate\n"
            <<" 2. TOP 3angajati, care au gestionat cele mai valoroase comenzi\n 3. TOP 3angajati, care au cel mai mare salariu in luna curenta\n"
            <<" 4. Inapoi\n 5. Iesire\n\nOptiunea dvs. este: ";

        string option;
        getline(cin, option);;

        try {
            if(option.size() != 1)
                throw invalid_argument("optiune invalida\n");
            
            switch(stoi(option)) {
                case 1: {
                    m.writeMostOrders();
                    break;
                }
                case 2: {
                    m.writeMostExpensive();
                    break;
                }
                case 3: {
                    m.writeBigSalary();
                    break;
                }
                case 4: return;
                case 5: {
                    exit = true;
                    return;
                }
                default: throw invalid_argument("optiune invalida\n");
            }
        } catch(const exception& e) { cout<<e.what();}

        wait();
    }
}

int main()
{  
    Store m;

    while(true)
    {
        system("cls");
        cout<<"     ROCK the SHOP\n1. Gestiunea angajatilor\n2. Gestiunea produselor\n"
            <<"3. Gestiunea comenzilor\n4. Generarea rapoartelor\n5. Iesire\n\nOptiunea dvs. este: ";
        
        string option;
        getline(cin, option);;

        bool exit = false;
        try {
            if(option.size() != 1)
                throw invalid_argument("optiune invalida\n");
            
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
                    wait();
                    break;
                }
                case 4: {
                    Option4(m, exit);
                    break;
                }
                case 5: {
                    exit = true;
                    break;
                }
                default: throw invalid_argument("optiune invalida\n");
            }
        } catch(const exception& e) { cout<<e.what(); wait();}

        if(exit)
        {
            cout<<"Magazinul a dat faliment! :(";
            return 0;
        }
    }
}