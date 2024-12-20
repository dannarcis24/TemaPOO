#include "Clothes.h"

Clothes::Clothes(const string name, int number1, double price, const string culoare, const string marca): Product(name, number1, price), color(culoare), brand(marca) 
{
    if(color.empty())
        throw DynamicException("culoare_invalida", "!! culoarea nu poate sa fie un sir gol !!\n\n");
    if(brand.empty())
        throw DynamicException("marca_invalida", "!! marca nu poate sa fie un sir gol!!\n\n");
}

const double Clothes::getPrice(bool cost) const {
    return (cost ? (20 + price_base) : price_base);
}

void Clothes::write(ostream& out) const{
    out<<"Culoarea: "<<color<<"\nMarca: "<<brand<<'\n';
}

ostream& operator<<(ostream& out, const Clothes& elem)
{
    out<<"DETALII DESPRE PRODUSUL: ARTICOLE VESTIMENTARE\n";
    elem.Product::write(out);
    elem.write(out);

    return out;
}

void Clothes::read(istream& in)
{
    if(&in == &cin)
        cout<<"Culoarea este: ";
    in>>color;
    if(color.empty())
        throw DynamicException("culoare_invalida", "!! culoarea nu poate sa fie un sir gol !!\n\n");

    if(&in == &cin)
        cout<<"Marca este: ";
    in>>brand;
    if(brand.empty())
        throw DynamicException("marca_invalida", "!! marca nu poate sa fie un sir gol!!\n\n");
}

istream& operator>>(istream& in, Clothes& elem)
{
    Clothes aux = elem;
    aux.Product::read(in);
    aux.read(in);
    elem = aux;

    return in;
}