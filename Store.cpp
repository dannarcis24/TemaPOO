#include "Store.h"
#include <type_traits>

void Store::validation() const
{
    if(employees.size() < 2)
        throw DynamicException("magazin_nefunctional", "!! magazinul trebuie sa aiba macar un managaer si un asistent !!\n\n");
    if(operators.size() < 3)
        throw DynamicException("magazin_nefunctional", "!! magazinul nu poate functiona fara sa aiba minim 3operatori de comenzi !!\n\n");

}

template<class T1, class T2, class T3>
void Store::setInfo(const vector<T1>& vec1, const vector<T2>& vec2, const vector<T3>& vec3) 
{
    for(auto& i : vec1)
        if(!is_pointer<T1>::value)
            employees.push_back(&(*i));
    
    for(auto& i : vec2)
        if(is_pointer<T2>::value)
            operators.push(&(*i));
        else
        {
            OrderOperator* aux = *i;
            operators.push(aux);
        }
    
    for(auto& i : vec3)
        if(is_pointer<T3>::value)
            orders.push(&(*i));
        else
        {
            Order* aux = *i;
            orders.push(aux);
        }

    validation();
}

Store::Store(vector<Employee> vec1, vector<OrderOperator> vec2, vector<Order> vec3) {
    setInfo(vec1, vec2, vec3);
}

Store::Store(vector<Employee> vec1, vector<OrderOperator> vec2, vector<Order*> vec3) {
    setInfo(vec1, vec2, vec3);
}

Store::Store(vector<Employee> vec1, vector<OrderOperator*> vec2, vector<Order> vec3) {
    setInfo(vec1, vec2, vec3);
}

Store::Store(vector<Employee> vec1, vector<OrderOperator*> vec2, vector<Order*> vec3) {
    setInfo(vec1, vec2, vec3);
}

Store::Store(vector<Employee*> vec1, vector<OrderOperator> vec2, vector<Order> vec3): employees(vec1) {
    setInfo(vec1, vec2, vec3);
}

Store::Store(vector<Employee*> vec1, vector<OrderOperator> vec2, vector<Order*> vec3): employees(vec1) {
    setInfo(vec1, vec2, vec3);
}

Store::Store(vector<Employee*> vec1, vector<OrderOperator*> vec2, vector<Order> vec3): employees(vec1) {
    setInfo(vec1, vec2, vec3);
}

Store::Store(vector<Employee*> vec1, vector<OrderOperator*> vec2, vector<Order*> vec3): employees(vec1) {
    setInfo(vec1, vec2, vec3);
}