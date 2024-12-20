#include <iostream>
#include <string>
#include <exception>

using namespace std;

class DynamicException: public exception {
private:
    string name, message;

public:
    DynamicException() = delete;
    DynamicException(const string nume, const string sir): name(nume), message(sir) {
        if(name.empty() || message.empty())
            throw invalid_argument("!! numele si mesajul unei exceptii nu pot fi goale !!\n\n");
    }

    const char* what() const noexcept override {
        string text = name + ": " + message;  
        return text.c_str(); // se creaza o exceptie personalizata, in functie de tip si eroare
    }
};
