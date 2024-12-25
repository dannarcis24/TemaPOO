#include <iostream>
#include <string>
#include <exception>

using namespace std;

class DynamicException: public exception {
private:
    string message;

public:
    DynamicException() = delete;
    DynamicException(const string& name, const string& s): message(name + ": " + s) {
        if(name.empty() || s.empty())
            throw invalid_argument("!! numele si mesajul unei exceptii nu pot fi goale !!\n\n");
    }

    const char* what() const noexcept override {
        return message.c_str(); // se creaza o exceptie personalizata, in functie de tip si eroare
    }
};