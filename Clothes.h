#include "Product.h"

class Clothes: public Product{
    string color, brand;

public:
    Clothes() = default;
    Clothes(const string&, int, int, const string&, const string&);

    friend ostream& operator<<(ostream&, const Clothes&);
    friend istream& operator>>(istream&, Clothes&);
    friend istream& operator>>(istream&, Clothes*);
    friend bool operator==(const Clothes&, const Clothes&);
    friend bool operator!=(const Clothes&, const Clothes&);

    const double getPrice(bool = true) const;

private:
    void write(ostream&) const;
    void read(istream&);
    bool isEqual(const Product&) const;
};