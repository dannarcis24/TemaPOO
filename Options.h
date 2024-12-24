#include "Store.h"

/* FUNCTII PENTRU MODULARIZARE */
int number();
int number(ifstream&);
const string searchID();
const string name();

/* FUNCTII PENTRU GESTIUNEA ANGAJATILOR */
template<class T>
void readEmployee(Store& m, istream& in)
{
    unsigned int nr = (&in == &cin ? number() : number(dynamic_cast<ifstream&>(in)));
    
    for(register int i = 0; i < nr; i++)
    {
        Employee* elem = new T;
        try{
            in>>elem;

            if(typeid(T) == typeid(OrderOperator) && elem->position() != "operator comenzi")
                throw DynamicException("pozitie_invalida", "!! pentru a retine un manager sau un asistent, trebuie sa folositi tipul Employee !!\n\n");
            if(typeid(T) == typeid(Employee) && elem->position() == "operator comenzi")
                throw DynamicException("pozitie_invalida", "!! pentru a retine un operator de comenzi, trebuie sa folositi tipul OrderOperator !!\n\n");
        } catch(const exception& e) { 
            delete elem; 
            cout<<e.what(); 
            if(&in == &cin)
                i--; 
            continue;
        } 

        m.employeeAdd(elem);
    }
}
void addEmployee(Store&);

/* FUNCTII PENTRU GESTIUNEA PRODUSELOR */
template<class T>
void readProduct(Store& m, istream& in)
{
    unsigned int nr = (&in == &cin ? number() : number(dynamic_cast<ifstream&>(in)));
    
    for(register int i = 0; i < nr; i++)
    {
        Product* elem = new T;
        try{ in>>elem;} 
        catch(const exception& e) { 
            delete elem; 
            throw e.what(); 
            if(&in == &cin)
                i--; 
            continue;
        }

        m.productAdd(elem);
    }
}
void addProduct(Store&);