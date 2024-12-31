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
}

void Store::validationProducts() const
{
    vector<int> number = vector<int>(3, 0);
    for(auto i = products.begin(); i != products.end(); i++)
    {
        if(typeid(**i) == typeid(Clothes))
            number[0]++;
        else
            if(typeid(**i) == typeid(Disk))
                number[1]++;
            else
                number[2]++;
        
        if(count_if(number.begin(), number.end(), [](int x) { return (x >= 2); }) == 3)
            break;
    }

    if(any_of(number.begin(), number.end(), [](int x) { return (x < 2);}))
        throw DynamicException("magazin_nefunctional", "!! magazinul trebuie sa aiba cel putin cate 2produse din fiecare tip !!\n\n");
}

void Store::validation() const{
    validationEmployees();
    validationProducts();
}

/* IMPLEMENTARE METODE PENTRU GESTIUNEA ANGAJATILOR */
vector<shared_ptr<OrderOperator>> Store::queue2Vec()
{
    vector<shared_ptr<OrderOperator>> vec;
    if(operators.empty())
        return vec;

    vector<shared_ptr<OrderOperator>> aux;
    bool ok = false;
    for(; !operators.empty(); operators.pop())
        vec.push_back(operators.top());

    for(auto i : vec)
        operators.push(i);

    return vec;
}

void Store::employeeAdd(unique_ptr<Employee>& elem) {
    if(elem->position() == "operator comenzi")
    {
        shared_ptr<Employee> aux = move(elem);
        operators.push(dynamic_pointer_cast<OrderOperator>(move(aux)));
    }
    else
        employees.push_back(move(elem));
}

void Store::employeeAdd(unique_ptr<OrderOperator>& elem) {
    operators.push(move(elem));
}

void Store::employeeAdd(Employee& elem) {
    employees.push_back(make_unique<Employee>(elem));
}

void Store::employeeAdd(Employee&& elem) {
    employees.push_back(make_unique<Employee>(move(elem)));
}

void Store::employeeAdd(OrderOperator& elem) {
    operators.push(make_shared<OrderOperator>(elem));
}

void Store::employeeAdd(OrderOperator&& elem) {
    operators.push(make_shared<OrderOperator>(move(elem)));
}

vector<shared_ptr<Employee>>::const_iterator Store::employeeExist(const string& ID) const {
    return find_if(employees.begin(), employees.end(), [&ID](const shared_ptr<Employee>& x) { return x->exist(ID);});
}

void Store::employeeDel(const string& ID)
{
    auto&& elem = employeeExist(ID);
    if(elem != employees.end()) 
        employees.erase(elem);
    else
    {
        if(operators.empty())
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");

        vector<shared_ptr<OrderOperator>> aux;
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
        aux.clear();

        if(!ok)
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");
    }
    validationEmployees();
}

void Store::employeeSet(const string& ID, string&& name)
{
    auto&& elem = employeeExist(ID);
    if(elem != employees.end())
        (*elem)->setName(move(name));
    else
    {
        if(operators.empty())
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");

        vector<shared_ptr<OrderOperator>> vec = queue2Vec();
        auto&& elem1 = find_if(vec.begin(), vec.end(), [&ID](const shared_ptr<OrderOperator>& x) { return x->exist(ID);});
        if(elem1 == vec.end())
        {
            vec.clear();
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");
        }
        (*elem1)->setName(move(name));
        vec.clear();
    }
}

void Store::employeeSet(const string& ID, const string& name) {
    employeeSet(ID, string(name));    
}

void Store::employeeInf(const string& ID, ostream& out)
{
    auto&& elem = employeeExist(ID);
    if(elem != employees.end())
        out<<*elem;
    else
    {
        if(operators.empty())
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");

        vector<shared_ptr<OrderOperator>> vec = queue2Vec();
        auto&& elem1 = find_if(vec.begin(), vec.end(), [&ID](const shared_ptr<OrderOperator>& x) { return x->exist(ID);});
        if(elem1 == vec.end())
        {
            vec.clear();
            throw DynamicException("angajat_inexistent", "!! angajatul cu ID ul " + ID + " nu exista !!\n\n");
        }
        cout<<*elem1;
        vec.clear();
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
        vector<shared_ptr<OrderOperator>> vec;
        for(; !operators.empty(); operators.pop())
        {
            auto i = operators.top();
            out<<i<<'\n';
            vec.push_back(move(i));
        }

        for(auto& i : vec)
            operators.push(move(i));
        vec.clear();
    }
}   

/* IMPLEMENTARE METODE PENTRU GESTIUNEA PRODUSELOR */
void Store::productAdd(unique_ptr<Product>& elem) {
    products.push_back(move(elem));
}

template<class T>
void Store::productAdd(T&& elem)
{
    auto aux = typeid(elem);
    if(aux == typeid(Clothes) || aux == typeid(Disk) || aux == typeid(VintageDisk))
    {
        unique_ptr<Product> aux1;
        if(aux == typeid(Clothes))
            aux1 = make_unique<Clothes>(move(elem));
        else
            if(aux == typeid(Disk))
                aux1 = make_unique<Disk>(move(elem));
            else
                aux1 = make_unique<VintageDisk>(move(elem));
        
        products.push_back(move(aux1));
    }
    else
        throw DynamicException("produs_inexistent", "!! produsul nu exista in stocul magazinului !!\n\n");
}

template<class T>
void Store::productAdd(T& elem)
{
    auto aux = typeid(elem);
    if(aux == typeid(Clothes) || aux == typeid(Disk) || aux == typeid(VintageDisk))
        productAdd(T(elem));
    else
        throw DynamicException("produs_inexistent", "!! produsul nu exista in stocul magazinului !!\n\n");
}

vector<unique_ptr<Product>>::const_iterator Store::productExist(const string& ID) const {
    return find_if(products.begin(), products.end(), [&ID](const unique_ptr<Product>& x) { return x->exist(ID);});
}

void Store::productDel(const string& ID)
{
    auto&& elem = productExist(ID);
    if(elem != products.end())
        products.erase(elem);
    else
        throw DynamicException("produs_inexistent", "!! produsul cu ID ul " + ID + " nu exista in stocul magazinului !!\n\n");
    validationProducts();
}

void Store::productSet(const string& ID, const int number)
{
    auto&& elem = productExist(ID);
    if(elem != products.end())
        (*elem)->setNumberProducts(number);
    else
        throw DynamicException("produs_inexistent", "!! produsul cu ID ul " + ID + " nu exista in stocul magazinului !!\n\n");
}

void Store::productInf(const string& ID, ostream& out) const
{
    auto&& elem =  productExist(ID);
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
void Store::orderAdd(vector<unique_ptr<Order>>&& elem) {
    for(auto i = elem.begin(); i != elem.end(); i++)
        orders.push(move(*i));
    elem.clear();
}

bool Store::orderExist() {
    if(orders.empty())
    {
        vector<shared_ptr<OrderOperator>> vec = queue2Vec();
        int nr = count_if(vec.begin(), vec.end(), [](const shared_ptr<OrderOperator>& elem) {return (elem->ordersNumber() != 0);});
        vec.clear();

        return (nr > 0);
    }
    
    return true;
}

int Store::orderNumber()  {
    return orders.size();
}

void Store::order2Operator()
{
    if(orders.empty())
        throw DynamicException("comanda_inexistenta", "!! nu mai exista comenzi de procesat !!\n");

    for(; !orders.empty() && (operators.top())->ordersNumber() < 3; orders.pop())
    {
        unique_ptr<Order> order = move(const_cast<unique_ptr<Order>&>(orders.top()));
        cout<<"Comanda a fost asignata unui operator de comenzi\n"<<order;

        bool ok = order->verifStock(products);
        if(!ok)
            continue;

        shared_ptr<OrderOperator> aux = operators.top();
        aux->orderAdd(order);
        operators.pop();
        operators.push(aux);

        Store::orders_processed++;
    }
}

void Store::orderFinish(ostream& out)
{
    vector<shared_ptr<OrderOperator>> vec = queue2Vec();
    vector<int> number(vec.size());
    int i = 0;
    
    for(auto elem : vec)
    {
        elem->orderFinish();
        number[i++] = elem->ordersNumber();
    }
    out<<"Numarul de comenzi al fiecarui operator: ";
    for(int j = 0; j < i; j++)
        out<<number[j]<<' ';
    out<<'\n';
    
    vec.clear();
    number.clear();
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
        vector<shared_ptr<OrderOperator>> vec = queue2Vec();
    
        vector<shared_ptr<OrderOperator>>::iterator ma = max_element(vec.begin(), vec.end(), 
                [](const shared_ptr<OrderOperator>& elem1, const shared_ptr<OrderOperator>& elem2) { return (elem1->allOrders() < elem2->allOrders());});
        if((*ma)->allOrders() == 0)
            cout<<"raport_invalid: !! nu s-a realizat nici o procesare de comenzi !!\n\n";
        else
        {
            out<<*ma;
            cout<<"Raportul a fost creat cu succes!";
        }
        
        vec.clear();
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
        vector<shared_ptr<OrderOperator>> vec = queue2Vec();

        if(!Store::orders_processed)
            cout<<"raport_invalid: !! nu s-a realizat nici o procesare de comenzi !!\n\n";
        else
        {
            sort(vec.begin(), vec.end(), [](const shared_ptr<OrderOperator>& elem1, const shared_ptr<OrderOperator>& elem2) { return (elem1->bonus4Orders() > elem2->bonus4Orders());});
            out<<vec[0]<<'\n'<<vec[1]<<'\n'<<vec[2];
        }
        
        vec.clear();
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
        vector<shared_ptr<OrderOperator>> aux = queue2Vec();
        vector<shared_ptr<Employee>> vec;
        for(auto& i : aux)
            vec.push_back(move(i));
        aux.clear();

        vec.insert(vec.end(), employees.begin(), employees.end());
        sort(vec.begin(), vec.end(), [](const shared_ptr<Employee> elem1, const shared_ptr<Employee> elem2) { return (elem1->salary() > elem2->salary());});
        sort(vec.begin(), vec.begin() + 3, [](const shared_ptr<Employee> elem1, const shared_ptr<Employee> elem2) { return compareByName(elem1, elem2);});

        out<<vec[0]<<'\n'<<vec[1]<<'\n'<<vec[2];
        
        vec.clear();
        out.close();
        cout<<"Raportul a fost creat cu succes!";
    }
}