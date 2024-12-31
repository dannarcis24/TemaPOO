#include "Product.h"

class Clothes: public Product{
    string color, brand;

public:
    Clothes() = default;
    Clothes(const string&, int, double, const string&, const string&);
    Clothes(const Product&, const string&, const string&);

    friend ostream& operator<<(ostream&, const Clothes&);
    friend ostream& operator<<(ostream&, const unique_ptr<Clothes>&);
    friend istream& operator>>(istream&, Clothes&);
    friend istream& operator>>(istream&, unique_ptr<Clothes>&);
    friend bool operator==(const Clothes&, const Clothes&);
    friend bool operator!=(const Clothes&, const Clothes&);

    const double getPrice(bool = true) const;

private:
    void write(ostream&) const;
    void write(ofstream&) const;
    void read(istream&);
    bool isEqual(const Product&) const;
};