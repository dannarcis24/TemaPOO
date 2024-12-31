#include "Store.h"

/* FUNCTII PENTRU MODULARIZARE */
int number();
int number(ifstream&);
const string searchID();
const string name();

/* FUNCTII PENTRU GESTIUNEA ANGAJATILOR */
void readEmployeeFromFile(Store&, istream&);
void addEmployee(Store&);
void writeEmployee(Store&, bool = false);

/* FUNCTII PENTRU GESTIUNEA PRODUSELOR */
void readProductFromFile(Store&, istream&);
void addProduct(Store&);
void writeProducts(Store&, bool = false);

/* FUNCTII PENTRU GESTIUNEA COMENZILOR */
vector<unique_ptr<Order>> readOrders(istream&);
void managementOrders(Store&);