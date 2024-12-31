#include "Date.h"

Date Date::currentDate() 
{
    time_t t = time(NULL); // se salveaza data curenta
    tm* now = localtime(&t);
    now->tm_mon++;// lunile sunt retinute de la 0 la 11
    now->tm_year += 1900;// primul an este considerat 1900

    return Date(*now);
}

void Date::validationDate(const string data)
{
    if(data.length() != 10)
        throw DynamicException("data_invalida", "!! data angajarii trebuie sa aiba forma: zz.ll.aaaa !!\n\n");
    if(data[2] != '.' || data[5] != '.')
        throw DynamicException("data_invalida", "!! data angajarii trebuie sa aiba forma: zz.ll.aaaa !!\n\n");
    
    try{
        day   = stoi(data.substr(0, 2));
        month = stoi(data.substr(3, 2));
        year   = stoi(data.substr(6, 4));
    } catch(const exception&) { throw DynamicException("data_invalida", "!! data trebuie sa fie compusa din numere naturale !!\n\n");}
    
    validationDate();
}

void Date::validationDate() const
{
    if(month <= 0 || day <= 0 || year <= 0)
        throw DynamicException("data_invalida", "!! luna, ziua si anul trebuie sa fie numere naturale pozitive nenule !!\n\n");

    if(month > 12)
        throw DynamicException("data_invalida", "!! luna trebuie sa apartina intervalului 1-12 !!\n\n");

    if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31)
        throw DynamicException("data_invalida", ("!! cum luna este " + to_string(month) + " ziua poate avea maxim 31zile !!\n"));
    else
        if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            throw DynamicException("data_invalida", ("!! cum luna este " + to_string(month) + " ziua poate avea maxim 30zile !!\n"));
        else
            if(month == 2) {
                if(year % 4 == 0 && (year % 100 || year % 400 == 0)) {
                    if(day > 29) 
                        throw DynamicException("data_invalida", "!! luna februarie in an bisect are cel mult 29zile !!\n\n");
                }
                else
                    if(day > 28)
                        throw DynamicException("data_invalida", "!! luna februare in an nebisect are cel mult 28zile !!\n\n");
            }

    if(currentDate() < *this)
        throw DynamicException("data_invalida", "!! data trebuie sa fie mai mica decat data curenta !!\n\n");
}

Date::Date(int zz, int ll, int aaaa): day(zz), month(ll), year(aaaa) {
    validationDate();
}

Date::Date(const string& date) {
    validationDate(date);
}

Date::Date(const tm& date): day(date.tm_mday), month(date.tm_mon), year(date.tm_year) {}

ostream& operator<<(ostream& out, const Date& elem)
{
    out<<elem.day<<'.'<<elem.month<<'.'<<elem.year;
    return out;
}

istream& operator>>(istream& in, Date& elem)
{
    if(&in == &cin)
        cout<<"(zz.ll.aaaa): ";
    string aux;
    getline(in, aux);
    elem = Date(aux);

    return in;
}

bool operator==(const Date& elem1, const Date& elem2) {
    return (elem1.day == elem2.day && elem1.month == elem2.month && elem1.year == elem2.year);
}

bool operator!=(const Date& elem1, const Date& elem2) {
    return !(elem1 == elem2);
}

bool operator<=(const Date& elem1, const Date& elem2) {
    if(elem1.year < elem2.year)
        return true;
    else
        if(elem1.year == elem2.year && elem1.month < elem2.month)
            return true;
        else
            if(elem1.year == elem2.year && elem1.month == elem2.month && elem1.day <= elem2.day)
                return true;
            else
                return false;
}

bool operator>(const Date& elem1, const Date& elem2) {
    return !(elem1 <= elem2);
}

bool operator>=(const Date& elem1, const Date& elem2) {
    if(elem1.year > elem2.year)
        return true;
    else
        if(elem1.year == elem2.year && elem1.month > elem2.month)
            return true;
        else
            if(elem1.year == elem2.year && elem1.month == elem2.month && elem1.day >= elem2.day)
                return true;
            else
                return false;
}

bool operator<(const Date& elem1, const Date& elem2) {
    return !(elem1 >= elem2);
}

int Date::operator-(const Date& elem) const
{
    if(*this == elem)
        return 0;
    
    int years = year - elem.year;
    if(years < 0)
        years = -years;
    if(month < elem.month || (month == elem.month && day < elem.day))
        years--;
    
    return years;
}

bool Date::isAdult() const {
    return ((currentDate() - *this) >= 18);
}

const int Date::years() const {
    return (currentDate() - *this);
}

bool Date::isBirthday() const  {
    return (currentDate().month == month);
}