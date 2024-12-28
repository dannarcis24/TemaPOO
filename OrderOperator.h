#include "Order.h"

class OrderOperator: public Employee {
    vector<Order*> orders;
    double bonus = 0;
    unsigned int total_orders = 0;

    void write(ostream&) const;
    void write(ofstream&) const;

public:
    OrderOperator();
    OrderOperator(vector<Order>&);

    ~OrderOperator();

    friend ostream& operator<<(ostream&, const OrderOperator*);
    friend ostream& operator<<(ostream&, const OrderOperator&);
    friend istream& operator>>(istream&, OrderOperator&);
    friend istream& operator>>(istream&, OrderOperator*);

    const int salary() const;
    
    void orderAdd(Order*);
    void orderFinish();
    const int ordersNumber() const;
    const int allOrders() const;
    double bonus4Orders() const;
};