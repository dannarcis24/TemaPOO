#include "Disk.h"

void Disk::validation() const
{
    if(record_company.empty())
        throw DynamicException("casa_discuri_invalida", "!! casa de discuri nu poate sa fie un sir gol !!\n\n");
    if(band.empty())
        throw DynamicException("trupa_invalida", "!! numele trupei nu poate sa fie un sir gol !!\n\n");
    if(album_name.empty())
        throw DynamicException("album_invalid", "!! numele albumului nu poate sa fie un sir gol !!\n\n");
}

Disk::Disk(const string& name, int number1, double price, const string& disk, const string& band1, const string& album, const Date& data, bool t): Product(name, number1, price), record_company(disk), band(band1), album_name(album), sale_date(data), type(t) {
    validation();
}

Disk::Disk(const string& name, int number1, double price, const string& disk, const string& band1, const string& album, const string& data, bool t): Product(name, number1, price), record_company(disk), band(band1), album_name(album), sale_date(data), type(t) {
    validation();
}

Disk::Disk(const string& name, int number1, double price, const string& disk, const string& band1, const string& album, int day, int month, int year, bool t): Product(name, number1, price), record_company(disk), band(band1), album_name(album), sale_date(day, month, year), type(t) {
    validation();
}

const double Disk::getPrice(bool cost) const {
    return (cost ? (5 + price_base) : price_base);
}

void Disk::write(ostream& out) const {
    Product::write(out);
    out<<"Tipul produsului: disc "<<(type ? "vinil" : "CD")<<"\nCasa de Disk: "<<record_company<<"\nNumele trupei: "<<band<<"\nNumele albumului: "<<album_name<<"\nData vanzare: "<<sale_date<<'\n';
}

void Disk::write(ofstream& out) const {
    Product::write(out);
    out<<','<<record_company<<','<<band<<','<<album_name<<','<<sale_date<<','<<(type ? "vinil" : "CD");
}

ostream& operator<<(ostream& out, const Disk& elem)
{
    if(auto* aux = dynamic_cast<ofstream*>(&out))
        elem.write(*aux);
    else
        elem.write(out);
    return out;
}

ostream& operator<<(ostream& out, const Disk* elem)
{
    if(auto* aux = dynamic_cast<ofstream*>(&out))
        elem->write(*aux);
    else
        elem->write(out);
    return out;
}

void Disk::read(istream& in)
{
    Product::read(in);

    if(&in == &cin)
        cout<<"Numele casei de Diskuri este: ";
    getline(in, record_company);
    if(record_company.empty())
        throw DynamicException("casa_Disk_invalida", "!! casa de Disk nu poate sa fie un sir gol !!\n\n");

    if(&in == &cin)
        cout<<"Numele trupei este: ";
    getline(in, band);
    if(band.empty())
        throw DynamicException("trupa_invalida", "!! numele trupei nu poate sa fie un sir gol !!\n\n");

    if(&in == &cin)
        cout<<"Numele albumului este: ";
    getline(in, album_name);
    if(album_name.empty())
        throw DynamicException("album_invalid", "!! numele albumului nu poate sa fie un sir gol !!\n\n");

    if(&in == &cin)
        cout<<"Data vanzarii este ";
    in>>sale_date;

    if(&in == &cin)
        cout<<"Introduceti 0 pentru CD sau 1 pentru viniluri: ";
    string aux;
    getline(in, aux);
    if(aux != "0" && aux != "1")
        throw DynamicException("argument_invalid", "!! pentru starea discului introduceti 1/0 !!\n\n");
    
    type = (aux == "0 " ? 0 : 1);
}

istream& operator>>(istream& in, Disk& elem)
{
    Disk aux = elem;
    try{ aux.read(in);}
    catch(const exception&) {Product::number--; throw;}
    elem = aux;

    return in;
}

istream& operator>>(istream& in, Disk* elem)
{
    try{ elem->read(in);}
    catch(const exception&) {Product::number--; throw;}
    return in;
}

bool Disk::isEqual(const Product& elem) const
{
    const Disk* aux = dynamic_cast<const Disk*>(&elem);
    if(!aux)    
        return false;

    return (Product::isEqual(elem) && record_company == aux->record_company && album_name == aux->album_name && sale_date == aux->sale_date && type == aux->type); 
}

bool operator==(const Disk& elem1, const Disk& elem2) {
    return elem1.isEqual(elem2);
}

bool operator!=(const Disk& elem1, const Disk& elem2) {
    return !(elem1 == elem2);
}