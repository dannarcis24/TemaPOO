#include "Order.h"

class OrderOperator: public Employee {
    vector<unique_ptr<Order>> orders;
    double bonus = 0;
    unsigned int total_orders = 0;

    void write(ostream&) const;
    void write(ofstream&) const;

public:
    OrderOperator();
    OrderOperator(vector<unique_ptr<Order>>&);
    OrderOperator(const OrderOperator&);
    OrderOperator(OrderOperator&&);

    OrderOperator& operator=(const OrderOperator&);
    OrderOperator& operator=(OrderOperator&&);

    friend ostream& operator<<(ostream&, const shared_ptr<OrderOperator>&);
    friend ostream& operator<<(ostream&, const OrderOperator&);
    friend istream& operator>>(istream&, OrderOperator&);
    friend istream& operator>>(istream&, shared_ptr<OrderOperator>&);
    friend bool operator==(const shared_ptr<OrderOperator>&, const shared_ptr<OrderOperator>&);
    friend bool operator!=(const shared_ptr<OrderOperator>&, const shared_ptr<OrderOperator>&);

    const int salary() const;
    
    void orderAdd(unique_ptr<Order>&);
    void orderFinish();
    const int ordersNumber() const;
    const int allOrders() const;
    double bonus4Orders() const;
};