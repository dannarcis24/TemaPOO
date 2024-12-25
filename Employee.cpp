#include "Employee.h"

unsigned long long Employee::number = 0;
double Employee::coefficient = 1;

void Employee::validationString(const string sir, bool tip) const
{
    int dim = sir.length();
    if(dim < 3 || dim > 30)
        (tip ? throw DynamicException("nume_invalid", "!! numele nu poate sa contina mai putin de 3litere sau mai mult 30caractere !!\n\n") 
            : throw DynamicException("prenume_invalid", "!! prenumele nu poate sa contina mai putin de 3litere sau mai mult 30caractere !!\n\n"));
    if(sir[0] < 'A' || sir[0] > 'Z') 
        (tip ? throw DynamicException("nume_invalid", "!! numele trebuie sa aiba prima litera mare si restul litere mici ale alfabetului englez !!\n\n") 
            : throw DynamicException("prenume_invalid", "!! prenumele trebuie sa aiba prima litera mare si restul litere mici ale alfabetului englez !!\n\n"));

    if(tip == 1) {
        for(register int i = 1; i < dim; i++)
            if(sir[i] < 'a' || sir[i] > 'z')
                throw DynamicException("nume_invalid", "!! numele trebuie sa aiba prima litera mare si restul litere mici ale alfabetului englez !!\n\n");
    }
    else
    {
        bool litera_mare = true, separator = false;

        for(register int i = 0; i < dim; i++)
            if(litera_mare)
            {
                if(sir[i] == '-' || sir[i] == ' ')
                    throw DynamicException("prenume_invalid", "!! prenumele trebuie sa fie separate printr-o singura cratima sau un singur spatiu !!\n\n");

                if(sir[i] < 'A' || sir[i] > 'Z')
                    throw DynamicException("prenume_invalid", "!! prenumele trebuie sa aiba prima litera mare !!\n\n");
                else
                    litera_mare = false;
            }
            else
                if(sir[i] == '-' || sir[i] == ' ')
                {
                    separator = true;
                    litera_mare = true;
                }
                else
                    if(sir[i] < 'a' || sir[i] > 'z')
                        throw DynamicException("prenumele_invalid", "!! prenumele trebuie sa aiba prima litera mare si restul litere mici ale alfabetului englez !!\n\n");
                    else
                        separator = false;

        if(sir.back() == '-' || sir.back() == ' ')
            throw DynamicException("prenumele_invalid", "!! ultimul caracter al prenumelui trebuie sa fie o litera mica a alfabetului englez !!\n\n");
    }
}

const Date Employee::birthday() const
{
    string data = CNP.substr(5, 2) + '.' + CNP.substr(3, 2) + '.';

    if(CNP[0] == '1' || CNP[0] == '2')
        return Date(data + "19" + CNP.substr(1, 2));
    if(CNP[0] == '3' || CNP[0] == '4')
        return Date(data + "18" + CNP.substr(1, 2));
    if(CNP[0] == '5' || CNP[0] == '6')
        return Date(data + "20" + CNP.substr(1, 2));
    if(CNP[0] == '7' || CNP[0] == '8')
        throw DynamicException("rezident", "!! nu se poate extrage anul nasterii pentru persoanele rezidente !!\n\n");
    else
        throw DynamicException("cnp_invalid", "!! primul caracter din CNP este incorect, ani recunoscuti: 1800-2099 !!\n\n");
}

void Employee::validationCNP() const
{
    int dim = CNP.length();
    if(dim != 13)
        throw DynamicException("cnp_invalid", "!! un CNP valid este format din 13 cifre !!\n\n");
    for(register int i = 0; i < dim; i++)
        if(CNP[i] < '0' || CNP[i] > '9')
            throw DynamicException("cnp_invalid", "!! un CNP valid este format din cifre 0-9 !!\n\n");
    
    Date data_nasterii = birthday();
    if(!data_nasterii.esteMajor())
        throw DynamicException("data_invalida", "!! persoana, care trebuie angajata, trebuie sa aiba minim 18ani impliniti !!\n\n");

    int jud = stoi(CNP.substr(7, 2));
    if(jud < 1 || (jud > 46 && jud < 50) || jud > 52)
        throw DynamicException("cnp_invalid", "!! judetul din CNP nu este valid !!\n\n");
    if(CNP.substr(9, 3) == "000")
        throw DynamicException("cnp_invalid", "!! componenta NNN din CNP nu poate fi 000 !!\n\n");

    int control[12] = {2, 7, 9, 1, 4, 6, 3, 5, 8, 2, 7, 9}, c = 0;
    for(register int i = 0; i < 12; i++)
        c += (CNP[i] - '0') * control[i];
    c = ((c % 11 == 10) ? 1 : (c % 11));

    if(c != CNP[12] - '0')
        throw DynamicException("cnp_invalid", "!! cifra de control nu este corecta, deci CNP ul este invalid !!\n\n");
}

void Employee::validation()
{
    validationString(last_name);
    validationString(first_name, 0);
    validationCNP();

    ID = "@" + to_string(number++);
    coefficient = (job ? 0.75 : 1.25);
}

Employee::Employee() {
    Employee::number++;
    job = true;
    coefficient = 1;
}

Employee::Employee(const string& name1, const string& name2, const string& cod, const Date& date, bool type): last_name(name1), first_name(name2), CNP(cod), employment_date(date), job(type) {
    validation();
}

Employee::Employee(const string& name1, const string& name2, const string& cod, int day, int month, int year, bool type): last_name(name1), first_name(name2), CNP(cod), employment_date(day, month, year), job(type) {
    validation();
}

Employee::Employee(const string& name1, const string& name2, const string& cod, const string& date, bool type): last_name(name1), first_name(name2), CNP(cod), employment_date(date), job(type) {
    validation();
}

Employee::Employee(const string& position)
{
    if(position == "manager")
        job = false;
    else
        if(position == "asistent")
            job = true;
        else
            throw DynamicException("posizitie_invalida", "!! pozitii valide: manager/asistent !!\n\n");
    
    ID = "@" + to_string(number++);
    coefficient = (job ? 0.75 : 1.25);
}

const int Employee::salary() const {
    return ((salary_base + old * employment_date.years()) * coefficient + (job && birthday().isBirthday() ? 100 : 0));
}

void Employee::setName(const string& sir)
{
    validationString(sir);
    last_name = sir;
}

void Employee::write(ostream& out) const
{
    out<<"////// INFORMATII DESPRE ANGAJATUL: "<<last_name<<' '<<first_name<<" //////\n\n";
    out<<"CNP: "<<CNP<<"\nID: "<<ID<<'\n'<<"Pozitie: "<<position()<<'\n'<<"Data angajarii: "<<employment_date<<"\nSalariul pe luna curenta este: "<<salary()<<'\n';
}

void Employee::write(ofstream& out) const {
    out<<last_name<<','<<first_name<<','<<CNP<<','<<ID<<','<<position()<<','<<employment_date<<','<<salary();
}

ostream& operator<<(ostream& out, const Employee* elem) 
{
    elem->write(out);
    return out;
}

ostream& operator<<(ostream& out, const Employee elem)
{
    elem.write(out);
    return out;
}

void Employee::read(istream& in)
{
    if(&in == &cin)
    {
        cout<<"Introduceti pozitia angajatului (manager/asistent/operator comenzi): ";
        string pozitie;
        getline(in, pozitie);

        if(pozitie == "manager") {   
            job = false;
            coefficient = 1.25;
        }
        else
            if(pozitie == "asistent") {
                job = true;
                coefficient = 0.75;
            }
            else
                if(pozitie == "operator comenzi")
                {
                    job = true;
                    coefficient = 1;
                }
                else
                    throw DynamicException("pozitie_invalida", "!! pozitia angajatului trebuie sa fie una dintre cele trei: manager/asistent/operator comenzi !!\n\n");
    }

    if(&in == &cin)
        cout<<"Introduceti numele: ";
    getline(in, last_name);
    validationString(last_name);

    if(&in == &cin)
        cout<<"Introduceti prenumele: ";
    getline(in, first_name);
    validationString(first_name, 0);

    if(&in == &cin)
        cout<<"Introduceti CNP ul: ";
    getline(in, CNP);
    validationCNP();

    if(&in == &cin)
        cout<<"Introduceti data angajarii ";
    in>>employment_date;
}

istream& operator>>(istream& in, Employee& elem)
{
    Employee aux;
    
    try {
        aux.read(in);
        if(Employee::coefficient == 1)
            throw DynamicException("pozitie_invalida", "!! pentru a retine un operator de comenzi, trebuie sa folositi tipul OrderOperator !!\n\n");
    } catch(const exception& e) { Employee::number--; throw;}
    elem = aux;

    return in;
}

istream& operator>>(istream& in, Employee* elem)
{  
    try {
        elem->read(in);
        if(Employee::coefficient == 1)
            throw DynamicException("pozitie_invalida", "!! pentru a retine un operator de comenzi, trebuie sa folositi tipul OrderOperator !!\n\n");
    } catch(const exception& e) { Employee::number--; throw;}

    return in;
}

const string Employee::position() const {
    return (coefficient == 0.75 ? "asistent" : (coefficient == 1 ? "operator comenzi" : "manager"));
}

bool Employee::exist(const string& id) const {
    return (ID == id);
}

bool compareByName(const Employee* elem1, const Employee* elem2) {
    return ((elem1->last_name + elem1->first_name) > (elem2->last_name + elem2->first_name));
}