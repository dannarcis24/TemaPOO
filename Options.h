#include "Store.h"

// operator de citire pentru comenzi
// feature: afisarea in fisier sa fie facuta doar in excell, e mai frumos XP

/* FUNCTII PENTRU MODULARIZARE */
int number();
int number(ifstream&);
const string searchID();
const string name();

/* FUNCTII PENTRU GESTIUNEA ANGAJATILOR */
template<class T>
void readEmployee(Store& m)
{
    unsigned int nr = number();
    
    for(register int i = 0; i < nr; i++)
    {
        Employee* elem = new T;
        try{
            cin>>elem;

            if(typeid(T) == typeid(OrderOperator) && elem->position() != "operator comenzi")
                throw DynamicException("pozitie_invalida", "!! pentru a retine un manager sau un asistent, trebuie sa folositi tipul Employee !!\n\n");
            if(typeid(T) == typeid(Employee) && elem->position() == "operator comenzi")
                throw DynamicException("pozitie_invalida", "!! pentru a retine un operator de comenzi, trebuie sa folositi tipul OrderOperator !!\n\n");
        } catch(const exception& e) { 
            delete elem; 
            cout<<e.what(); 
            i--;
            continue;
        } 

        m.employeeAdd(elem);
    }
}
void readEmployeeFromFile(Store&, ifstream&);
void addEmployee(Store&);
void writeEmployee(Store&, bool = false);

/* FUNCTII PENTRU GESTIUNEA PRODUSELOR */
template<class T>
void readProduct(Store& m)
{
    unsigned int nr = number();
    
    for(register int i = 0; i < nr; i++)
    {
        Product* elem = new T;
        try{ cin>>elem;} 
        catch(const exception& e) { 
            delete elem; 
            cout<<e.what(); 
            i--;
            continue;
        }

        m.productAdd(elem);
    }
}
void readProductFromFile(Store&, ifstream&);
void addProduct(Store&);
void writeProducts(Store&, bool = false);

/* FUNCTII PENTRU GESTIUNEA COMENZILOR */
vector<Order*> readOrders(istream&);
void managementOrders(Store&);