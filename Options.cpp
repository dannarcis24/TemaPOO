#include "Options.h"
#include <fstream>

int number()
{
    unsigned int nr;

    while(true)
    {
        cout<<"Introduceti numarul: ";
        string option;
        getline(cin, option);
            
        try {
            nr = stoi(option);
            if(nr < 0)
                throw DynamicException("numar_invalid", "!! numarul trebuie sa fie un numar pozitiv nenul !!\n\n");

            return nr;
        } catch(const exception&) { cout<<"numar_invalid: !! numarul trebuie sa fie un numar pozitiv nenul !!\n\n";}

        cout<<"Daca doriti sa renuntati la a adauga, introduceti 0 la urmatorul pas.\n";
    }
}

int number(ifstream& in)
{
    unsigned int nr;
    string aux;
    getline(in, aux);

    try { nr = stoi(aux);}
    catch(const exception&) { 
        nr = 0;
        throw DynamicException("numar_invalid", "!! numarul trebuie sa fie un numar pozitiv nenul !!\n\n");
    }

    return nr;
}

const string searchID()
{
    string ID;
    cout<<"Introduceti ID ul pentru cautare: ";
    getline(cin, ID);

    return ID;
}

const string name()
{
    string name;
    cout<<"Introduceti numele: ";
    getline(cin, name);

    return name;
}

void addEmployee(Store& m)
{
    cout<<"Doriti sa cititi de la tastatura sau din fisier? (tastatura/fisier): ";
    string option;
    getline(cin, option);

    if(option == "tastatura")
    {
        cout<<"Pentru a adauga manageri/asistenti introduceti 0, pentru a adauga operator de comenzi introduceti 1: ";
        getline(cin, option);
        if(option == "0")
            readEmployee<Employee>(m, cin);
        else
            if(option == "1")
                readEmployee<OrderOperator>(m, cin);
            else
                cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: 0/1 !!\n\n";
    }
    else
        if(option == "fisier")
        {
            cout<<"Fisierul trebuie sa contina pe prima linie numarul de angajati, pe care doriti sa-i introduceti,"
                <<"urmand ca pe fiecare linie sa fie introduse informatiile despre acestia, respectiv: "
                <<"pozitia, numele, prenumele, CNP si data angajarii\n\nIntroduceti numele fisierului, din care doriti sa cititi: ";
            getline(cin, option);

            ifstream in(option);
            if(!in.is_open())
                cout<<"fisier_inexistent: !! fisierul nu exista sau nu poate fi deschis !!\n\n";
            else
            {
                cout<<"Pentru a adauga manageri/asistenti introduceti 0, pentru a adauga operatori de comenzi introduceti 1: ";
                getline(cin, option);
                if(option == "0")
                    readEmployee<Employee>(m, cin);
                else
                    if(option == "1")
                        readEmployee<OrderOperator>(m, cin);
                    else
                        cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: 0/1 !!\n\n";
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: tastatura/fisier !!\n\n";
}

void addProduct(Store& m)
{
    cout<<"Doriti sa cititi de la tastatura sau din fisier? (tastatura/fisier): ";
    string option;
    getline(cin, option);

    if(option == "tastatura")
    {
        cout<<"Pentru a adauga haine introduceti 0, pentru discuri introduceti 1, iar pentru discuri vintage introduceti 2:";
        getline(cin, option);

        if(option == "0")
            readProduct<Clothes>(m, cin);
        else
            if(option == "1")
                readProduct<Disk>(m, cin);
            else
                if(option == "2")
                    readProduct<VintageDisk>(m, cin);
                else
                    cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele trei: 0/1/2 !!\n\n";
    }
    else
        if(option == "fisier")
        {
            cout<<"Fisierul trebuie sa contina pe prima linie numarul de produse, pe care doriti sa le introduceti,"
                <<"urmand ca pe fiecare linie sa fie introduse informatiile despre acestea, respectiv: "
                <<"denumirea, numarul de produse din stoc, pretul de baza si pentru fiecare tip:\nArticole vestimentare: "
                <<"culoare, brand\nDiscuri: casa de discuri, trupa, numele albumului, data vanzarii, CD sau vinil (0/1)\n"
                <<"Discuri vintage: raritate (1-5), mint (0/1)\n\nIntroduceti numele fisierului, din care doriti sa cititi: ";
            getline(cin, option);

            ifstream in(option);
            if(!in.is_open())
                cout<<"fisier_inexistent: !! fisierul nu exista sau nu poate fi deschis !!\n\n";
            else
            {
                cout<<"Pentru a adauga manageri/asistenti introduceti 0, pentru a adauga operatori de comenzi introduceti 1: ";
                getline(cin, option);

                if(option == "0")
                    readProduct<Clothes>(m, cin);
                else
                    if(option == "1")
                        readProduct<Disk>(m, cin);
                    else
                        if(option == "2")
                            readProduct<VintageDisk>(m, cin);
                        else
                            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele trei: 0/1/2 !!\n\n";
                
                in.close();
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: tastatura/fisier !!\n\n";
}