#include "OrderOperator.h"
#include <queue>

class Compare {
public:
    bool operator()(const shared_ptr<OrderOperator>& elem1, const shared_ptr<OrderOperator>& elem2) {
        return (elem1->ordersNumber() > elem2->ordersNumber());
    }

    bool operator()(const unique_ptr<Order>& elem1, const unique_ptr<Order>& elem2) {
        return (elem1->getTime(false) > elem2->getTime(false));
    }
};

class Store {
    vector<shared_ptr<Employee>> employees;
    vector<unique_ptr<Product>> products;
    priority_queue<shared_ptr<OrderOperator>, vector<shared_ptr<OrderOperator>>, Compare> operators;
    priority_queue<unique_ptr<Order>, vector<unique_ptr<Order>>, Compare> orders;

    static unsigned long long orders_processed;

    inline void validationEmployees() const;
    inline void validationProducts() const;
    vector<shared_ptr<OrderOperator>> queue2Vec();

public:
    Store() = default;

    void validation() const;

      //////////////////////////
     /* OPERATII CU ANGAJATI */
    //////////////////////////
    void employeeAdd(unique_ptr<Employee>&);
    void employeeAdd(unique_ptr<OrderOperator>&);
    vector<shared_ptr<Employee>>::const_iterator employeeExist(const string&) const; // cautarea se face doar dupa ID
    void employeeDel(const string&);
    void employeeSet(const string&, const string&);
    void employeeSet(const string&, string&&);
    void employeeInf(const string&, ostream& = cout);
    void employeesWrite(ostream& = cout);

      /////////////////////////
     /* OPERATII CU PRODUSE */
    /////////////////////////
    void productAdd(unique_ptr<Product>&);
    vector<unique_ptr<Product>>::const_iterator productExist(const string&) const; // cautarea se face doar dupa ID
    void productDel(const string&);
    void productSet(const string&, const int);
    void productInf(const string&, ostream& = cout) const;
    void productsWrite(ostream& = cout) const;

      /////////////////////////
     /* OPERATII CU COMENZI */
    /////////////////////////
    void orderAdd(vector<unique_ptr<Order>>&&);
    bool orderExist();
    int orderNumber();
    void order2Operator();
    void orderFinish(ostream& = cout);
    void ordersDel();

      ///////////////////////
     /* OPERATII RAPOARTE */
    ///////////////////////
    void writeMostOrders();
    void writeMostExpensive();
    void writeBigSalary();
};