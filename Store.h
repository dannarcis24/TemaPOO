#include "OrderOperator.h"
#include <queue>

class Compare {
public:
    bool operator()(const OrderOperator* elem1, const OrderOperator* elem2) {
        return (elem1->ordersNumber() > elem2->ordersNumber());
    }

    bool operator()(Order* elem1, Order* elem2) {
        return (elem1->getTime(false) > elem2->getTime(false));
    }
};

class Store {
    vector<Employee*> employees;
    priority_queue<OrderOperator*, vector<OrderOperator*>, Compare> operators;
    priority_queue<Order*, vector<Order*>, Compare> orders;

    inline void validation() const;

    template<class T1, class T2, class T3>
    inline void setInfo(const vector<T1>&, const vector<T2>&, const vector<T3>&);

public:
    Store() = default;
    Store(vector<Employee>, vector<OrderOperator>, vector<Order>);
    Store(vector<Employee>, vector<OrderOperator>, vector<Order*>);
    Store(vector<Employee>, vector<OrderOperator*>, vector<Order>);
    Store(vector<Employee>, vector<OrderOperator*>, vector<Order*>);
    Store(vector<Employee*>, vector<OrderOperator>, vector<Order>);
    Store(vector<Employee*>, vector<OrderOperator>, vector<Order*>);
    Store(vector<Employee*>, vector<OrderOperator*>, vector<Order>);
    Store(vector<Employee*>, vector<OrderOperator*>, vector<Order*>);
};