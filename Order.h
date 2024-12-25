#include "VintageDisk.h"
#include <vector>

class Order {
    vector<Product*> list;
    Date processing_date;
    string ID = "$0";
    int time;

    static long long number;

    inline void validation(vector<Product>&);
    inline void write(ostream&) const;
    inline void read(istream&);

public:
    Order();
    Order(vector<Product>&, const Date&, int);
    Order(vector<Product>&, const string&, int);
    Order(vector<Product>&, int, int, int, int);

    ~Order();

    friend ostream& operator<<(ostream&, const Order&);
    friend ostream& operator<<(ostream&, const Order*);
    friend istream& operator>>(istream&, Order&);
    friend istream& operator>>(istream&, Order*);

    const int getTime(bool = true);
    const int getPrice() const;
    bool verifStock(vector<Product*>) const;
};