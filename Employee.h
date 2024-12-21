#include "Date.h"

class Employee {
    static unsigned long long number;
    bool job = true; // assistent(true) or manager(false)

protected:
    string last_name, first_name, CNP, ID = "@0";
    Date employment_date = Date();

    static const int salary_base = 3500, old = 100;
    static int coefficient;

    inline virtual void write(ostream&) const;

public:
    Employee() = default;
    Employee(const string&, const string&, const string&, const Date&, bool);
    Employee(const string&, const string&, const string&, int, int, int, bool);
    Employee(const string&, const string&, const string&, const string&, bool);

    friend ostream& operator<<(ostream&, const Employee*);
    friend ostream& operator<<(ostream&, const Employee); 

    // de implementat citirea

    virtual const int salary() const;
    inline void setName(const string&);
    const string position() const;
    bool exist(const string&) const;

private:
    const Date birthday() const;

    inline void validationString(const string, bool = true) const;
    inline void validationCNP() const;
    inline void validation();
};