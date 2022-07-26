class list
{
private:

    struct element {
        int value = 0;
        element* next = nullptr;
    };

    int length = 0;
    element* root = nullptr;
    element* last = nullptr;

public:

    list(int length)
    {
        if (length == 0)
            return;
        root = new element;
        element* end = root;
        this->length++;
        while (this->length < length) {
            end->next = new element;
            end = end->next;
            end->value = 0;
            this->length++;
        }
        last = end;
    }

    list() { list(0); }
    ~list() { clear(); }

    void clear()
    {
        while (length > 0)
            pop_back();
        root = nullptr;
        last = nullptr;
    }

    void erase(int index)
    {
        if (index >= length)
            index %= length;
        if (index < 0)
            index = (length - (-index % length)) % length;
        int current_index = 0;
        element* current = root;
        while (current_index < index - 1) {
            current = current->next;
            current_index++;
        }
        if (index == 0) {
            element* element_to_delete = root;
            root = element_to_delete->next;
            delete element_to_delete;
            length--;
            return;
        }
        element* element_to_delete = current->next;
        current->next = element_to_delete->next;
        if (index == length - 1)
            last = current;
        delete element_to_delete;
        length--;
    }

    void pop_front()
    {
        if (length == 0)
            return;
        if (length == 1) {
            delete root;
            root = nullptr;
            length = 0;
            return;
        }
        element* element_to_delete = root;
        root = root->next;
        delete element_to_delete;
        length--;
    }

    void pop_back()
    {
        if (length == 0)
            return;
        if (length == 1) {
            delete root;
            root = nullptr;
            last = nullptr;
            length = 0;
            return;
        }
        erase(-1);
    }

    void push_front(int value)
    {
        element* new_element = new element;
        new_element->next = root;
        root = new_element;
        new_element->value = value;
        length++;
    }

    void push_back(int value)
    {
        if (length == 0) {
            root = new element;
            last = root;
            root->value = value;
            length++;
            return;
        }
        last->next = new element;
        last = last->next;
        last->value = value;
        length++;
    }

    void insert(int value, int index)
    {
        if (index > length || index < 0)
            return;
        if (index == 0) {
            push_front(value);
            return;
        }
        int current_index = 0;
        element* current = root;
        while (current_index < index - 1) {
            current = current->next;
            current_index++;
        }
        element* new_element = new element;
        new_element->next = current->next;
        current->next = new_element;
        new_element->value = value;
        length++;
    }

    void print()
    {
        if (length == 0)
            return;
        cout << root->value;
        element* current = root->next;
        int step = 1;
        while (step < length) {
            cout << ' ' << current->value;
            current = current->next;
            step++;
        }
    }

    void println() { print(); cout << '\n'; }

    int size() { return length; }

    int back() { if (last) return last->value; else return 0; }

    int front() { if (root) return root->value; else return 0; }

    bool empty() { return length == 0; }

    int &operator [](int index)
    {
        if (index >= length)
            index %= length;
        if (index < 0)
            index = (length - (-index % length)) % length;
        element* current = root;
        int step = 0;
        while (step < index) {
            current = current->next;
            step++;
        }
        return current->value;
    }
};