#include <iostream>
#include <utility>
#include <vector>
#include <stdexcept>

using namespace std;

template<class T>
class Tower {
public:
    string Name;
    vector<T> Data;
};

template<class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << ", " << v[i];
        }
    }
    return out;
}

template<class T>
ostream& operator<<(ostream& out, const Tower<T>& t) {
    out << t.Name << ": " << t.Data << endl;
    return out;
}

template<class T>
void tower_of_hanoi(Tower<T>& src, size_t n, Tower<T>& tmp, Tower<T>& dst) {
    if (n > 0) {
        tower_of_hanoi(src, n - 1, dst, tmp);
        move_data(src, dst);
        tower_of_hanoi(tmp, n - 1, src, dst);
    }
}

template<class T>
void move_data(Tower<T>& src, Tower<T>& dst) {
    if (!dst.Data.empty() && dst.Data.back() < src.Data.back()) {
        throw runtime_error("invalid move");
    }
    dst.Data.emplace_back(std::move(src.Data.back()));
    src.Data.pop_back();
}

int main() {
    Tower<int> src{.Name = "A", .Data= vector<int>{5, 4, 3, 2, 1}};
    Tower<int> tmp{.Name = "B"};
    Tower<int> dst{.Name = "C"};

    cerr << "before:" << endl;
    cerr << src << endl;
    cerr << tmp << endl;
    cerr << dst << endl;

    tower_of_hanoi(src, src.Data.size(), tmp, dst);

    cerr << "after:" << endl;
    cerr << src << endl;
    cerr << tmp << endl;
    cerr << dst << endl;
}
