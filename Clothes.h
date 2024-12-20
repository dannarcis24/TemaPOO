#include "Product.h"

class Clothes: public Product{
    string color, brand;

public:
    Clothes() = default;
    Clothes(const string, int, double, const string, const string);

    friend ostream& operator<<(ostream&, const Clothes&);
    friend istream& operator>>(istream&, Clothes&);

    const double getPrice(bool = true) const;

private:
    void write(ostream&) const;
    void read(istream&);
};