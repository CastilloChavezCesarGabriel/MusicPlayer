#ifndef I_SORTING_H
#define I_SORTING_H
#include <vector>

template <typename T, typename U, typename V>
class ISorting {
public:
    virtual ~ISorting() = default;
    virtual void shellSort(std::vector<T>& t) = 0;
    virtual void quickSort(std::vector<T>& t, U u, V v) = 0;
    virtual U partition(std::vector<T>& t, U u, V v) = 0;
};

#endif //I_SORTING_H
