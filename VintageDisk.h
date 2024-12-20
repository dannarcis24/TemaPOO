#include "Disk.h"

class VintageDisk: public Disk {
    int rarity;
    bool mint;

    void write(ostream&) const;
    void read(istream&);

public:
    VintageDisk() = default;
    VintageDisk(const string, int, double, const string, const string, const string, const Date, bool, int, bool);
    VintageDisk(const string, int, double, const string, const string, const string, const string, bool, int, bool);
    VintageDisk(const string, int, double, const string, const string, const string, int, int, int, bool, int, bool);
    VintageDisk(const Disk, int, bool);

    friend ostream& operator<<(ostream&, const VintageDisk&);
    friend istream& operator>>(istream&, VintageDisk&);

    const double getPrice(bool = true) const;
};