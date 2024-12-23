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
    priority_queue<OrderOperator*, vector<OrderOperator*>, Compare> operators;
    priority_queue<Order*, vector<Order*>, Compare> orders;

    inline void validation() const;

public:
    Store() = default;

      //////////////////////////
     /* OPERATII CU ANGAJATI */
    //////////////////////////
    void employeeAdd(Employee*);
    void employeeAdd(Employee&);
    void employeeAdd(OrderOperator&);
    Employee* employeeExist(const string&) const; // cautarea se face doar dupa ID
    void employeeDel(const string&);
    void employeeSet(const string&, const string&);
    void employeeInf(const string&, ostream& = cout);
    void employeesWrite(ostream& = cout);

      /////////////////////////
     /* OPERATII CU PRODUSE */
    /////////////////////////
    void productAdd(Product*);

    template<class T>
    void productAdd(T&);
    vector<Product*>::const_iterator productExist(const string&) const; // cautarea se face doar dupa ID
    void productDel(const string&);
    void productSet(const string&, int);
    void productInf(const string&, ostream& = cout) const;
    void productsWrite(ostream& = cout) const;

      /////////////////////////
     /* OPERATII CU COMENZI */
    /////////////////////////
};