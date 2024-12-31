#include "Clothes.h"

Clothes::Clothes(const string& name, int number1, double price, const string& culoare, const string& marca): Product(name, number1, price), color(culoare), brand(marca) 
{
    if(color.empty())
        throw DynamicException("culoare_invalida", "!! culoarea nu poate sa fie un sir gol !!\n\n");
    if(brand.empty())
        throw DynamicException("marca_invalida", "!! marca nu poate sa fie un sir gol!!\n\n");
}

Clothes::Clothes(const Product& product, const string& culoare, const string& marca): Product(product), color(culoare), brand(marca) 
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
    Product::write(out);
    out<<"Tip: articol vestimentar\nCuloarea: "<<color<<"\nMarca: "<<brand<<'\n';
}

void Clothes::write(ofstream& out) const{
    Product::write(out);
    out<<','<<"articol vestimentar"<<','<<color<<','<<brand;
}

ostream& operator<<(ostream& out, const Clothes& elem)
{
    if(auto* aux = dynamic_cast<ofstream*>(&out))
        elem.write(*aux);
    else
        elem.write(out);
    return out;
}

ostream& operator<<(ostream& out, const unique_ptr<Clothes>& elem)
{
    if(auto* aux = dynamic_cast<ofstream*>(&out))
        elem->write(*aux);
    else
        elem->write(out);
    return out;
}

void Clothes::read(istream& in)
{
    Product::read(in);
    if(&in == &cin)
        cout<<"Introduceti culoarea: ";
    getline(in, color);
    if(color.empty())
        throw DynamicException("culoare_invalida", "!! culoarea nu poate sa fie un sir gol !!\n\n");

    if(&in == &cin)
        cout<<"Introduceti marca: ";
    getline(in, brand);
    if(brand.empty())
        throw DynamicException("marca_invalida", "!! marca nu poate sa fie un sir gol!!\n\n");
}

istream& operator>>(istream& in, Clothes& elem)
{
    Clothes aux = elem;
    try{ aux.read(in);}
    catch(const exception&) { Product::number--; throw;}
    elem = aux;

    return in;
}

istream& operator>>(istream& in, unique_ptr<Clothes>& elem)
{
    Clothes aux;
    try{ aux.read(in);}
    catch(const exception&) { Product::number--; throw;}
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