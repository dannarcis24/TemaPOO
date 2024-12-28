#include "Employee.h"

class Product {
protected:
    string name, ID = "#0";
    unsigned int number_products = 0;
    double price_base = 0;

    static long long number;

    virtual void write(ostream&) const;
    virtual void write(ofstream&) const;
    virtual void read(istream&);
    virtual bool isEqual(const Product&) const;

public:
    Product();
    Product(const string&, int, double);
    virtual ~Product() = default;

    friend ostream& operator<<(ostream&, const Product*);
    friend istream& operator>>(istream&, Product*);
    friend bool compare(const Product*, const Product*);

    virtual const double getPrice(bool = true) const = 0;

    void setNumberProducts(const int&);
    bool exist(const string&) const;
    const int getNumber() const;
};