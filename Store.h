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
    vector<Product*> products;
    priority_queue<OrderOperator*, const vector<OrderOperator*>, Compare> operators;
    priority_queue<Order*, const vector<Order*>, Compare> orders;

    inline void validation() const;

    template<class T1, class T2, class T3, class T4>
    inline void setInfo(const vector<T1>&, const vector<T2>&, const vector<T3>&, const vector<T4>&);

public:
    Store() = default;
    Store(const vector<Employee>&, const vector<Product>&, const vector<OrderOperator>&, const vector<Order>&);
    Store(const vector<Employee*>&, const vector<Product>&, const vector<OrderOperator>&, const vector<Order>&);
    Store(const vector<Employee>&, const vector<Product*>&, const vector<OrderOperator>&, const vector<Order>&);
    Store(const vector<Employee>&, const vector<Product>&, const vector<OrderOperator*>&, const vector<Order>&);
    Store(const vector<Employee>&, const vector<Product>&, const vector<OrderOperator>&, const vector<Order*>&);
    Store(const vector<Employee*>&, const vector<Product*>&, const vector<OrderOperator>&, const vector<Order>&);
    Store(const vector<Employee*>&, const vector<Product>&, const vector<OrderOperator*>&, const vector<Order>&);
    Store(const vector<Employee*>&, const vector<Product>&, const vector<OrderOperator>&, const vector<Order*>&);
    Store(const vector<Employee>&, const vector<Product*>&, const vector<OrderOperator*>&, const vector<Order>&);
    Store(const vector<Employee>&, const vector<Product*>&, const vector<OrderOperator>&, const vector<Order*>&);
    Store(const vector<Employee>&, const vector<Product>&, const vector<OrderOperator*>&, const vector<Order*>&);
    Store(const vector<Employee*>&, const vector<Product*>&, const vector<OrderOperator*>&, const vector<Order>&);
    Store(const vector<Employee*>&, const vector<Product*>&, const vector<OrderOperator>&, const vector<Order*>&);
    Store(const vector<Employee*>&, const vector<Product>&, const vector<OrderOperator*>&, const vector<Order*>&);
    Store(const vector<Employee>&, const vector<Product*>&, const vector<OrderOperator*>&, const vector<Order*>&);
    Store(const vector<Employee*>&, const vector<Product*>&, const vector<OrderOperator*>&, const vector<Order*>&);

      //////////////////////////
     /* OPERATII CU ANGAJATI */
    //////////////////////////
    inline void employeeAdd(Employee*);
    inline void employeeAdd(Employee);
    Employee* employeeExist(const string&) const; // cautarea se face doar dupa ID
    void employeeDel(const string&);
    void employeeSet(const string&, const string&);
    inline void employeeInf(const string&, ostream& = cout);
    inline void employeesWrite(ostream& = cout);

      ///////////////////////////
     /* OPERATII CU PRODUSELE */
    ///////////////////////////
    void productAdd(Product*);
    void productAdd(Product);
    bool productExist(const string); // cautarea se face doar dupa ID
    void productDel(const string);
    void productSet(const string, int);
    inline void productInf(const string) const;
    inline void productsWrite() const;
};