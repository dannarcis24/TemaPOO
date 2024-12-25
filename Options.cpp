#include "Options.h"

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
                throw DynamicException("numar_invalid", "!! numarul trebuie sa fie un numar natural pozitiv nenul !!\n\n");

            return nr;
        } catch(const exception& e) { cout<<e.what();}

        cout<<"Daca doriti sa renuntati la a adauga, introduceti 0 la urmatorul pas.\n";
    }
}

int number(ifstream& in)
{
    unsigned int nr;
    string aux;
    getline(in, aux);

    try { 
        nr = stoi(aux);
        if(nr < 0)
            throw DynamicException("numar_invalid", "!! numarul trebuie sa fie un numar natural pozitiv nenul !!\n\n");
    }
    catch(const exception& e) { 
        nr = 0;
        cout<<e.what();
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

void readEmployeeFromFile(Store& m, ifstream& in)
{
    unsigned int nr = number(in);

    for(register int i = 0; i < nr; i++)
    {
        string option;
        getline(in, option);

        Employee* elem;
        if(option == "manager" || option == "asistent")
            elem = new Employee(option);
        else
            if(option == "operator comenzi")
                elem = new OrderOperator;
            else
            {
                cout<<("pozitie_invalida", "!! pozitia trebuie sa fie una dintre cele trei (manager/asistent/operator comenzi) !!\n\n");
                return;
            }

        try{ in>>elem;}
        catch(const exception& e) { 
            delete elem; 
            cout<<e.what(); 
            return;
        }
        m.employeeAdd(elem);
    }
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
            readEmployee<Employee>(m);
        else
            if(option == "1")
                readEmployee<OrderOperator>(m);
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
                readEmployeeFromFile(m, in);
                in.close();
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: tastatura/fisier !!\n\n";
}

void writeEmployee(Store& m, bool all)
{
    cout<<"Doriti sa afisati in consola sau in fisier? (consola/fisier): ";
    string option;
    getline(cin, option);

    if(option == "consola")
        if(all)
            m.employeesWrite();
        else
            m.employeeInf(searchID());
    else
        if(option == "fisier")
        {
            cout<<"Introduceti numele fisierului, in care doriti sa afisati: ";
            getline(cin, option);

            ofstream out(option);
            if(!out.is_open())
                cout<<"fisier_inexistent: !! fisierul nu exista sau nu poate fi deschis !!\n\n";
            else
            {
                if(all)
                    m.employeesWrite(out);
                else
                    m.employeeInf(searchID(), out);
                    
                out.close();
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: consola/fisier !!\n\n";
}

void readProductFromFile(Store& m, ifstream& in)
{
    unsigned int nr = number(in);

    for(register int i = 0; i < nr; i++)
    {
        string option;
        getline(in, option);

        Product* elem;
        if(option == "artciol vestimentar")
            elem = new Clothes;
        else
            if(option == "disc")
                elem = new Disk;
            else
                if(option == "disc vintage")
                    elem = new VintageDisk;
                else
                {
                    cout<<"pozitie_invalida", "!! pozitia trebuie sa fie una dintre cele trei (articol vestimentar/disc/disc vintage) !!\n\n";
                    return;
                }

        try{ in>>elem;}
        catch(const exception& e) { 
            delete elem; 
            cout<<e.what(); 
            continue;
        }
        m.productAdd(elem);
    }
}

void addProduct(Store& m)
{
    cout<<"Doriti sa cititi de la tastatura sau din fisier? (tastatura/fisier): ";
    string option;
    getline(cin, option);

    if(option == "tastatura")
    {
        cout<<"Pentru a adauga haine introduceti 0, pentru discuri introduceti 1, iar pentru discuri vintage introduceti 2: ";
        getline(cin, option);

        if(option == "0")
            readProduct<Clothes>(m);
        else
            if(option == "1")
                readProduct<Disk>(m);
            else
                if(option == "2")
                    readProduct<VintageDisk>(m);
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
                readProductFromFile(m, in);
                in.close();
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: tastatura/fisier !!\n\n";
}

void writeProducts(Store& m, bool all)
{
    cout<<"Doriti sa afisati in consola sau in fisier? (consola/fisier): ";
    string option;
    getline(cin, option);

    if(option == "consola")
        (all ? m.productsWrite() : m.productInf(searchID()));
    else
        if(option == "fisier")
        {
            cout<<"Introduceti numele fisierului, in care doriti sa afisati: ";
            getline(cin, option);

            ofstream out(option);
            if(!out.is_open())
                cout<<"fisier_inexistent: !! fisierul nu exista sau nu poate fi deschis !!\n\n";
            else
            {
                (all ? m.employeesWrite(out) : m.employeeInf(searchID()), out);
                out.close();
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: consola/fisier !!\n\n";
}

vector<Order*> readOrders(istream& in)
{
    vector<Order*> orders;
    unsigned int nr = (&in == &cin ? number() : number(dynamic_cast<ifstream&>(in)));

    for(register int i = 0; i < nr; i++)
    {
        Order* elem = new Order; 
        try{ in>>elem;}
        catch(const exception& e) { 
            cout<<e.what(); 
            if(&in == &cin)
                i--; 
            continue;
        }

        orders.push_back(elem);
    }

    return orders;
}

void managementOrders(Store& m)
{
    try{ m.validation();}
    catch(const exception& e) { cout<<e.what(); return;}

    cout<<"Doriti sa cititi de la tastatura sau din fisier? (tastatura/fisier): ";
    string option;
    getline(cin, option);

    if(option == "tastatura")
        m.orderAdd(readOrders(cin));
    else
        if(option == "fisier")
        {
            cout<<"Fisierul trebuie sa contina pe prima linie numarul de comenzi, pe care doriti sa le introduceti,"
                <<"urmand ca pe fiecare linie sa fie introduse informatiile despre acestea, respectiv: "
                <<"numarul de produse, data procesarii comenzii, ID ul comenzii si timpul de procesare\n\n"
                <<"Introduceti numele fisierului, din care doriti sa cititi: ";
            getline(cin, option);

            ifstream in(option);
            if(!in.is_open())
                cout<<"fisier_inexistent: !! fisierul nu exista sau nu poate fi deschis !!\n\n";
            else
            {
                m.orderAdd(readOrders(in));
                in.close();
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: tastatura/fisier !!\n\n";

    for(register int i = 0; m.orderExist(); i++)
    {
        try{ m.validation();}
        catch(const exception& e) {cout<<e.what(); m.ordersDel(); return;}

        try{ m.order2Operator();}
        catch(const exception& e) { cout<<e.what();}
        
        m.orderFinish();
        cout<<"Momentul de timp "<<(i + 1)<<":\nMai sunt "<<m.orderNumber()<<" comenzi de procesat, acestea se afla in lista de asteptare.\n\n";
    }
}