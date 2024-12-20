#include "Date.h"
#include <ctime>

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
    } catch(const exception&) { throw DynamicException("data_invalida", "!! data trebuie sa fie compusa din numere !!\n\n");}
    
    validationDate();
}

void Date::validationDate() const
{
    if(year < 1900)
        throw DynamicException("data_invalida", "!! anul < 1900, este invalid !!\n\n");

    if(month <= 0 || day <= 0 || year <= 0)
        throw DynamicException("data_invalida", "!! luna, ziua si anul trebuie sa fie numere naturale nenule !!\n\n");

    if(month > 12)
        throw DynamicException("data_invalida", "!! luna trebuie sa apartina intervalului 1-12 !!\n\n");

    if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31)
    {
        string text = "!! cum luna este " + to_string(month) + " ziua poate avea maxim 31zile !!\n";
        throw DynamicException("data_invalida", text.c_str());
    }
    else
        if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        {
            string text = "!! cum luna este " + to_string(month) + " ziua poate avea maxim 30zile !!\n";
            throw DynamicException("data_invalida", text.c_str());
        }
        else
            if(year % 4 == 0 && (year % 100 || year % 400 == 0))
            {
                if(day > 29) 
                    throw DynamicException("data_invalida", "!! luna februarie in an bisect are cel mult 29zile !!\n\n");
            }
            else
                if(day > 28)
                    throw DynamicException("data_invalida", "!! luna februare in an nebisect are cel mult 28zile !!\n\n");
}

Date::Date(int zz, int ll, int aaaa): day(zz), month(ll), year(aaaa) {
    validationDate();
}

Date::Date(const string data) {
    validationDate(data);
}

ostream& operator<<(ostream& out, const Date& elem)
{
    out<<elem.day<<'.'<<elem.month<<'.'<<elem.year;
    return out;
}

istream& operator>>(istream& in, Date& elem)
{
    if(&in == &cin)
        cout<<"Date este (zz.ll.aaaa): ";
    string aux;
    in>>aux;
    elem = Date(aux);

    return in;
}

bool Date::esteMajor() const
{
    time_t t = time(NULL); // se salveaza data curenta
    tm* now = localtime(&t);
    now->tm_mon++; // lunile sunt retinute de la 0 la 11
    now->tm_year += 1900; // primul an este considerat 1900

    if(now->tm_year < year)
        throw DynamicException("data_invalida", "!! anul nasterii trebuie sa fie <" + to_string(now->tm_year) + " !!\n\n");

    int age = now->tm_year - year;
    if(month < now->tm_mon || (month == now->tm_mon && day < now->tm_mday))
        age--;

    return (age > 18);
}

const int Date::years() const 
{
    time_t t = time(NULL); // se salveaza data curenta
    tm* now = localtime(&t);
    now->tm_mon++; // lunile sunt retinute de la 0 la 11
    now->tm_year += 1900; // primul an este considerat 1900

    int years = now->tm_year - year;
    if(month < now->tm_mon || (month == now->tm_mon && day < now->tm_mday))
        years--;

    return years;
}

bool Date::isBirthday() const 
{
    time_t t = time(NULL); // se salveaza data curenta
    tm* now = localtime(&t);

    return (now->tm_mday == day && ++now->tm_mon == month && now->tm_year + 1900 == year);
}