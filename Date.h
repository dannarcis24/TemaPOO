#include "DynamicException.h"
#include <ctime>

class Date{
    unsigned int day = 1, month = 1, year = 1900; // se considera primul an 1900
    
    inline void validationDate(const string);
    void validationDate() const;

public:
    Date() = default;
    Date(int, int, int);
    Date(const string&);
    Date(const tm&);

    static Date currentDate();

    friend ostream& operator<<(ostream&, const Date&);
    friend istream& operator>>(istream&, Date&);
    friend bool operator==(const Date&, const Date&);
    friend bool operator!=(const Date&, const Date&);
    friend bool operator<=(const Date&, const Date&);
    friend bool operator<(const Date&, const Date&);
    friend bool operator>=(const Date&, const Date&);
    friend bool operator>(const Date&, const Date&);
    int operator-(const Date&) const;
    
    bool isAdult() const; // de gandit la un nume mai bun
    const int years() const;
    bool isBirthday() const;
};
