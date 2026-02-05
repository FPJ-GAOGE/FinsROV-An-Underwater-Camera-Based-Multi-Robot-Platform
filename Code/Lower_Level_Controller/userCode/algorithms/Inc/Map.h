//
// Created by 25396 on 2023/2/11.
//

#ifndef RM_FRAME_C_MAP_H
#define RM_FRAME_C_MAP_H


template <typename Key, typename Value>
class MyMap {
public:
    struct Node {
        Key first;
        Value second;
        Node *left;
        Node *right;
    };

    MyMap() : root_(nullptr) {}

    void insert(const Key &key, const Value &value) {
        Node *node = new Node;
        node->first = key;
        node->second = value;
        node->left = nullptr;
        node->right = nullptr;

        if (!root_) {
            root_ = node;
            return;
        }

        Node *cur = root_;
        while (cur) {
            if (key < cur->first) {
                if (cur->left) {
                    cur = cur->left;
                } else {
                    cur->left = node;
                    return;
                }
            } else if (key > cur->first) {
                if (cur->right) {
                    cur = cur->right;
                } else {
                    cur->right = node;
                    return;
                }
            } else {
                cur->second = value;
                return;
            }
        }
    }

    Value& operator[](const Key &key) {
        Node *node = root_;
        while (node) {
            if (key < node->first) {
                node = node->left;
            } else if (key > node->first) {
                node = node->right;
            } else {
                return node->second;
            }
        }

        insert(key, Value());
        return operator[](key);
    }

    bool find(const Key &key) {
        Node *node = root_;
        while (node) {
            if (key < node->first) {
                node = node->left;
            } else if (key > node->first) {
                node = node->right;
            } else {
                return true;
            }
        }
        return false;
    }

    Node* root_;
};

#endif //RM_FRAME_C_MAP_H
