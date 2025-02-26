#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>

double cap(const double value, const double min_bound, const double max_bound){
    double capped_min = std::max(value, min_bound);
    double capped_min_max = std::min(capped_min, max_bound);
    return capped_min_max;
}

#endif
