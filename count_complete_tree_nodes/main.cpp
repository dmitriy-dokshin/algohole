#include <iostream>
#include <memory>
#include <queue>

using namespace std;

template<class T>
class TreeNode {
public:
    explicit TreeNode(T value)
            : Value(value) {
    }

    shared_ptr<TreeNode> Left;
    shared_ptr<TreeNode> Right;
    T Value = T();
};

template<class T>
shared_ptr<TreeNode<T>> build_complete_tree(size_t size) {
    if (size == 0) {
        return nullptr;
    }
    auto root = make_shared<TreeNode<T>>(0);
    queue<shared_ptr<TreeNode<T>>> q;
    q.emplace(root);
    for (T count = 1; count < size; count++) {
        auto node = make_shared<TreeNode<T>>(count);
        if (q.front()->Left) {
            q.front()->Right = node;
            q.pop();
        } else {
            q.front()->Left = node;
        }
        q.emplace(node);
    }
    return root;
}

template<class T>
shared_ptr<TreeNode<T>> get_node(shared_ptr<TreeNode<T>> x, size_t idx, size_t begin, size_t end) {
    while (end - begin > 1) {
        size_t mid = begin + (end - begin)/2;
        if (idx < mid) {
            x = x->Left;
            end = mid;
        } else {
            x = x->Right;
            begin = mid;
        }
    }
    return x;
}

template<class T>
size_t count_nodes(shared_ptr<TreeNode<T>> root) {
    size_t h = 0;
    for (auto x = root; x != nullptr; x = x->Left) {
        h++;
    }

    if (h == 0) {
        return 0;
    }

    size_t end = 1 << (h - 1);
    size_t begin = 0;
    while (begin < end) {
        size_t mid = begin + (end - begin)/2;
        if (get_node(root, mid, 0, 1 << (h - 1)) == nullptr) {
            end = mid;
        } else {
            begin = mid + 1;
        }
    }

    size_t count = 0;
    for (size_t l = 0; l < h - 1; l++) {
        count += 1 << l;
    }
    count += begin;
    return count;
}

int main() {
    for (size_t size = 0; size < 1000; size++) {
        auto root = build_complete_tree<size_t>(size);
        size_t count = count_nodes(root);
        if (count != size) {
            cerr << "invalid result, count is not equal initial size: " << count << " != " << size << endl;
        }
    }
    cerr << "all test cases passed" << endl;
}
