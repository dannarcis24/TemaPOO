#include "DynamicException.h"

class Date{
    int day = 1, month = 1, year = 1900; // se considera primul an 1900
    
    inline void validationDate(const string);
    void validationDate() const;

public:
    Date() = default;
    Date(int, int, int);
    Date(const string&);

    friend ostream& operator<<(ostream&, const Date&);
    friend istream& operator>>(istream&, Date&);

    bool esteMajor() const; // de gandit la un nume mai bun
    const int years() const;
    bool isBirthday() const;
};