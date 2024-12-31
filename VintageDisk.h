#include "Disk.h"

class VintageDisk: public Disk {
    int rarity;
    bool mint;

    void write(ostream&) const;
    void write(ofstream&) const;
    void read(istream&);
    bool isEqual(const Product&) const;

public:
    VintageDisk() = default;
    VintageDisk(const string&, int, double, const string&, const string&, const string&, const Date&, bool, int, bool);
    VintageDisk(const string&, int, double, const string&, const string&, const string&, const string&, bool, int, bool);
    VintageDisk(const string&, int, double, const string&, const string&, const string&, int, int, int, bool, int, bool);
    VintageDisk(const Disk, int, bool);

    friend ostream& operator<<(ostream&, const VintageDisk&);
    friend ostream& operator<<(ostream&, const unique_ptr<VintageDisk>&);
    friend istream& operator>>(istream&, VintageDisk&);
    friend istream& operator>>(istream&, unique_ptr<VintageDisk>&);
    friend bool operator==(const VintageDisk&, const VintageDisk&);
    friend bool operator!=(const VintageDisk&, const VintageDisk&);

    const double getPrice(bool = true) const;
};