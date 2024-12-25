#include "Clothes.h"

class Disk: public Product {
protected:
    string record_company, band, album_name;
    Date sale_date = Date();
    bool type; // 0 - CD uri/ 1 - viniluri

    void write(ostream&) const;
    void read(istream&);
    bool isEqual(const Product&) const;

public:
    Disk() = default;
    Disk(const string&, int, int, const string&, const string&, const string&, const Date&, bool);
    Disk(const string&, int, int, const string&, const string&, const string&, const string&, bool);
    Disk(const string&, int, int, const string&, const string&, const string&, int, int, int, bool);

    friend ostream& operator<<(ostream&, const Disk&);
    friend istream& operator>>(istream&, Disk&);
    friend bool operator==(const Disk&, const Disk&);
    friend bool operator!=(const Disk&, const Disk&);

    const double getPrice(bool = true) const;

private:
    inline void validation() const;
};