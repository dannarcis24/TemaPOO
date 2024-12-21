#include "Order.h"

long long Order::numar = 0;

void Order::validation(vector<Product>& vec) 
{
    if(vec.empty())
        throw DynamicException("comanda_invalida", "!! o comanda trebuie sa aiba cel putin un Product !!\n\n");
    if(vec.size() > 8)
        throw DynamicException("comanda_invalida", "!! o comanda poate sa contina maxim 5discuri si 3artcole vestimentare !!\n\n");
    
    int disk = 0, number = 0, price = 0;
    for(auto i = vec.begin(); i != vec.end(); i++)
    {
        if(typeid(*i) == typeid(Clothes())) {
            if(++number > 3)
                throw DynamicException("comanda_invalida", "!! o comanda poate sa contina maxim 5discuri si 3artcole vestimentare !!\n\n");
            }
        else
            if(++disk > 5)
                throw DynamicException("comanda_invalida", "!! o comanda poate sa contina maxim 5discuri si 3artcole vestimentare !!\n\n");
        
        price += i->getPrice(false);

        list.push_back(&(*i));
    }
    if(price < 100)
        throw DynamicException("comanda_invalida", "!! o comanda trebuie sa aiba pretul minim de 100lei, fara costuri suplimentare !!\n\n");   

    ID = "$" + to_string(Order::numar++);     
}

Order::Order(vector<Product>& vec, const Date& date, int t): processing_date(date), time(t) {
    validation(vec);
}

Order::Order(vector<Product>& vec, const string& date, int t): processing_date(date), time(t) {
    validation(vec);
}

Order::Order(vector<Product>& vec, int day, int month, int year, int t): processing_date(day, month, year), time(t) {
    validation(vec);
}

istream& operator>>(istream& in, Order& elem)
{
    if(&in == &cin)
        cout<<"Data de procesare este: ";
    in>>elem.processing_date;

    if(&in == &cin)
        cout<<"Durata pentru finalizarea comenzii este: ";
    string aux;
    getline(in, aux);
    elem.time = stoi(aux);

    // trebuie sa ma opresc la o linie goala sau nush, poate iau numarul de elemente, desi e o coada cu prioritatie, care e tot un vector pana la urma, daca iau cazul cu vector e lejer

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