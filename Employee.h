#include "Date.h"
#include <fstream>
#include <typeinfo>

class Employee {
protected:
    string last_name, first_name, CNP, ID = "@0";
    Date employment_date = Date();
    double coefficient;
    bool job = true; // assistent(true) or manager(false)

    static const int salary_base = 3500, old = 100;
    static unsigned long long number;

    virtual void write(ostream&) const;
    virtual void write(ofstream&) const;
    void read(istream&);

public:
    Employee();
    Employee(const string&, const string&, const string&, const Date&, bool);
    Employee(const string&, const string&, const string&, int, int, int, bool);
    Employee(const string&, const string&, const string&, const string&, bool);
    Employee(const string&);

    friend ostream& operator<<(ostream&, const Employee*);
    friend ostream& operator<<(ostream&, const Employee); 
    friend istream& operator>>(istream&, Employee&);
    friend istream& operator>>(istream&, Employee*);
    friend bool compareByName(const Employee*, const Employee*);

    // de implementat citirea

    virtual const int salary() const;
    void setName(const string&);
    const string position() const;
    bool exist(const string&) const;

private:
    const Date birthday() const;

    inline void validationString(const string, bool = true) const;
    inline void validationCNP() const;
    inline void validation();
};