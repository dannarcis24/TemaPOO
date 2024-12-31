#include "VintageDisk.h"
#include <vector>

class Order {
    vector<unique_ptr<Product>> list;
    Date processing_date = Date::currentDate();
    string ID = "$0";
    int time;

    static long long number;

    inline void validation(vector<unique_ptr<Product>>&);
    inline void write(ostream&) const;
    inline void read(istream&);

public:
    Order();
    Order(vector<unique_ptr<Product>>&, int);
    Order(const Order&);
    Order(Order&&);

    Order& operator=(const Order&);
    Order& operator=(Order&&);

    friend ostream& operator<<(ostream&, const Order&);
    friend ostream& operator<<(ostream&, const unique_ptr<Order>&);
    friend istream& operator>>(istream&, Order&);
    friend istream& operator>>(istream&, unique_ptr<Order>&);

    const int getTime(bool = true);
    const double getPrice() const;
    bool verifStock(vector<unique_ptr<Product>>&) const;
};