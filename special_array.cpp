template <typename T>
class special_array
{
private:
    vector<int> first, second;

public:
    special_array(vector<T>);
    special_array(unsigned n);
    unsigned size();
    unsigned find(T);
    void sort(bool (*comp)(T, T));
    void sort();
    void reverse();
    void print(string sep=" ", string end="\n");
    void insert(T, unsigned);
    void push_back(T);
    void push_front(T);
    void erase(unsigned);
    void pop_back();
    void pop_front();
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
    bool non_decreasing();
    bool non_increasing();
    bool decreasing();
    bool increasing();
    inline long long sum();
    long long sum(unsigned l, unsigned r);
};

template <typename T>
special_array<T>::special_array(vector<T> v)
{
    unsigned n = v.size() / 2;
    for (int i = n - 1; i >= 0; i--)
        first.push_back(v[i]);
    for (unsigned i = n; i < v.size(); i++)
        second.push_back(v[i]);
}

template <typename T>
special_array<T>::special_array(unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        if (i & 1)
            first.push_back(0);
        else
            second.push_back(0);
    }
}

template <typename T>
bool special_array<T>::empty()
{
    return this->size() == 0;
}

template <typename T>
bool special_array<T>::non_increasing()
{
    for (int i = 1; i < size(); i++)
        if (at(i) > at(i - 1))
            return false;
    return true;
}

template <typename T>
bool special_array<T>::non_decreasing()
{
    for (int i = 1; i < size(); i++)
        if (at(i) < at(i - 1))
            return false;
    return true;
}

template <typename T>
bool special_array<T>::decreasing()
{
    for (int i = 1; i < size(); i++)
        if (at(i) >= at(i - 1))
            return false;
    return true;
}

template <typename T>
bool special_array<T>::increasing()
{
    for (int i = 1; i < size(); i++)
        if (at(i) <= at(i - 1))
            return false;
    return true;
}

template <typename T>
unsigned special_array<T>::size()
{
    return first.size() + second.size();
}

template <typename T>
void special_array<T>::print(string sep, string end)
{
    if (size() == 0)
    {
        cout << end;
        return;
    }
    for (unsigned i = 0; i < size() - 1; i++)
        cout << at(i) << sep;
    cout << at(size() - 1) << end;
}

template <typename T>
void special_array<T>::reverse()
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
void special_array<T>::sort(bool (*comp)(T, T))
{
    vector<T> v;
    for (int i = first.size() - 1; i >= 0; i--)
        v.push_back( first[i] );
    for (unsigned i = 0; i < second.size(); i++)
        v.push_back( second[i] );
    std::sort(v.begin(), v.end(), comp);
    for (int i = 0; i < v.size(); i++)
        at(i) = v[i];
    v.clear();
}
template <typename T>
void special_array<T>::sort()
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
T special_array<T>::max_element()
{
    T x = *std::max_element(first.begin(), first.end());
    T y = *std::max_element(second.begin(), second.end());
    return x > y ? x : y;
}

template <typename T>
T special_array<T>::min_element()
{
    T x = *std::min_element(first.begin(), first.end());
    T y = *std::min_element(second.begin(), second.end());
    return x < y ? x : y;
}

template <typename T>
unsigned special_array<T>::find(T element)
{
    for (unsigned i = 0; i < size(); i++)
        if (at(i) == element)
            return i;
    return size();
}

template <typename T>
void special_array<T>::push_back(T value)
{
    second.push_back(value);
}

template <typename T>
void special_array<T>::push_front(T value)
{
    first.push_back(value);
}

template <typename T>
void special_array<T>::insert(T value, unsigned index)
{
    special_array<T>::push_back(value);
    for (unsigned i = size() - 1; i > index; i--)
        swap(at(i), at(i - 1));
}

template <typename T>
void special_array<T>::erase(unsigned index)
{
    if (size() == 0)
        return;
    for (unsigned i = index; i < size() - 1; i++)
        swap(at(i), at(i + 1));
    pop_back();
}

template <typename T>
void special_array<T>::pop_back()
{
    if (size() == 0)
        return;
    if (second.size() > 0) {
        second.pop_back();
        return;
    }
    int n = (size() + 1) / 2;
    for (int i = n - 1; i >= 0; i--)
        second.push_back(first[i]);
    for (unsigned i = 0; i + n < first.size(); i++)
        first[i] = first[i + n];
    first.resize(first.size() - n);
    second.pop_back();
}

template <typename T>
void special_array<T>::pop_front()
{
    if (size() == 0)
        return;
    if (first.size() > 0) {
        first.pop_back();
        return;
    }
    int n = (size() + 1) / 2;
    for (int i = n - 1; i >= 0; i--)
        first.push_back(second[i]);
    for (unsigned i = 0; i + n < second.size(); i++)
        second[i] = second[i + n];
    second.resize(second.size() - n);
    first.pop_back();
}

template <typename T>
long long special_array<T>::sum(unsigned l, unsigned r)
{
    long long result = 0;
    for (int i = l; i < r; i++)
        result += at(i);
    return result;
}

template <typename T>
inline long long special_array<T>::sum()
{
    return sum(0, size());
}
