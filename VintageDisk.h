#include "Disk.h"

class VintageDisk: public Disk {
    int rarity;
    bool mint;

    void write(ostream&) const;
    void read(istream&);
    bool isEqual(const Product&) const;

public:
    VintageDisk() = default;
    VintageDisk(const string&, int, int, const string&, const string&, const string&, const Date&, bool, int, bool);
    VintageDisk(const string&, int, int, const string&, const string&, const string&, const string&, bool, int, bool);
    VintageDisk(const string&, int, int, const string&, const string&, const string&, int, int, int, bool, int, bool);
    VintageDisk(const Disk, int, bool);

    friend ostream& operator<<(ostream&, const VintageDisk&);
    friend istream& operator>>(istream&, VintageDisk&);
    friend bool operator==(const VintageDisk&, const VintageDisk&);
    friend bool operator!=(const VintageDisk&, const VintageDisk&);

    const double getPrice(bool = true) const;
};