#include "Store.h"
#include <algorithm>

unsigned long long Store::orders_processed = 0;

void Store::validationEmployees() const
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
}

void Store::validationProducts() const
{
    vector<int> number = vector<int>(3, 0);
    for(auto& i : products)
    {
        if(typeid(i) == typeid(Clothes))
            number[0] += i->getNumber();
        else
            if(typeid(i) == typeid(Disk))
                number[1] += i->getNumber();
            else
                number[2] += i->getNumber();
        
        if(count_if(number.begin(), number.end(), [](bool x) { return (x >= 2); }) == 3)
            break;
    }
    if(any_of(number.begin(), number.end(), [](bool x) { return (x < 2); }))
        throw DynamicException("magazin_nefunctional", "!! magazinul trebuie sa aiba cel putin cate 2produse din fiecare tip !!\n\n");
}

void Store::validation() const{
    validationEmployees();
    validationProducts();
}

Store::~Store()
{
    for(auto& i : employees)
        delete i;
    
    for(auto& i : products)
        delete i;
    
    for(auto i = operators.top(); !operators.empty(); operators.pop())
        delete i;

    for(auto i = orders.top(); !orders.empty(); orders.pop())
        delete i;
}

/* IMPLEMENTARE METODE PENTRU GESTIUNEA ANGAJATILOR */
void Store::employeeAdd(Employee* elem) {
    if(elem->position() == "operator comenzi")
        operators.push(dynamic_cast<OrderOperator*>(elem));
    else
        employees.push_back(elem);
}

void Store::employeeAdd(OrderOperator* elem) {
    operators.push(elem);
}

void Store::employeeAdd(Employee& elem) {
    employees.push_back(&elem);
}

void Store::employeeAdd(OrderOperator& elem) {
    operators.push(&elem);
}

Employee* Store::employeeExist(const string& ID) const
{
    if(employees.empty())
        return nullptr;
    
    for(auto i = employees.begin(); i != employees.end(); i++)
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
        for(; !operators.empty(); operators.pop())
        {
            auto i = operators.top();

            if(i->exist(ID))
            {
                ok = true;
                operators.pop();
                break;
            }

            aux.push_back(i);
        }

        for(auto& i : aux)
            operators.push(i);

        if(!ok)
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");
    }
    validationEmployees();
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
        for(; !operators.empty(); operators.pop())
        {
            auto i = operators.top();

            if(i->exist(ID))
            {
                ok = true;
                i->setName(name);
                operators.pop();
                operators.push(i);
                break;
            }

            aux.push_back(i);
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
        for(; !operators.empty(); operators.pop())
        {   
            auto i = operators.top();

            if(i->exist(ID))
            {
                operators.pop();
                operators.push(i);
                ok = true;
                out<<i;
                break;
            }

            aux.push_back(i);
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
        for(; !operators.empty(); operators.pop())
        {
            auto i = operators.top();
            out<<i<<'\n';
            aux.push_back(i);
        }

        for(auto& i : aux)
            operators.push(i);
    }
}   

/* IMPLEMENTARE METODE PENTRU GESTIUNEA PRODUSELOR */
void Store::productAdd(Product* elem) {
    products.push_back(elem);
}

template<class T>
void Store::productAdd(T& elem)
{
    auto aux = typeid(elem);
    if(aux == typeid(Clothes) || aux == typeid(Disk) || aux == typeid(VintageDisk))
        products.push_back(&elem);
    else
        throw DynamicException("produs_inexistent", "!! produsul nu exista in stocul magazinului !!\n\n");
}

vector<Product*>::const_iterator Store::productExist(const string& ID) const {
    return find_if(products.begin(), products.end(), [&ID](Product* x) { return x->exist(ID);});
}

void Store::productDel(const string& ID)
{
    vector<Product*>::const_iterator elem = productExist(ID);
    if(elem != products.end())
        products.erase(elem);
    else
        throw DynamicException("produs_inexistent", "!! produsul cu ID ul " + ID + " nu exista in stocul magazinului !!\n\n");
    validationProducts();
}

void Store::productSet(const string& ID, int number)
{
    vector<Product*>::const_iterator elem = productExist(ID);
    if(elem != products.end())
        (*elem)->setNumberProducts(number);
    else
        throw DynamicException("produs_inexistent", "!! produsul cu ID ul " + ID + " nu exista in stocul magazinului !!\n\n");
}

void Store::productInf(const string& ID, ostream& out) const
{
    vector<Product*>::const_iterator elem =  productExist(ID);
    if(elem != products.end())
        out<<*elem;
    else
        throw DynamicException("produs_inexistent", "!! produsul cu ID ul " + ID + " nu exista in stocul magazinului !!\n\n");
}

void Store::productsWrite(ostream& out) const
{
    if(products.empty())
        throw DynamicException("produse_inexistente", "!! magazinul nu are nici un produs in stoc !!\n\n");
    
    for(auto& i : products)
        out<<i<<'\n';
}

/* IMPLEMENTARE METODE PENTRU GESTIUNEA COMENZILOR */
void Store::orderAdd(const vector<Order*>& elem) {
    for(auto& i : elem)
        orders.push(i);
}

bool Store::orderExist() const {
    return (!orders.empty() || (operators.top())->ordersNumber());
}

int Store::orderNumber() 
{
    vector<Order*> vec;

    for(vec.push_back(orders.top()); !orders.empty(); orders.pop())
        ;
    orderAdd(vec);

    return vec.size();
}

void Store::order2Operator()
{
    if(orders.empty())
        throw DynamicException("comanda_inexistenta", "!! nu mai exista comenzi d procesat !!\n\n");

    for(; !orders.empty() && (operators.top())->ordersNumber() < 4; orders.pop())
    {
        Order* order = orders.top();

        bool ok = order->verifStock(products);
        auto back = products.begin();
        for(auto i = products.begin(); i != products.end(); back = i, i++)
            if((*i)->getNumber() == 0)
            {
                products.erase(i);
                i = back;
            }

        OrderOperator* aux = operators.top();
        aux->orderAdd(order);
        operators.pop();
        operators.push(aux);

        Store::orders_processed++;
    }
}

void Store::orderFinish(ostream& out)
{
    vector<OrderOperator*> vec;
    for(; !orders.empty(); operators.pop())
        vec.push_back(operators.top());
    
    out<<"Numarul de comenzi al fiecarui operator: ";
    for(auto elem : vec)
    {
        elem->orderFinish();
        operators.push(elem);

        out<<elem->ordersNumber()<<' ';
    }
    out<<'\n';
}

void Store::ordersDel() {
    while(!orders.empty())
        orders.pop();
}

/* IMPLEMENTARE METODE PENTRU GESTIUNEA RAPOARTELOR */
void Store::writeMostOrders()
{
    if(operators.empty())
    {
        cout<<"raport_invalid: !! nu exista nici un anagjat de tipul OPERATOR DE COMENZI !!\n\n";
        return;
    }

    ofstream out("employee_the_most_orders_processed.csv");
    if(!out.is_open())
        cout<<"eroare_fisier !! nu se poate deschide fisierul !!";
    else
    {
        vector<OrderOperator*> vec;
        for(; !operators.empty(); operators.pop())
            vec.push_back(operators.top());
        for(auto i : vec)
            operators.push(i);
    
        vector<OrderOperator*>::iterator ma = max(vec.begin(), vec.end(), 
                [](vector<OrderOperator*>::iterator elem1, vector<OrderOperator*>::iterator elem2) { return ((*elem1)->allOrders() > (*elem2)->allOrders());});
        if((*ma)->allOrders() == 0)
            cout<<"raport_invalid: !! nu s-a realizat nici o procesare de comenzi !!\n\n";
        else
        {
            out<<*ma;
            cout<<"Raportul a fost creat cu succes!";
        }
        
        out.close();
    }
}

void Store::writeMostExpensive()
{
    if(operators.empty())
    {
        cout<<"raport_invalid: !! nu exista nici un anagjat de tipul OPERATOR DE COMENZI !!\n\n";
        return;
    }
    
    ofstream out("employee_the_most_expensive_orders.csv");
    if(!out.is_open())
        cout<<"eroare_fisier !! nu se poate deschide fisierul !!";
    else
    {
        vector<OrderOperator*> vec;
        for(; !operators.empty(); operators.pop())
            vec.push_back(operators.top());
        for(auto i : vec)
            operators.push(i);

        if(!count_if(vec.begin(), vec.end(), [](const OrderOperator* i) { return !(i->allOrders());}))
            cout<<"raport_invalid: !! nu s-a realizat nici o procesare de comenzi !!\n\n";
        else
        {
            sort(vec.begin(), vec.end(), [](const OrderOperator* elem1, const OrderOperator* elem2) { return (elem1->bonus4Orders() > elem2->bonus4Orders());});
            out<<vec[0]<<'\n'<<vec[1]<<'\n'<<vec[2];
        }
        
        out.close();
    }
}

void Store::writeBigSalary()
{
    if(employees.empty() && operators.empty())
    {
        cout<<"raport_invalid: !! magazinul nu are nici un angajat !!\n\n";
        return;
    }

    ofstream out("employees_the_highest_salary.csv");
    if(!out.is_open())
        cout<<"eroare_fisier !! nu se poate deschide fisierul !!";
    else
    {
        vector<Employee*> vec;
        for(; !operators.empty(); operators.pop())
            vec.push_back(operators.top());
        for(auto i : vec)
            operators.push(dynamic_cast<OrderOperator*>(i));

        vec.insert(vec.end(), employees.begin(), employees.end());
        sort(vec.begin(), vec.end(), [](const Employee* elem1, const Employee* elem2) { return (elem1->salary() > elem2->salary());});
        sort(vec.begin(), vec.begin() + 3, [](const Employee* elem1, const Employee* elem2) { return compareByName(elem1, elem2);});

        out<<vec[0]<<'\n'<<vec[1]<<'\n'<<vec[2];
        out.close();
        cout<<"Raportul a fost creat cu succes!";
    }
}