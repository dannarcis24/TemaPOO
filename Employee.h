#include "Date.h"
#include <fstream>
#include <typeinfo>
#include <memory>

class Employee {
protected:
    string last_name, first_name, CNP, ID; // ID = "@number";
    Date employment_date;
    double coefficient;
    bool job = true; // assistent(true) or manager(false)

    static const int salary_base = 3500, old = 100;
    static unsigned long long number;

    virtual void write(ostream&) const;
    virtual void write(ofstream&) const;
    virtual void read(istream&);

public:
    Employee();
    Employee(const string&, const string&, const string&, const Date&, bool);
    Employee(const string&, const string&, const string&, int, int, int, bool);
    Employee(const string&, const string&, const string&, const string&, bool);
    Employee(const string&);

    friend ostream& operator<<(ostream&, const shared_ptr<Employee>&);
    friend ostream& operator<<(ostream&, const Employee); 
    friend istream& operator>>(istream&, Employee&);
    friend istream& operator>>(istream&, unique_ptr<Employee>&);
    friend bool compareByName(const shared_ptr<Employee>&, const shared_ptr<Employee>&);
    friend bool operator==(const shared_ptr<Employee>&, const shared_ptr<Employee>&);
    friend bool operator!=(const shared_ptr<Employee>&, const shared_ptr<Employee>&);

    virtual const int salary() const;
    void setName(const string&);
    void setName(string&&);
    const string position() const;
    bool exist(const string&) const;

private:
    const Date birthday() const;

    inline void validationString(const string, bool = true) const;
    inline void validationCNP() const;
    inline void validation();
};