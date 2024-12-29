#include "Product.h"

long long Product::number = 0;

Product::Product() {
    ID =  "#" + to_string(Product::number++);
}

Product::Product(const string& name1, int number1, double price): name(name1), number_products(number1), price_base(price) { 
    if(name.empty())
        throw DynamicException("denumire_invalida", "!! denumirea unui produs nu poate fi un sir gol !!\n\n");
    if(number_products < 0)
    {
        number_products = 0;
        throw DynamicException("numar_produse_invalid", "!! numarul de produse nu poate fi un numar negativ !!\n\n");
    }
    if(price_base <= 0)
    {
        price_base = 0;
        throw DynamicException("pret_invalid", "!! pretul unui produs trebuie sa fie un numar pozitiv !!\n\n");
    }

    ID =  "#" + to_string(Product::number++);
}

void Product::write(ostream& out) const {
    out<<"DETALII DESPRE PRODUSUL: "<<name<<'\n'<<"ID: "<<ID<<"\nNumarul de produse: "<<number_products<<"\nPretul de baza: "<<price_base<<'\n'<<"Pretul final: "<<getPrice()<<'\n';
}

void Product::write(ofstream& out) const {
    out<<name<<','<<ID<<','<<number_products<<','<<price_base<<','<<getPrice();
}

ostream& operator<<(ostream& out, const Product* elem) 
{
    if(auto* aux = dynamic_cast<ofstream*>(&out))
        elem->write(*aux);
    else
        elem->write(out);
    return out;
}

void Product::read(istream& in)
{
    if(&in == &cin)
        cout<<"Introduceti denumirea: ";
    getline(in, name);
    if(name.empty())
        throw DynamicException("denumire_invalida", "!! denumirea unui product nu poate fi un sir gol !!\n\n");

    if(&in == &cin)
        cout<<"Introduceti numarul de produse: ";
    string aux;
    getline(in, aux);
    try{ number_products = stoi(aux);
        if(number_products <= 0)
            throw DynamicException("numar_produse_invalid", "!! numarul de produse trebuie sa fie un numar natural pozitiv nenul !!\n\n");}
    catch(const exception&) { throw;}

    if(&in == &cin)
        cout<<"Introduceti pretul de baza: ";
    getline(in, aux);
    try{ price_base = stoi(aux);
        if(price_base <= 0)
            throw DynamicException("numar_produse_invalid", "!! numarul de produse trebuie sa fie un numar natural pozitiv nenul !!\n\n");}
    catch(const exception&) { throw;}
}

istream& operator>>(istream& in, Product* elem) 
{
    try{ elem->read(in);}
    catch(const exception&) { throw;}

    return in;
}

void Product::setNumberProducts(const int& nr) {
    if(nr < 0)
        throw DynamicException("numar_produse_invalid", "!! numarul de produse trebuie sa fie un numar natual pozitiv !!\n\n");
    number_products = nr;
}

bool Product::exist(const string& id) const {
    return (ID == id);
}

const int Product::getNumber() const {
    return number_products;
}

bool Product::isEqual(const Product& elem) const {
    return (name == elem.name && price_base == elem.price_base);
} 

bool compare(const Product* elem1, const Product* elem2)
{   
    if(elem1 == nullptr || elem2 == nullptr)
        return false;
    if(typeid(*elem1) != typeid(*elem2))
        return false;

    return elem1->isEqual(*elem2);
}