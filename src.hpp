
#ifndef PYLIST_H
#define PYLIST_H

#include <iostream>
#include <vector>
#include <memory>
#include <set>

class pylist {
    struct Data {
        bool is_int;
        int val;
        std::vector<pylist> items;
        Data() : is_int(false), val(0) {}
        Data(int v) : is_int(true), val(v) {}
    };
    std::shared_ptr<Data> data;

public:
    pylist() : data(std::make_shared<Data>()) {}
    pylist(int v) : data(std::make_shared<Data>(v)) {}

    void append(const pylist &x) {
        if (!data->is_int) {
            data->items.push_back(x);
        }
    }

    pylist pop() {
        if (data->is_int || data->items.empty()) {
            return pylist();
        }
        pylist last = data->items.back();
        data->items.pop_back();
        return last;
    }

    pylist &operator[](size_t i) {
        return data->items[i];
    }

    const pylist &operator[](size_t i) const {
        return data->items[i];
    }

    pylist& operator=(int v) {
        data = std::make_shared<Data>(v);
        return *this;
    }

    operator int() const {
        return data->is_int ? data->val : 0;
    }

    void print(std::ostream &os, std::set<const Data*> &visited) const {
        if (data->is_int) {
            os << data->val;
        } else {
            if (visited.count(data.get())) {
                os << "[...]";
            } else {
                visited.insert(data.get());
                os << "[";
                for (size_t i = 0; i < data->items.size(); ++i) {
                    data->items[i].print(os, visited);
                    if (i != data->items.size() - 1) os << ", ";
                }
                os << "]";
                visited.erase(data.get());
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const pylist &ls) {
        std::set<const Data*> visited;
        ls.print(os, visited);
        return os;
    }
};

#endif // PYLIST_H
