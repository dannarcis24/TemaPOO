#include "Product.h"

long long Product::number = 0;

Product::Product() {
    Product::number++;
}

Product::Product(const string& name1, int number1, int price): name(name1), number_products(number1), price_base(price) { 
    if(name.empty())
        throw DynamicException("denumire_invalida", "!! denumirea unui produs nu poate fi un sir gol !!\n\n");
    if(number_products < 0)
    {
        number_products = 0;
        throw DynamicException("numar_produse_invalid", "!! numarul de produse nu poate fi un numar negativ !!");
    }
    if(price_base <= 0)
    {
        price_base = 0;
        throw DynamicException("pret_invalid", "!! pretul unui produs trebuie sa fie un numar pozitiv !!\n\n");
    }

    ID =  "#" + to_string(Product::number++);
}

void Product::write(ostream& out) const {
    out<<"ID: "<<ID<<"\nNumarul de produse: "<<number_products<<"\nPretul de baza: "<<price_base<<'\n'<<"Pretul final: "<<getPrice()<<'\n';
}

ostream& operator<<(ostream& out, const Product* elem) 
{
    out<<"DETALII DESPRE PRODUSUL: "<<elem->name<<'\n';
    elem->Product::write(out);
    elem->write(out);

    return out;
}

void Product::read(istream& in)
{
    if(&in == &cin)
        cout<<"Denumirea produsului: ";
    in>>name;
    if(name.empty())
        throw DynamicException("denumire_invalida", "!! denumirea unui product nu poate fi un sir gol !!\n\n");

    if(&in == &cin)
        cout<<"Numarul de produse: ";
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
    try{ elem->read(in);}
    catch(const exception& e) { Product::number--; throw;}

    return in;
}

void Product::setNumberProducts(const int& nr) {
    if(nr < 0)
        throw DynamicException("numar_producte_invalid", "!! numarul de producte nu poate fi un numar negativ !!");
    number_products = nr;
}

bool Product::exist(const string& ID) const {
    return (this->ID == ID);
}