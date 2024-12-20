#include "Employee.h"

unsigned long long Employee::number = 0;

void Employee::validationString(const string sir, bool tip) const
{
    int dim = sir.length();
    if(dim < 3 || dim > 30)
        throw DynamicException(tip ? "name1_invalid", "!! name1le nu poate sa contina mai putin de 3litere sau mai mult 30caractere !!\n\n" 
                           : "name2_invalid", "!! name2le nu poate sa contina mai putin de 3litere sau mai mult 30caractere !!\n\n");
    if(sir[0] < 'A' || sir[0] > 'Z') 
        throw DynamicException(tip ? "name1_invalid", "!! name1le trebuie sa aiba prima litera mare si restul litere mici ale alfabetului englez !!\n\n" 
                           : "name2_invalid", "!! name2le trebuie sa aiba prima litera mare si restul litere mici ale alfabetului englez !!\n\n");

    if(tip == 1) {
        for(register int i = 1; i < dim; i++)
            if(sir[i] < 'a' || sir[i] > 'z')
                throw DynamicException("name1_invalid", "!! name1le trebuie sa aiba prima litera mare si restul litere mici ale alfabetului englez !!\n\n");
    }
    else
    {
        bool litera_mare = true, separator = false;

        for(register int i = 0; i < dim; i++)
            if(litera_mare)
            {
                if(sir[i] == '-' || sir[i] == ' ')
                    throw DynamicException("name2_invalid", "!! name2le trebuie sa fie separate printr-o singura cratima sau un singur spatiu !!\n\n");

                if(sir[i] < 'A' || sir[i] > 'Z')
                    throw DynamicException("name2_invalid", "!! name2le trebuie sa aiba prima litera mare !!\n\n");
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
                        throw DynamicException("name2_invalid", "!! name2le trebuie sa aiba prima litera mare si restul litere mici ale alfabetului englez !!\n\n");
                    else
                        separator = false;

        if(sir.back() == '-' || sir.back() == ' ')
            throw DynamicException("name2_invalid", "!! ultimul caracter al name2lui trebuie sa fie o litera mica a alfabetului englez !!\n\n");
    }
}

const Date Employee::birthday() const
{
    string data = CNP.substr(5, 2) + '.' + CNP.substr(3, 2) + '.';

    if(CNP[0] == '1' || CNP[0] == '2')
        data += "19";
    if(CNP[0] == '3' || CNP[0] == '4')
        data += "18";
    if(CNP[0] >= '5' && CNP[0] <= '8')
        data += "20";
    else
        throw DynamicException("cnp_invalid", "\n!! primul caracter din CNP este incorect, ani recunoscuti: 1800-2099 !!\n\n");
    
    return Date(data + CNP.substr(1, 2));
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
        throw DynamicException("data_invalida", "!! persoana, care trebuie Employeea, trebuie sa aiba minim 18ani impliniti !!\n\n");

    int jud = stoi(CNP.substr(7, 2));
    if(jud < 1 || (jud > 46 && jud < 50) || jud > 52)
        throw DynamicException("cnp_invalid", "!! judetul din CNP nu este valid !!\n\n");
    if(CNP.substr(9, 3) == "000")
        throw DynamicException("cnp_invalid", "!! componenta NNN din CNP nu poate fi 000 !!\n\n");

    int control[12] = {2, 7, 6, 5, 4, 3, 2, 7, 6, 5, 4, 3}, c = 0;
    for(register int i = 0; i < 13; i++)
        c = (CNP[i] - '0') * control[i];
    c = (c % 11 == 10) ? 1 : (c % 11);

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

Employee::Employee(const string name1, const string name2, const string cod, const Date date, bool type): last_name(name1), first_name(name2), CNP(cod), employment_date(date), job(type) {
    validation();
}

Employee::Employee(const string name1, const string name2, const string cod, int day, int month, int year, bool type): last_name(name1), first_name(name2), CNP(cod), employment_date(day, month, year), job(type) {
    validation();
}

Employee::Employee(const string name1, const string name2, const string cod, const string date, bool type): last_name(name1), first_name(name2), CNP(cod), employment_date(date), job(type) {
    validation();
}

const int Employee::salary() const {
    return ((salary_base + old * employment_date.years()) * coefficient + (job && birthday().isBirthday() ? 100 : 0));
}

void Employee::setName(const string sir)
{
    validationString(sir);
    last_name = sir;
}

void Employee::write(ostream& out) const
{
    out<<"////// INFORMATII DESPRE ANGAJATUL: "<<first_name<<' '<<last_name<<" //////\n\n";

    out<<"CNP: "<<CNP<<"\nID: "<<ID<<'\n';
    out<<"Pozitie: "<<(coefficient != 1 ? (job ? "asistent" : "manager") : "operator de comenzi")<<'\n';
    out<<"Data angajarii: "<<employment_date<<"\nSalariul pe luna curenta este: "<<salary()<<'\n';
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