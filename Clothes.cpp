#include "Clothes.h"

Clothes::Clothes(const string& name, int number1, int price, const string& culoare, const string& marca): Product(name, number1, price), color(culoare), brand(marca) 
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
    Product::read(in);
    if(&in == &cin)
        cout<<"Culoarea este: ";
    getline(in, color);
    if(color.empty())
        throw DynamicException("culoare_invalida", "!! culoarea nu poate sa fie un sir gol !!\n\n");

    if(&in == &cin)
        cout<<"Marca este: ";
    getline(in, brand);
    if(brand.empty())
        throw DynamicException("marca_invalida", "!! marca nu poate sa fie un sir gol!!\n\n");
}

istream& operator>>(istream& in, Clothes& elem)
{
    Clothes aux = elem;
    try{ aux.read(in);}
    catch(const exception& e) { Product::number--; throw DynamicException(dynamic_cast<const DynamicException&>(e));}
    elem = aux;

    return in;
}

istream& operator>>(istream& in, Clothes* elem)
{
    Clothes aux;
    try{ aux.read(in);}
    catch(const exception& e) { Product::number--; throw DynamicException(dynamic_cast<const DynamicException&>(e));}
    *elem = aux;

    return in;
}

bool Clothes::isEqual(const Product& elem) const
{
    const Clothes* aux = dynamic_cast<const Clothes*>(&elem);
    if(!aux)    
        return false;

    return (Product::isEqual(elem) && brand == aux->brand && color == aux->color); 
}

bool operator==(const Clothes& elem1, const Clothes& elem2) {
    return elem1.isEqual(elem2);
}

bool operator!=(const Clothes& elem1, const Clothes& elem2) {
    return !(elem1 == elem2);
}