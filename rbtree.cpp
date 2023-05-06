#include <bits/stdc++.h>
constexpr bool BLACK = false;
constexpr bool RED = true;
using namespace std;

// TODO: use template type instead of int
struct RBTree {
    struct Node {
        Node *left, *right;
        Node *parent;
        int value;
        bool color;  // TODO: in case of unsigned integer values and signed type for values, use sign bit for color
                     // (wins 1 bit!!!)

        auto operator==(const Node &other) {
            return value == other.value;
        }

        bool isLeftKiddo() const {
            return this == parent->left;
        }

        void CheckCorrent() const {
            if (color == RED) {
                if (left) {
                    assert(left->color == BLACK);
                }
                if (right) {
                    assert(right->color == BLACK);
                }
            }
        }
    };

    Node *root;

    RBTree() {
        root = nullptr;
        // root = new Node{.left = nullptr, .right = nullptr, .parent = nullptr, .value = 0, .color = BLACK};
    }

    void Insert(int value) {
        Insert_(root, value, nullptr);
    }

    bool GetColor(Node *node) {
        if (node == nullptr)
            return BLACK;
        return node->color;
    }

    void Insert_(Node *&node, int value, Node *from) {
        if (node) {
            if (value == node->value)
                return;
            if (value < node->value) {
                Insert_(node->left, value, node);
            } else {
                Insert_(node->right, value, node);
            }
        } else {
            node = new Node{.left = nullptr, .right = nullptr, .parent = from, .value = value, .color = RED};
            FixInsert_(node);
        }
    }

    void FixInsert_(Node *node) {
        while (node->parent and node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {  // BUG: node->parent->parent may cause segfault
                Node *uncle = node->parent->parent->right;     // NOTE: uncle is called 'y' in Korman book
                if (GetColor(uncle) == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;  // BUG: same here
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        LeftRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    RightRotate(node->parent->parent);
                }

            } else {
                // TODO: same as then clause with “right” and “left” exchanged
                Node *uncle = node->parent->parent->left;  // NOTE: uncle is called 'y' in Korman book
                if (GetColor(uncle) == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;  // BUG: same here
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        RightRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    LeftRotate(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void LeftRotate(Node *node) {  // NOTE: node is called 'x' in Korman
        Node *y = node->right;
        node->right = y->left;
        if (y->left) {
            y->left->parent = node;
        }
        y->parent = node->parent;
        if (!node->parent) {
            root = y;
        } else if (node == node->parent->left) {
            node->parent->left = y;
        } else
            node->parent->right = y;
        y->left = node;
        node->parent = y;
    }

    void RightRotate(Node *node) {  // NOTE: node is called 'y' in Korman
        Node *x = node->left;
        node->left = x->right;
        if (x->right) {
            x->right->parent = node;
        }
        x->parent = node->parent;
        if (!node->parent) {
            root = x;
        } else if (node == node->parent->left) {
            node->parent->left = x;
        } else
            node->parent->right = x;
        x->right = node;
        node->parent = x;
    }

    template <typename Callable>
    void Traverse(const Callable &functor) const {
        TraverseSubtree(root, functor);
    }

    void TraverseSubtree(Node *node, const auto &functor) const {
        if (!node)
            return;
#ifndef DEBUG
        node->CheckCorrent();
#endif  // !DEBUG
        TraverseSubtree(node->left, functor);
        functor(node);
        TraverseSubtree(node->right, functor);
    }

    bool Lookup(const int &value) const {
        return Lookup_(root, value);
    }

    bool Lookup_(Node *node, int value) const {
        if (!node)
            return false;
        if (value == node->value)
            return true;
        if (value < node->value)
            return Lookup_(node->left, value);
        return Lookup_(node->right, value);
    }
};

constexpr auto Printer = [](const auto &t) -> void { cout << t->value << ' '; };

int main() {
    cin.tie(0)->sync_with_stdio(false);
#ifdef DEBUG
    cout << "DEBUG\n---------------------\n";
#endif  // !DEBUG
    RBTree rbtree;
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        rbtree.Insert(x);
        rbtree.Traverse(Printer);
        cout << endl;
        cout.flush();
    }
    return 0;
}
