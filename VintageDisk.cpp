#include "VintageDisk.h"

VintageDisk::VintageDisk(const string& name, int number, double price, const string& disk, const string& band, const string& album, const Date& data, bool t,int coef, bool type): Disk(name, number, price, disk, band, album, data, t), rarity(coef), mint(type) {
    if(rarity < 1 || rarity > 5)
        throw DynamicException("coeficient_raritate_invalid", "!! coeficientul de raritate al unui disc vintage este cuprins intre 1-5 !!\n\n");
}

VintageDisk::VintageDisk(const string& name, int number, double price, const string& disk, const string& band, const string& album, const string& data, bool t, int coef, bool type): Disk(name, number, price, disk, band, album, data, t), rarity(coef), mint(type) {
    if(rarity < 1 || rarity > 5)
        throw DynamicException("coeficient_raritate_invalid", "!! coeficientul de raritate al unui disc vintage este cuprins intre 1-5 !!\n\n");
}

VintageDisk::VintageDisk(const string& name, int number, double price, const string& disk, const string& band, const string& album, int day, int month, int year, bool t, int coef, bool type):Disk(name, number, price, disk, band, album, day, month, year, t), rarity(coef), mint(type) {
    if(rarity < 1 || rarity > 5)
        throw DynamicException("coeficient_raritate_invalid", "!! coeficientul de raritate al unui disc vintage este cuprins intre 1-5 !!\n\n");
}

VintageDisk::VintageDisk(const Disk disk, int coef, bool type): Disk(disk), rarity(coef), mint(type) {
    if(rarity < 1 || rarity > 5)
        throw DynamicException("coeficient_raritate_invalid", "!! coeficientul de raritate al unui disc vintage este cuprins intre 1-5 !!\n\n");
}

const double VintageDisk::getPrice(bool cost) const {
    return (cost ? (15 * rarity + price_base) : price_base);
}

void VintageDisk::write(ostream& out) const {
    Disk::write(out);
    out<<"Coeficientul de raritate: "<<rarity<<"\nStarea discului vintage: "<<(mint ? "neutilizat" : "utilizat")<<'\n';
}

void VintageDisk::write(ofstream& out) const {
    Disk::write(out);
    out<<','<<rarity<<','<<(mint ? "neutilizat" : "utilizat");
}

ostream& operator<<(ostream& out, const VintageDisk& elem)
{
    if(auto* aux = dynamic_cast<ofstream*>(&out))
        elem.write(*aux);
    else
        elem.write(out);
    return out;
}

ostream& operator<<(ostream& out, const VintageDisk* elem)
{
    if(auto* aux = dynamic_cast<ofstream*>(&out))
        elem->write(*aux);
    else
        elem->write(out);
    return out;
}

void VintageDisk::read(istream& in)
{
    Disk::read(in);
    
    if(&in == &cin)
        cout<<"Introduceti coeficientul de raritate: ";
    string aux;
    getline(in, aux);
    try{ 
        rarity = stoi(aux);
        if(rarity < 1 || rarity > 5)
            throw DynamicException("-", "-");
    } catch(const exception&) { throw DynamicException("coeficient_raritate_invalid", "!! coeficientul de raritate al unui disc vintage este cuprins intre 1-5 !!\n\n");}

    if(&in == &cin)
        cout<<"Daca starea discului este buna, introduceti 1, altfel 0: ";
    getline(in, aux);
    if(aux != "0" && aux != "1")
        throw DynamicException("argument_invalid", "!! pentru starea discului introduceti 1/0 !!\n\n");
    
    mint  = (aux == "0 " ? 0 : 1);
}

istream& operator>>(istream& in, VintageDisk& elem)
{
    VintageDisk aux = elem;
    try { aux.read(in);}
    catch(const exception&) { Product::number--; throw;}
    elem = aux;

    return in;
}

istream& operator>>(istream& in, VintageDisk* elem)
{
    try{ elem->read(in);}
    catch(const exception&) { Product::number--; throw;}
    return in;
}

bool VintageDisk::isEqual(const Product& elem) const 
{
    const VintageDisk* aux = dynamic_cast<const VintageDisk*>(&elem);
    if(!aux)
        return false;
    
    return (Disk::isEqual(elem) && rarity == aux->rarity && mint == aux->mint);
}

bool operator==(const VintageDisk& elem1, const VintageDisk& elem2) {
    return elem1.isEqual(elem2);
}

bool operator!=(const VintageDisk& elem1, const VintageDisk& elem2) {
    return !(elem1 == elem2);
}