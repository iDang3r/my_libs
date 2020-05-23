//
// Created by Александр on 08.11.2019.
//

#ifndef TREE_H
#define TREE_H

template <typename T>
struct node {

    int type_ = 1;
    T data_;
    node* left_  = nullptr;
    node* right_ = nullptr;

    // Constructors

    explicit node(T el, node* left_  = nullptr, node* right_ = nullptr) :
        data_(el),
        left_(left_),
        right_(right_)
    {}

    explicit node(int type, T el, node* left_  = nullptr, node* right_ = nullptr) :
        type_(type),
        data_(el),
        left_(left_),
        right_(right_)
    {}
};

template <typename T>
struct Tree {
    int MAX_TREE_SIZE = 1024;

    int size_ = 0;

    node<T>* head_ = nullptr;

    // Methods

    ~Tree() {
//        cout << "Tree was destructed" << endl;
        if (head_ != nullptr)
            free_tree(head_);
        head_ = nullptr;
    }

    void free_tree(node<T>* el) {
        assert(el != nullptr);
        if (el->left_ != nullptr)
            free_tree(el->left_);
        if (el->right_ != nullptr)
            free_tree(el->right_);
        delete el;
//        free(el);
        size_--;
    }

    int push_left(node<T>* el, T value) {
        assert(el);

        size_++;
        el->left_ = make_node(value);
        return 0;
    }

    int push_right(node<T>* el, T value) {
        assert(el);

        size_++;
        el->right_ = make_node(value);
        return 0;
    }

    int push_head(T value) {
        if (head_ != nullptr) {
            dump(DUMP_INFO, "Tree was not free to use 'push_head' function");
            return 1;
        }

        size_ = 1;
        head_ = make_node(value);
        return 0;
    }

    node<T>* make_node(T value) {
//        node<T>* new_node = (node<T>*)calloc(1, sizeof(node<T>));
        node<T>* new_node = new node<T>(value);

        if (new_node == nullptr) {
            dump(DUMP_INFO, "Memory was not allocated");
            assert(ERROR);
            return nullptr;
        }

        new_node->data_ = value;

        return new_node;
    }

};

#endif //TREE_H