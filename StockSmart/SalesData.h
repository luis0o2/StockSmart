#ifndef SALESDATA_H
#define SALESDATA_H
#include <string>

struct SalesData {
    SalesData() = default;

    SalesData(const std::string& ym, int s, double r)
        : yearMonth(ym), sold(s), revenue(r) {}

    std::string yearMonth;
    int sold = 0;
    int returned = 0;
    double revenue = 0.0;
};

#endif // SALESDATA_H
