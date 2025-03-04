#include "OrderOperator.h"

OrderOperator::OrderOperator() {
    coefficient = 1;
    job = true;
}

OrderOperator::OrderOperator(vector<unique_ptr<Order>>& vec)
{
    if(vec.size() > 3)
        throw DynamicException("cerere_invalida", "!! un operator de comenzi nu poate gestiona mai mult de 3comenzi in paralel !!\n\n");
    
    if(!vec.empty())
        for(auto i = vec.begin(); i != vec.end(); i++)
            orders.push_back(move(*i));
}

OrderOperator::OrderOperator(const OrderOperator& elem): Employee(elem), bonus(elem.bonus), total_orders(elem.total_orders) {
    for(auto i = elem.orders.begin(); i != elem.orders.end(); i++)
        orders.push_back(make_unique<Order>(**i));
}

OrderOperator::OrderOperator(OrderOperator&& elem): Employee(move(elem)), bonus(elem.bonus), total_orders(elem.total_orders) {
    orders = move(elem.orders);
}

OrderOperator& OrderOperator::operator=(const OrderOperator& elem)
{
    if(this == &elem)
        return *this;

    Employee::operator=(elem);
    bonus = elem.bonus;
    total_orders = elem.total_orders;

    orders.clear();
    for(auto i = elem.orders.begin(); i != elem.orders.end(); i++)
        orders.push_back(make_unique<Order>(**i));

    return *this;
}

OrderOperator& OrderOperator::operator=(OrderOperator&& elem)
{
    if(this == &elem)
        return *this;

    Employee::operator=(move(elem));
    bonus = move(elem.bonus);
    total_orders = move(elem.total_orders);
    orders.clear();
    orders = move(elem.orders);

    return *this;
}

const int OrderOperator::salary() const {
    return (Employee::salary() + bonus);
}

void OrderOperator::orderAdd(unique_ptr<Order>& elem)
{
    if(orders.size() == 3)
        throw DynamicException("cerere_invalida", "!! un operator de comenzi nu poate gestiona mai mult de 3comenzi in paralel !!\n\n");
    
    orders.push_back(move(elem));
}

void OrderOperator::orderFinish()
{
    if(orders.empty())  
        return;

    unsigned work = orders.size(), finish = work;
    for(auto i = orders.begin(); i != orders.end();)
        if((*i)->getTime() == 0)
        {
            total_orders++;
            work--;
            bonus += 0.005 * (*i)->getPrice();

            i = orders.erase(i);
        }
        else
        {
            i++;
            finish--;
        }
    
    cout<<"Operatorul de comenzi cu ID ul "<<ID<<" a finalizat "<<finish<<" comenzi si mare are de terminat "<<work<<" comenzi de impachetat si livrat.\n";
}

void OrderOperator::write(ostream& out) const
{
    Employee::write(out);
    out<<"\nInformatii privind gestiunea operatorului\nNumarul total de comenzi procesate: "<<total_orders<<"\nBonusul acumulat, in urma comenzilor realizate: "<<bonus<<'\n';
}

void OrderOperator::write(ofstream& out) const {
    Employee::write(out);
    out<<','<<total_orders<<','<<bonus;
}

ostream& operator<<(ostream& out, const shared_ptr<OrderOperator>& elem) 
{
    if(auto* aux = dynamic_cast<ofstream*>(&out))
        elem->write(*aux);
    else
        elem->write(out);
    return out;
}

ostream& operator<<(ostream& out, const OrderOperator& elem)
{
    if(auto* aux = dynamic_cast<ofstream*>(&out))
        elem.write(*aux);
    else
        elem.write(out);
    return out;
}

istream& operator>>(istream& in, OrderOperator& elem)
{
    OrderOperator aux;
    try{ aux.read(in);
        if(elem.coefficient != 1)
            throw DynamicException("pozitie_invalida", "!! pentru a retine un manager sau asistent trebuie sa folositi tipul Employee !!\n\n");
    } catch(const exception&) { Employee::number--; throw;}
    elem = aux;

    return in;
}

istream& operator>>(istream& in, shared_ptr<OrderOperator>& elem)
{
    OrderOperator aux;
    aux.read(in);
    *elem = aux;
    
    return in;
}

bool operator==(const shared_ptr<OrderOperator>& elem1, const shared_ptr<OrderOperator>& elem2) {
    return (elem1->CNP == elem2->CNP);
}

bool operator!=(const shared_ptr<OrderOperator>& elem1, const shared_ptr<OrderOperator>& elem2) {
    return !(elem1 == elem2);
}

const int OrderOperator::ordersNumber() const {
    return orders.size();
}

const int OrderOperator::allOrders() const {
    return total_orders;
}

double OrderOperator::bonus4Orders() const {
    return (bonus * total_orders);
}
