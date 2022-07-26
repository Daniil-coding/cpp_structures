#include <vector>

template<typename T>
class sparce_table
{
    vector< vector<T> > table;
    vector<unsigned> log;

public:
    sparce_table(vector<T> data)
    {
        unsigned N = data.size();
        if (N == 0)
            return;

        log.resize(N + 1);
        log[1] = 0;
        for (unsigned i = 2; i <= N; i++)
            log[i] = log[i / 2] + 1;

        table.push_back(data);
        for (unsigned len = 2; len <= N; len *= 2)
        {
            table.push_back({});
            table.back().resize(N - len + 1);
            for (unsigned i = 0; i <= N - len; i++)
            {
                T first = table[log[len] - 1][i];
                T second = table[ log[len - 1] ][i + len / 2];
                table[ log[len] ][i] = min(first, second);
            }
        }
    }

    T minimum(unsigned l, unsigned r)
    {
        unsigned i = log[r - l + 1];
        return min(table[i][l], table[i][ r - (1 << (i - 0)) + 1 ]);
    }
};
