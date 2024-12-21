#include "Store.h"
#include <algorithm>
#include <type_traits>
#include <typeinfo>

void Store::validation() const
{
    if(employees.size() < 2)
        throw DynamicException("magazin_nefunctional", "!! magazinul trebuie sa aiba macar un managaer si un asistent !!\n\n");
    
    vector<int> number(2, 0);
    for(auto& i : employees)
    {
        if(i->position() == "manager")
            number[0]++;
        else
            number[1]++;
        
        if(number[0] && number[1])
            break;
    }
    if(number[0] == 0 || number[1] == 0)
        throw DynamicException("magazin_nefunctional", "!! magazinul trebuie sa aiba macar un managaer si un asistent !!\n\n");
    
    if(operators.size() < 3)
        throw DynamicException("magazin_nefunctional", "!! magazinul nu poate functiona fara sa aiba minim 3operatori de comenzi !!\n\n");
    
    if(products.size() < 6)
        throw DynamicException("magazin_nefunctional", "!! magazinul trebuie sa aiba cel putin cate 2produse din fiecare tip !!\n\n");
    
    number = vector(3, 0);
    for(auto& i : products)
    {
        if(typeid(i) == typeid(Clothes))
            number[0]++;
        else
            if(typeid(i) == typeid(Disk))
                number[1]++;
            else
                number[2]++;
        
        if(count_if(number.begin(), number.end(), [](bool x) { return (x >= 2); }) == 3)
            break;
    }
    if(any_of(number.begin(), number.end(), [](bool x) { return (x < 2); }))
        throw DynamicException("magazin_nefunctional", "!! magazinul trebuie sa aiba cel putin cate 2produse din fiecare tip !!\n\n");
}

template<class T1, class T2, class T3, class T4>
void Store::setInfo(const vector<T1>& vec1, const vector<T2>& vec2, const vector<T3>& vec3, const vector<T4>& vec4) 
{
    for(auto& i : vec1)
        if(!is_pointer<T1>::value)
            employees.push_back(&i);

    for(auto& i : vec2)
        if(!is_pointer<T1>::value)
            products.push_back(&i);
    
    for(auto& i : vec3)
        if(is_pointer<T2>::value)
            operators.push(i);
        else
            operators.push(&i);
    
    for(auto& i : vec4)
        if(is_pointer<T3>::value)
            orders.push(i);
        else
            orders.push(&i);

    validation();
}

/* IMPLEMENTARE CONSTRUCTORII */
Store::Store(const vector<Employee>& vec1, const vector<Product>& vec2, const vector<OrderOperator>& vec3, const vector<Order>& vec4) {
    setInfo(vec1, vec2, vec3, vec4);
}

Store::Store(const vector<Employee*>& vec1, const vector<Product>& vec2, const vector<OrderOperator>& vec3, const vector<Order>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee>& vec1, const vector<Product*>& vec2, const vector<OrderOperator>& vec3, const vector<Order>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee>& vec1, const vector<Product>& vec2, const vector<OrderOperator*>& vec3, const vector<Order>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee>& vec1, const vector<Product>& vec2, const vector<OrderOperator>& vec3, const vector<Order*>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee*>& vec1, const vector<Product*>& vec2, const vector<OrderOperator>& vec3, const vector<Order>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee*>& vec1, const vector<Product>& vec2, const vector<OrderOperator*>& vec3, const vector<Order>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee*>& vec1, const vector<Product>& vec2, const vector<OrderOperator>& vec3, const vector<Order*>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee>& vec1, const vector<Product*>& vec2, const vector<OrderOperator*>& vec3, const vector<Order>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee>& vec1, const vector<Product*>& vec2, const vector<OrderOperator>& vec3, const vector<Order*>& vec4) {
    setInfo(vec1, vec2, vec3, vec4);
}

Store::Store(const vector<Employee>& vec1, const vector<Product>& vec2, const vector<OrderOperator*>& vec3, const vector<Order*>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee*>& vec1, const vector<Product*>& vec2, const vector<OrderOperator*>& vec3, const vector<Order>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee*>& vec1, const vector<Product*>& vec2, const vector<OrderOperator>& vec3, const vector<Order*>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee*>& vec1, const vector<Product>& vec2, const vector<OrderOperator*>& vec3, const vector<Order*>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee>& vec1, const vector<Product*>& vec2, const vector<OrderOperator*>& vec3, const vector<Order*>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

Store::Store(const vector<Employee*>& vec1, const vector<Product*>& vec2, const vector<OrderOperator*>& vec3, const vector<Order*>& vec4) {
    setInfo(vec1, vec2, vec3, vec4); 
}

/* IMPLEMENTARE METODE PENTRU GESTIUNEA ANGAJATILOR */
void Store::employeeAdd(Employee* elem)
{
    employees.push_back(elem);
    validation();
}

void Store::employeeAdd(Employee elem)
{
    employees.push_back(&elem);
    validation();
}

Employee* Store::employeeExist(const string& ID) const
{
    if(employees.empty() && operators.empty())
        return nullptr;
    
    for(auto& i = employees.begin(); i != employees.end(); i++)
        if((*i)->exist(ID))
            return *i;

    return nullptr;
}

void Store::employeeDel(const string& ID)
{
    Employee* elem = employeeExist(ID);
    if(elem)
        employees.erase(find(employees.begin(), employees.end(), elem));
    else
    {
        if(operators.empty())
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");

        vector<OrderOperator*> aux;
        bool ok = false;
        for(auto& i = operators.top(); !operators.empty(); operators.pop())
            if(!i->exist(ID))
                aux.push_back(i);
            else
                ok = true;

        for(auto& i : aux)
            operators.push(i);

        if(!ok)
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");
    }
}

void Store::employeeSet(const string&ID, const string& name)
{
    Employee* elem = employeeExist(ID);
    if(elem)
        elem->setName(name);
    else
    {
        if(operators.empty())
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");

        vector<OrderOperator*> aux;
        bool ok = false;
        for(auto& i = operators.top(); !operators.empty(); operators.pop())
            if(!i->exist(ID))
                aux.push_back(i);
            else
            {
                ok = true;
                i->setName(name);
            }

        for(auto& i : aux)
            operators.push(i);

        if(!ok)
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");
    }
}

void Store::employeeInf(const string& ID, ostream& out)
{
    Employee* elem = employeeExist(ID);
    if(elem)
        out<<elem;
    else
    {
        if(operators.empty())
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");

        vector<OrderOperator*> aux;
        bool ok = false;
        for(auto& i = operators.top(); !operators.empty(); operators.pop())
            if(!i->exist(ID))
                aux.push_back(i);
            else
            {
                ok = true;
                out<<i;
            }

        for(auto& i : aux)
            operators.push(i);

        if(!ok)
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");
    }
}

void Store::employeesWrite(ostream& out)
{
    if(employees.empty() && operators.empty())
        throw DynamicException("angajati_inexistenti", "!! magazinul nu are nici un angajat !!\n\n");
    
    for(auto& i : employees)
        out<<i<<'\n';
    
    if(!operators.empty())
    {
        vector<OrderOperator*> aux;
        for(auto& i = operators.top(); !operators.empty(); operators.pop())
        {
            out<<i<<'\n';
            aux.push_back(i);
        }

        for(auto& i : aux)
            operators.push(i);
    }
}   

/* IMPLEMENTARE METODE PENTRU GESTIUNEA PRODUSELOR */