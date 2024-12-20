#include "Order.h"

class OrderOperator: public Employee {
    vector<Order*> orders;
    unsigned int bonus = 0, total_orders = 0;

    void write(ostream&) const;

public:
    OrderOperator() = default;
    OrderOperator(vector<Order>);

    friend ostream& operator<<(ostream&, const OrderOperator*);
    friend ostream& operator<<(ostream&, const OrderOperator);

    const int salary() const;
    
    void orderAdd(Order&);
    void orderFinish();
};