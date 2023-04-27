#include <iostream>

class RBTree {
public:
    RBTree() : nil_(new Node(0, Node::Color::BLACK)), root_(nil_) {};

    void Insert(const int key) {
        Insert(key, root_);
    }

    bool Find(const int key) const {
        return Find(key, root_);
    }

    void Print() const {
        std::cout << size_ << '\n';
        Print(root_);
    }

private:
    class Node {
    public:
        int key_;
        Node* l_ = nullptr;
        Node* r_ = nullptr;
        Node* p_ = nullptr;

        enum class Color {
            RED,
            BLACK
        } col_;

        Node(int key, Color col, Node* l = nullptr, Node* r = nullptr) : key_(key), l_(l), r_(r), col_(col) {};

        bool IsRed() const {
            return col_ == Color::RED;
        }

        bool IsBlack() const {
            return col_ == Color::BLACK;
        }

        void SetRed() {
            col_ = Color::RED;
        }

        void SetBlack() {
            col_ = Color::BLACK;
        }
    };

    size_t size_ = 0;
    Node* nil_;
    Node* root_;

    void Insert(const int key, Node* v)  {
        Node* cur = new Node(key, Node::Color::RED, nil_, nil_);
        if (v == nil_) {
            cur->SetBlack();
            root_ = cur;
            cur->p_ = nil_;
        } else {
            Node* parent = nil_;
            while (v != nil_) {
                parent = v;
                if (v->key_ == cur->key_) {
                    return;
                }
                v = (cur->key_ < v->key_ ? v->l_ : v->r_);
            }
            cur->p_ = parent;
            (cur->key_ < parent->key_ ? parent->l_ : parent->r_) = cur;
            Fix(cur);
        }
        ++size_;
    }

    void Fix(Node* v) {
        while (v->p_->IsRed()) {
            Node *parent = v->p_;
            Node *grand = parent->p_;
            Node *uncle = (grand->l_ == parent ? grand->r_ : grand->l_);

            if (uncle->IsRed()) {
                parent->SetBlack();
                uncle->SetBlack();
                grand->SetRed();
                v = grand;
            } else {
                if (parent == grand->l_) {
                    if (v == parent->r_) {
                        LeftRotate(v);
                        std::swap(v, parent);
                    }
                    parent->SetBlack();
                    grand->SetRed();
                    RightRotate(parent);
                } else {
                    if (v == parent->l_) {
                        RightRotate(v);
                        std::swap(v, parent);
                    }
                    parent->SetBlack();
                    grand->SetRed();
                    LeftRotate(parent);
                }
            }
            while (root_->p_ != nil_) {
                root_ = root_->p_;
            }
            root_->SetBlack();
        }
    }

    void LeftRotate(Node* v) const {
        Node* parent = v->p_;
        Node* grand = parent->p_;

        v->p_ = grand;
        (grand->l_ == parent ? grand->l_ : grand->r_) = v;

        parent->r_ = v->l_;
        v->l_->p_ = parent;

        parent->p_ = v;
        v->l_ = parent;
    }

    void RightRotate(Node* v) const {
        Node* parent = v->p_;
        Node* grand = parent->p_;

        v->p_ = grand;
        (grand->l_ == parent ? grand->l_ : grand->r_) = v;

        parent->l_ = v->r_;
        v->r_->p_ = parent;

        parent->p_ = v;
        v->r_ = parent;
    }

    bool Find(const int key, const Node* v) const {
        while (v != nil_) {
            if (key == v->key_) {
                return true;
            }
            v = (key < v->key_ ? v->l_ : v->r_);
        }
        return false;
    }

    std::string GetKey(const Node* v) const {
        return (v == nil_ ? "null" : std::to_string(v->key_));
    }

    char GetColor(const Node* v) const {
        return (v->col_ == Node::Color::RED ? 'R' : 'B');
    }

    void Print(const Node* v) const {
        if (v == nil_) {
            return;
        }

        std::cout << GetKey(v) << ' ' << GetKey(v->l_) << ' ' << GetKey(v->r_) << ' ' << GetColor(v) << '\n';

        Print(v->l_);
        Print(v->r_);
    }
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    RBTree tree;
    int q;
    std::cin >> q;

    while (q--) {
        int type, key;
        std::cin >> type >> key;
        if (!type) {
            tree.Insert(key);
        } else {
            std::cout << (tree.Find(key) ? "Yes" : "No") << '\n';
        }
    }

    tree.Print();
}
