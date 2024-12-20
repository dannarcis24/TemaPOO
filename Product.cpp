#include "Product.h"
#include <typeinfo>

long long Product::number = 0;

Product::Product(const string nume, int number1, double price): name(nume), number_products(number1), price_base(price) { 
    if(name.empty())
        throw DynamicException("denumire_invalida", "!! denumirea unui product nu poate fi un sir gol !!\n\n");
    if(number_products < 0)
    {
        number_products = 0;
        throw DynamicException("numar_producte_invalid", "!! numarul de producte nu poate fi un numar negativ !!");
    }
    if(price_base <= 0)
        throw DynamicException("pret_invalid", "!! pretul unui product trebuie sa fie un numar pozitiv !!\n\n");

    ID =  "#" + to_string(Product::number++);
}

void Product::write(ostream& out) const {
    out<<"Denumirea: "<<name<<"\nID: "<<ID<<"\nNumarul de producte: "<<number_products<<"\nPretul de baza: "<<price_base<<'\n'<<"Pretul final: "<<getPrice()<<'\n';
}

ostream& operator<<(ostream& out, const Product* elem) 
{
    out<<"DETALII DESPRE PRODUctUL: "<<typeid(*elem).name()<<'\n';
    elem->Product::write(out);
    elem->write(out);

    return out;
}

void Product::read(istream& in)
{
    if(&in == &cin)
        cout<<"Denumirea productului: ";
    in>>name;
    if(name.empty())
        throw DynamicException("denumire_invalida", "!! denumirea unui product nu poate fi un sir gol !!\n\n");

    if(&in == &cin)
        cout<<"Numarul de producte: ";
    string aux;
    getline(in, aux);
    number_products = stoi(aux);

    if(&in == &cin)
        cout<<"Pretul de baza: ";
    getline(in, aux);
    price_base = stoi(aux);
}

istream& operator>>(istream& in, Product* elem) 
{
    auto aux = *elem;
    aux.Product::read(in);
    aux.read(in);
    *elem = aux;

    return in;
}

void Product::setNumberProducts(int numar) {
    if(numar < 0)
        throw DynamicException("numar_producte_invalid", "!! numarul de producte nu poate fi un numar negativ !!");
    number_products = numar;
}