#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class optimized_array
{
private:
    vector<int> first, second;

public:
    optimized_array(vector<T>);
    unsigned size();
    unsigned find(T);
    void sort();
    void reverse();
    void print(string sep=" ", string end="\n");
    T min_element();
    T max_element();
    T & operator [] (unsigned i)
    {
        if (i >= first.size())
            return second[i - first.size()];
        return first[first.size() - i - 1];
    }
    T & at(unsigned i)
    {
        if (i < 0 || i >= size())
            exit(1);
        if (i >= first.size())
            return second[i - first.size()];
        return first[first.size() - i - 1];
    }
    bool empty();
    bool sorted();
};

template <typename T>
optimized_array<T>::optimized_array(vector<T> v)
{
    unsigned n = v.size() / 2;
    for (int i = n - 1; i >= 0; i--)
        first.push_back(v[i]);
    for (unsigned i = n; i < v.size(); i++)
        second.push_back(v[i]);
}

template <typename T>
bool optimized_array<T>::empty()
{
    return this->size() == 0;
}

template <typename T>
bool optimized_array<T>::sorted()
{
    for (int i = 1; i < size(); i++)
        if (at(i) < at(i - 1))
            return false;
    return true;
}

template <typename T>
unsigned optimized_array<T>::size()
{
    return first.size() + second.size();
}

template <typename T>
void optimized_array<T>::print(string sep, string end)
{
    for (unsigned i = 0; i < size() - 1; i++)
        cout << at(i) << sep;
    cout << at(size() - 1) << end;
}

template <typename T>
void optimized_array<T>::reverse()
{
    int i = 0, j = size() - 1;
    while (i < j)
    {
        swap(at(i), at(j));
        i++;
        j--;
    }
}

template <typename T>
void optimized_array<T>::sort()
{
    vector<T> v;
    for (int i = first.size() - 1; i >= 0; i--)
        v.push_back( first[i] );
    for (unsigned i = 0; i < second.size(); i++)
        v.push_back( second[i] );
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
        at(i) = v[i];
    v.clear();
}

template <typename T>
T optimized_array<T>::max_element()
{
    T x = *std::max_element(first.begin(), first.end());
    T y = *std::max_element(second.begin(), second.end());
    return x > y ? x : y;
}

template <typename T>
T optimized_array<T>::min_element()
{
    T x = *std::min_element(first.begin(), first.end());
    T y = *std::min_element(second.begin(), second.end());
    return x < y ? x : y;
}

template <typename T>
unsigned optimized_array<T>::find(T element)
{
    for (unsigned i = 0; i < size(); i++)
        if (at(i) == element)
            return i;
    return size();
}

/*
template <typename T>
T & operator [] (unsigned i)
{
    if (i >= first.size())
        return second[i - first.size()];
    return first[first.size() - i - 1];
}
*/
