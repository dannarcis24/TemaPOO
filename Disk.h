#include "Clothes.h"

class Disk: public Product {
protected:
    string record_company, band, album_name;
    Date sale_date = Date();
    bool type; // 0 - CD uri/ 1 - viniluri

    void write(ostream&) const;
    void read(istream&);

public:
    Disk() = default;
    Disk(const string, int, double, const string, const string, const string, const Date, bool);
    Disk(const string, int, double, const string, const string, const string, const string, bool);
    Disk(const string, int, double, const string, const string, const string, int, int, int, bool);

    friend ostream& operator<<(ostream&, const Disk&);
    friend istream& operator>>(istream&, Disk&);

    const double getPrice(bool = true) const;

private:
    inline void validation() const;
};