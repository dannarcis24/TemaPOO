#include "Order.h"

long long Order::number = 0;

void Order::validation(vector<Product>& vec) 
{
    if(vec.empty())
        throw DynamicException("comanda_invalida", "!! o comanda trebuie sa aiba cel putin un produs !!\n\n");

    int disks = 0, clothes = 0, price = 0;
    for(auto i = vec.begin(); i != vec.end(); i++)
    {
        if(typeid(*i) == typeid(Clothes())) 
        {
            clothes += i->getNumber();
            if(clothes > 3)
                throw DynamicException("comanda_invalida", "!! o comanda poate sa contina maxim 5discuri si 3artcole vestimentare !!\n\n");
        }
        else
            {
                disks += i->getNumber(); 
                if(disks > 5)
                    throw DynamicException("comanda_invalida", "!! o comanda poate sa contina maxim 5discuri si 3artcole vestimentare !!\n\n");
            }
        
        price += i->getPrice(false);

        list.push_back(&(*i));
    }
    if(price < 100)
        throw DynamicException("comanda_invalida", "!! o comanda trebuie sa aiba pretul minim de 100lei, fara costuri suplimentare !!\n\n");   

    ID = "$" + to_string(Order::number++);     
}

Order::Order() {
    ID = "$" + to_string(Order::number++);
}

Order::Order(vector<Product>& vec, int t): time(t) {
    validation(vec);
}

Order::Order(const Order& elem): time(elem.time), processing_date(elem.processing_date), list(elem.list) {
    ID = "$" + to_string(Order::number++);
}

Order::~Order() {
    for(auto i : list)
        delete i;
}

Order& Order::operator=(const Order& elem)
{
    time = elem.time;
    processing_date = elem.processing_date;
    
    for(auto i : list)
        delete i;
    for(auto i : elem.list)
    {
        Product* elem;
        if(typeid(*i) == typeid(Clothes))
            elem = new Clothes;
        else
            if(typeid(*i) == typeid(Disk))
                elem = new Disk;
            else
                elem = new VintageDisk;
        
        *elem = *i;
        list.push_back(elem);
    }

    return *this;
}

void Order::write(ostream& out) const
{
    out<<"////// INFORMATII DESPRE COMANDA: "<<ID<<" //////\n\n";
    out<<"Data de procesare: "<<processing_date<<'\n';
    out<<"Durata pentru finalizarea comenzii: "<<time<<'\n';
    out<<"Produsele din comanda:\n";
    for(auto& i : list)
        out<<i<<'\n';
}

ostream& operator<<(ostream& out, const Order& elem)
{
    elem.write(out);

    return out;
}

ostream& operator<<(ostream& out, const Order* elem)
{
    elem->write(out);

    return out;
}

void Order::read(istream& in)
{
    if(&in == &cin)
        cout<<"Durata pentru finalizarea comenzii este: ";
    string aux;
    getline(in, aux);
    try{ time = stoi(aux);}
    catch(const exception&) { throw DynamicException("timp_invalid", "!! timpul de procesare trebuie sa fie un numar natural pozitiv nenul !!\n\n");}

    if(&in == &cin)
        cout<<"Introduceti numarul de produse din comanda: ";
    getline(in, aux);
    int nr;
    try{ nr = stoi(aux);}
    catch(const exception&) { throw DynamicException("numar_invalid", "!! numarul de produse trebuie sa fie un numar natural pozitiv nenul !!\n\n");}

    for(register int i = 0; i < nr; i++)
    {
        if(&cin == &in)
            cout<<"Introduceti tipul produsului " + to_string(i + 1) + " (articol vestimentar/disc/disc vintage): ";
        getline(in, aux);
        
        Product* elem;
        if(aux == "articol vestimentar")
        {
            Product* elem = new Clothes;
            in>>elem;
            list.push_back(elem);
        }
        else
            if(aux == "disc")
                {
                    elem = new Disk;
                    in>>elem;
                    list.push_back(elem);
                }
            else
                if(aux == "disc vintage")
                {
                    elem = new VintageDisk;
                    in>>elem;
                    list.push_back(elem);
                }
                else
                    throw DynamicException("produs_invalid", "!! produsul trebuie sa fie unul dintre cele trei: articol vestimentar/disc/disc vintage !!\n\n");
    }
}

istream& operator>>(istream& in, Order& elem)
{
    Order aux;
    try{ aux.read(in);}
    catch(const exception& e) { throw DynamicException(dynamic_cast<const DynamicException&>(e));}
    elem = aux;

    return in;
}

istream& operator>>(istream& in, Order* elem)
{
    try{ elem->read(in);}
    catch(const exception& e) { throw DynamicException(dynamic_cast<const DynamicException&>(e));}

    return in;
}

const int Order::getTime(bool type) {
    return (type ? --time : time);
}

const int Order::getPrice() const
{
    int sum = (*(list.begin()))->getPrice();
    for(auto i = ++list.begin(); i != list.end(); i++)
        sum += (*i)->getPrice();

    return sum;
}

bool Order::verifStock(vector<Product*> products) const
{
    if(list.empty())
        return false;
    
    for(const auto& order : list)
    {
        bool ok = false;
        for(const auto& elem : products)
            if(compare(order, elem))
                if(elem->getNumber() >= order->getNumber())
                {
                    ok = true;
                    break;
                }
        
        if(ok == false)
            return false;
    }

    for(const auto& order : list)
        for(const auto& elem : products)
            if(compare(order, elem))
                if(elem->getNumber() >= order->getNumber())
                {
                    elem->setNumberProducts(elem->getNumber() - order->getNumber());
                    break;
                }

    return true;
}