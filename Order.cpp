#include "Order.h"

long long Order::number = 0;

void Order::validation(vector<unique_ptr<Product>>& vec) 
{
    if(vec.empty())
        throw DynamicException("comanda_invalida", "!! o comanda trebuie sa aiba cel putin un produs !!\n\n");

    int disks = 0, clothes = 0, price = 0;
    for(auto i = vec.begin(); i != vec.end(); i++)
    {
        if(typeid(**i) == typeid(Clothes)) 
        {
            clothes += (*i)->getNumber();
            if(clothes > 3)
                throw DynamicException("comanda_invalida", "!! o comanda poate sa contina maxim 5discuri si 3artcole vestimentare !!\n\n");
        }
        else
            {
                disks += (*i)->getNumber(); 
                if(disks > 5)
                    throw DynamicException("comanda_invalida", "!! o comanda poate sa contina maxim 5discuri si 3artcole vestimentare !!\n\n");
            }
        
        price += (*i)->getPrice(false) * (*i)->getNumber();
    }
    if(price < 100)
        throw DynamicException("comanda_invalida", "!! o comanda trebuie sa aiba pretul minim de 100lei, fara costuri suplimentare !!\n\n");    

    for(auto i = vec.begin(); i != vec.end(); i++)
        list.push_back(move(*i));
    vec.clear();
}

Order::Order() {
    ID = "$" + to_string(Order::number++);
}

Order::Order(vector<unique_ptr<Product>>& vec, int t): time(t) {
    validation(vec);
    ID = "$" + to_string(Order::number++);
}

Order::Order(const Order& elem): time(elem.time) {
    for(auto i = elem.list.begin(); i != elem.list.end(); i++)
    {
        unique_ptr<Product> aux;
        if(typeid(*i) == typeid(Clothes))
            aux = make_unique<Clothes>();
        else
            if(typeid(*i) == typeid(Disk))
                aux = make_unique<Disk>();
            else
                aux = make_unique<VintageDisk>();
        *aux = **i;
        
        list.push_back(move(aux));
    }

    ID = "$" + to_string(Order::number++);
}

Order::Order(Order&& elem): ID(move(elem.ID)), time(move(elem.time)), processing_date(move(elem.processing_date)) {
    list = move(elem.list);
}

Order& Order::operator=(const Order& elem)
{
    if(this == &elem)
        return *this;

    ID = elem.ID;
    time = elem.time;
    processing_date = elem.processing_date;
    
    list.clear();
    for(auto i = elem.list.begin(); i != elem.list.end(); i++)
    {
        unique_ptr<Product> aux;
        if(typeid(*i) == typeid(Clothes))
            aux = make_unique<Clothes>();
        else
            if(typeid(*i) == typeid(Disk))
                aux = make_unique<Disk>();
            else
                aux = make_unique<VintageDisk>();
        *aux = **i;
        
        list.push_back(move(aux));
    }

    return *this;
}

Order& Order::operator=(Order&& elem)
{
    if(this == &elem)
        return *this;

    ID = move(elem.ID);
    time = move(elem.time);
    processing_date = move(elem.processing_date);
    list = move(elem.list);

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

ostream& operator<<(ostream& out, const unique_ptr<Order>& elem)
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

    try {
        vector<unique_ptr<Product>> vec;
        for(register int i = 0; i < nr; i++)
        {
            if(&cin == &in)
                cout<<"Introduceti tipul produsului " + to_string(i + 1) + " (articol vestimentar/disc/disc vintage): ";
            getline(in, aux);
            
            unique_ptr<Product> elem;
            if(aux == "articol vestimentar")
                elem = make_unique<Clothes>();
            else
                if(aux == "disc")
                    elem = make_unique<Disk>();
                else
                    if(aux == "disc vintage")
                        elem = make_unique<VintageDisk>();
                    else
                        throw DynamicException("produs_invalid", "!! produsul trebuie sa fie unul dintre cele trei: articol vestimentar/disc/disc vintage !!\n\n");

            in>>elem;
            vec.push_back(move(elem));
        }
        validation(vec);
    } catch(const exception&) { throw;}
}

istream& operator>>(istream& in, Order& elem)
{
    Order aux;
    try{ aux.read(in);}
    catch(const exception&) { Order::number--; throw;}
    elem = move(aux);

    return in;
}

istream& operator>>(istream& in, unique_ptr<Order>& elem)
{
    try{ elem->read(in);}
    catch(const exception&) { Order::number--; throw;}

    return in;
}

const int Order::getTime(bool type) {
    return (type ? --time : time);
}

const double Order::getPrice() const
{
    int sum = (*(list.begin()))->getPrice();
    for(auto i = ++list.begin(); i != list.end(); i++)
        sum += (*i)->getPrice() * (*i)->getNumber();

    return sum;
}

bool Order::verifStock(vector<unique_ptr<Product>>& products) const
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