#include "Employee.h"

class Product {
protected:
    string name, ID = "#0";
    unsigned int number_products = 0;
    double price_base = 0;

    static long long number;

    inline virtual void write(ostream&) const;
    inline virtual void read(istream&);

public:
    Product() = default;
    Product(const string, int, double);
    virtual ~Product() = default;

    friend ostream& operator<<(ostream&, const Product*);
    friend istream& operator>>(istream&, Product*);

    virtual const double getPrice(bool = true) const = 0;
    void setNumberProducts(int);
};
