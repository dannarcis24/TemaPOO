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

void readEmployee(Store& m, istream& in)
{
    unsigned int nr = (&in == &cin ? number() : number(dynamic_cast<ifstream&>(in)));
    bool ok = false;

    for(register int i = 0; i < nr; i++)
    {
        if(&in == &cin)
            cout<<"Introduceti pozitia angajatului, pe care doriti sa-l adaugati (manager/asistent/operator de comenzi): ";
        string option;
        getline(in, option);

        unique_ptr<Employee> elem;
        if(option == "manager" || option == "asistent")
            elem = make_unique<Employee>(option);
        else
            if(option == "operator comenzi")
                elem = make_unique<OrderOperator>();
            else
            {
                cout<<"pozitie_invalida: !! pozitia trebuie sa fie una dintre cele trei (manager/asistent/operator comenzi) !!\n\n";
                if(&in == &cin) {
                    i--; continue;
                }
                else
                    return;
            }

        try { in>>elem;}
        catch(const exception& e) { 
            elem.reset(); 
            if(&in == &cin) { 
                cout<<e.what();
                i--; continue;
            }
            else {
                cout<<"Angajatul "<<i<<" (toti angajatii, care urmeaza dupa acesta nu vor putea fi adaugati): "<<e.what(); 
                return;
            }
        }

        try { 
            m.employeeAdd(elem); 
            ok = true;
            if(&in == &cin)
                cout<<"Adaugarea a fost efectuata cu succes!\n\n";
        } catch(const exception& e) { 
            if(&in == &cin) 
                i--;
            cout<<"Angajatul "<<(i + 1)<<": "<<e.what();
        }
    }

    if(ok && &in != &cin)
        cout<<"Adaugarea a fost efectuata cu succes!\n\n";
}

void addEmployee(Store& m)
{
    cout<<"Doriti sa cititi de la tastatura sau din fisier? (tastatura/fisier): ";
    string option;
    getline(cin, option);

    if(option == "tastatura")
        readEmployee(m, cin);
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
                readEmployee(m, in);
                in.close();
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: (tastatura/fisier) !!\n\n";
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

                cout<<"Afisarea a fost efectuata cu succes!\n\n"; 
                out.close();
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: (consola/fisier) !!\n\n";
}

void readProduct(Store& m, istream& in)
{
    unsigned int nr = (&in == &cin ? number() : number(dynamic_cast<ifstream&>(in)));
    bool ok = false;

    for(register int i = 0; i < nr; i++)
    {   
        if(&in == &cin)
            cout<<"Introduceti tipul produsului, pe care doriti sa-l adaugati (articol vestimentar/disc/disc vintage): ";
        string option;
        getline(in, option);

        unique_ptr<Product> elem;
        if(option == "articol vestimentar")
            elem = make_unique<Clothes>();
        else
            if(option == "disc")
                elem = make_unique<Disk>();
            else
                if(option == "disc vintage")
                    elem = make_unique<VintageDisk>();
                else
                {
                    cout<<"pozitie_invalida: !! pozitia trebuie sa fie una dintre cele trei (articol vestimentar/disc/disc vintage) !!\n\n";
                        if(&in == &cin) {
                        i--; continue;
                    }
                    else
                        return;
                }

        try { in>>elem;}
        catch(const exception& e) { 
            elem.reset(); 
            if(&in == &cin) { 
                cout<<e.what();
                i--; continue;
            }
            else
                cout<<"Produsul "<<(i + 1)<<" (toate produsele, care urmeaza dupa acesta nu vor putea fi adaugate): "<<e.what();
        }

        try { 
            m.productAdd(elem);
            ok = true;
            if(&in == &cin) 
                cout<<"Adaugarea a fost efectuata cu succes!\n\n";
        } catch(const exception& e) {
            if(&in == &cin) 
                i--;
            cout<<"Produsul "<<(i + 1)<<": "<<e.what(); 
        }
    }

    if(ok && &in != &cin)
        cout<<"Adaugarea a fost efectuata cu succes!\n\n";
}

void addProduct(Store& m)
{
    cout<<"Doriti sa cititi de la tastatura sau din fisier? (tastatura/fisier): ";
    string option;
    getline(cin, option);

    if(option == "tastatura")
        readProduct(m, cin);
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
                readProduct(m, in);
                in.close();
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: (tastatura/fisier) !!\n\n";
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
                (all ? m.productsWrite(out) : m.productInf(searchID()), out);
                cout<<"Afisarea a fost efectuata cu succes!\n\n";
                out.close();
            }
        }
        else
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: consola/fisier !!\n\n";
}

vector<unique_ptr<Order>> readOrders(istream& in)
{
    vector<unique_ptr<Order>> orders;
    unsigned int nr = (&in == &cin ? number() : number(dynamic_cast<ifstream&>(in)));

    for(register int i = 0; i < nr; i++)
    {
        unique_ptr<Order> elem = make_unique<Order>(); 
        try{ in>>elem;}
        catch(const exception& e) { 
            elem.reset();

            if(&in == &cin) 
            {
                cout<<e.what(); 
                i--; 
                continue;
            }
            else
            {
                cout<<"Comanda "<<i<<" (toate comemzile, care urmeaza dupa acesta nu vor putea fi adaugate): "<<e.what(); 
                return orders;
            }
        }

        orders.push_back(move(elem));
    }

    cout<<"Adaugarea a fost efectuata cu succes!\n\n";
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
                <<"timpul de procesare al comenzii, numarul de produse si informatiile despre fiecare produs in parte, "
                <<"pe fiecare linie sa fie introduse informatiile despre acestea, respectiv: "
                <<"denumirea, numarul de produse din stoc, pretul de baza si pentru fiecare tip:\nArticole vestimentare: "
                <<"culoare, brand\nDiscuri: casa de discuri, trupa, numele albumului, data vanzarii, CD sau vinil (0/1)\n"
                <<"Discuri vintage: raritate (1-5), mint (0/1)\n\nIntroduceti numele fisierului, din care doriti sa cititi: ";
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
            cout<<"optiune_invalida: !! optiunea trebuie sa fie una dintre cele doua: (tastatura/fisier) !!\n\n";

    bool exist = true;
    for(register int i = 0; m.orderExist(); i++)
    {
        try{ m.validation();}
        catch(const exception& e) {cout<<e.what(); m.ordersDel(); return;}

        cout<<"\nMomentul de timp "<<(i + 1)<<":\n";
        if(exist)
            try{ m.order2Operator();}
            catch(const exception& e) { exist = false; cout<<e.what();}
        
        m.orderFinish();
        if(m.orderNumber())
            cout<<"Mai sunt "<<m.orderNumber()<<" comenzi de procesat, acestea se afla in lista de asteptare.\n\n";
    }
}