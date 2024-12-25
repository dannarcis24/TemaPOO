#include "OrderOperator.h"

OrderOperator::OrderOperator(vector<Order>& vec)
{
    if(vec.size() > 3)
        throw DynamicException("cerere_invalida", "!! un operator de comenzi nu poate gestiona mai mult de 3comenzi in paralel !!\n\n");
    
    if(!vec.empty())
        for(auto i = vec.begin(); i != vec.end(); i++)
            orders.push_back(&(*i));
}

OrderOperator::~OrderOperator()
{
    for(auto& i : orders)
        delete i;
}

const int OrderOperator::salary() const {
    return (Employee::salary() + bonus);
}

void OrderOperator::orderAdd(Order* elem)
{
    if(orders.size() == 3)
        throw DynamicException("cerere_invalida", "!! un operator de comenzi nu poate gestiona mai mult de 3comenzi in paralel !!\n\n");
    
    orders.push_back(elem);
}

void OrderOperator::orderFinish()
{
    if(orders.empty())  return;

    for(auto i = orders.begin(); i != orders.end();)
        if((*i)->getTime() == 0)
        {
            total_orders++;
            bonus += 0.005 * (*i)->getPrice();

            orders.erase(i);
        }
        else
            i++;
}

void OrderOperator::write(ostream& out) const
{
    Employee::write(out);
    out<<"\nInformatii privind gestiunea operatorului\nNumarul total de comenzi procesate: "<<total_orders<<"\nBonusul acumulat, in urma comenzilor realizate: "<<bonus;
}

void OrderOperator::write(ofstream& out) const {
    out<<','<<total_orders<<','<<bonus;
}

ostream& operator<<(ostream& out, const OrderOperator* elem) 
{
    elem->write(out);
    return out;
}

ostream& operator<<(ostream& out, const OrderOperator elem)
{
    elem.write(out);
    return out;
}

istream& operator>>(istream& in, OrderOperator& elem)
{
    OrderOperator aux;
    aux.read(in);
    if(Employee::coefficient != 1)
        throw DynamicException("pozitie_invalida", "!! pentru a retine un manager sau asistent trebuie sa folositi tipul Employee !!\n\n");
    elem = aux;

    return in;
}

istream& operator>>(istream& in, OrderOperator* elem)
{
    OrderOperator aux;
    aux.read(in);
    *elem = aux;
    
    return in;
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