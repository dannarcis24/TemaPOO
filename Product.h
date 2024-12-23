#include "Employee.h"
#include <typeinfo>

class Product {
    static long long number;
    
protected:
    string name, ID = "#0";
    unsigned int number_products = 0, price_base = 0;

    virtual void write(ostream&) const;
    virtual void read(istream&);

public:
    Product() = default;
    Product(const string&, int, int);
    virtual ~Product() = default;

    friend ostream& operator<<(ostream&, const Product*);
    friend istream& operator>>(istream&, Product*);

    virtual const double getPrice(bool = true) const = 0;
    void setNumberProducts(const int&);
    bool exist(const string&) const;
};
