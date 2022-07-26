#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

class binary_tree
{
    struct vertex
    {
        int value;
        vertex* left;
        vertex* right;
        vertex(int value) {
            this->value = value;
            left = right = nullptr;
        }
    };

    vertex* root;
    int count_of_numbers;
    vector<vertex*> useful_vertexes;

    vector<int> cut(vector<int>::iterator begin, vector<int>::iterator end)
    {
        vector<int> result;
        for (auto i = begin; i != end; i++)
            result.push_back(*i);
        return result;
    }

public:

    binary_tree() {
        root = nullptr;
        count_of_numbers = 0;
        useful_vertexes.push_back(root);
    }

    binary_tree(vector<int> numbers) {
        root = nullptr;
        count_of_numbers = 0;
        useful_vertexes.push_back(root);
        fast_initialize(numbers);
    }

    void smart_initialize(vector<int> numbers)
    {
        clear();
        sort(numbers.begin(), numbers.end());
        stack< vector<int> > buf;
        buf.push(numbers);
        while (!buf.empty())
        {
            vector<int> v = buf.top();
            if (v.size() == 0)
                buf.pop();
            else {
                int i = v.size() / 2;
                insert(v[i]);
                buf.pop();
                buf.push(cut(v.begin(), v.begin() + i));
                buf.push(cut(v.begin() + i + 1, v.end()));
            }
        }
    }

    void fast_initialize(vector<int> numbers)
    {
        srand(time(0));
        clear();
        vector< pair<int, int> > buf;
        for (auto number: numbers)
            buf.push_back( make_pair(rand(), number) );
        sort(buf.begin(), buf.end());
        for (auto element: buf)
            insert(element.second);
    }

    void insert(int value)
    {
        if (!root) {
            root = new vertex(value);
            count_of_numbers++;
            return;
        }
        int depth = 0;
        vertex* location = root;
        while (location->value != value) {
            depth++;
            if (value > location->value) {
                if (!location->right) {
                    location->right = new vertex(value);
                    count_of_numbers++;
                    return;
                }
                location = location->right;
            } else if (value < location->value) {
                if (!location->left) {
                    location->left = new vertex(value);
                    count_of_numbers++;
                    return;
                }
                location = location->left;
            }
        }
    }

    void clear()
    {
        if (!root)
            return;
        stack<vertex*> buf;
        buf.push(root);
        vertex* location;
        while (!buf.empty()) {
            location = buf.top();
            if (location->left)
                buf.push(location->left);
            else if (location->right)
                buf.push(location->right);
            else {
                delete buf.top();
                buf.pop();
            }
        }
        root = nullptr;
    }

    void erase(int value)
    {
        if (!root)
            return;
        vertex* location = root;
        vertex* prev;
        while (location && location->value != value) {
            prev = location;
            if (value > location->value)
                location = location->right;
            else
                location = location->left;
        }
        if (location->value != value)
            return;
        stack<vertex*> buf;
        buf.push(location);
        while (!buf.empty())
        {
            if (!location || location->value != value)
                buf.pop();
            else if (!location->left && !location->right) {
                delete location;
                buf.pop();
            } else if (!location->left) {
                if (location == prev->right)
                    prev->right = location->right;
                else
                    prev->left = location->right;
                delete location;
                buf.pop();
            } else if (!location->right) {
                if (prev->right == location)
                    prev->right = location->left;
                else
                    prev->left = location->left;
                delete location;
                buf.pop();
            } else {
                location->value = location->left->value;
                buf.push(location->left);
                prev = location;
                location = location->left;
                value = location->value;
            }
        }
        count_of_numbers--;
    }

    int size() { return count_of_numbers; }

    bool find(int value)
    {
        vertex* location = root;
        while (location && location->value != value) {
            if (location->value > value)
                location = location->left;
            else if (location->value < value)
                location = location->right;
        }
        return location && location->value == value;
    }
};