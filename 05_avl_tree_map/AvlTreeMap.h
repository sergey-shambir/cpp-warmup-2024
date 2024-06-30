#pragma once

#include <cstdint>
#include <memory>
#include <utility>
#include <cassert>
#include <vector>

template <class Key, class Value>
class AvlTreeMap
{
    class Node;

public:
    explicit AvlTreeMap() {}

    ~AvlTreeMap() noexcept
    {
        delete root;
    }

    AvlTreeMap(Node &&other) noexcept
    {
        std::swap(root, other.root);
    }

    AvlTreeMap &operator=(Node &&other) noexcept
    {
        std::swap(root, other.root);
        return *this;
    }

    AvlTreeMap(const Node &) = delete;
    AvlTreeMap &operator=(const Node &) = delete;

    void Insert(const Key &key, const Value &value)
    {
        root = InsertImpl(root, key, value);
    }

    void Remove(const Key &key) noexcept
    {
        root = RemoveImpl(root, key);
    }

    std::vector<Key> ListKeys() const
    {
        std::vector<Key> keys;
        ListKeysRecursive(root, keys);

        return keys;
    }

    std::vector<Value> ListValues() const
    {
        std::vector<Value> values;
        ListValuesRecursive(root, values);

        return values;
    }

private:
    class Node
    {
    public:
        Key key;
        Value value;
        std::uint8_t height = 0;
        Node *left = nullptr;
        Node *right = nullptr;

        explicit Node(const Key &key, const Value &value)
            : key(key), value(value)
        {
        }

        ~Node()
        {
            delete left;
            delete right;
        }

        Node(Node &&) = delete;
        Node(const Node &) = delete;

        Node &operator=(Node &&) = delete;
        Node &operator=(const Node &) = delete;

        Node *Balance() noexcept
        {
            UpdateHeight();
            const auto factor = GetBalanceFactor();
            if (factor == 2)
            {
                if (left->GetBalanceFactor() > 0)
                {
                    left = left->RotateLeft();
                }
                return RotateRight();
            }
            if (factor == -2)
            {
                if (right->GetBalanceFactor() < 0)
                {
                    right = right->RotateRight();
                }
                return RotateLeft();
            }
            return this;
        }

        Node *FindLeftmostChild() noexcept
        {
            return left ? left->FindLeftmostChild() : this;
        }

        Node *RemoveLeftmostChild() noexcept
        {
            if (!left)
            {
                return right;
            }
            left = left->RemoveLeftmostChild();
            return Balance();
        }

    private:
        Node *RotateRight() noexcept
        {
            assert(left != nullptr);

            Node *newRoot = left;
            left = newRoot->right;
            newRoot->right = this;

            UpdateHeight();
            newRoot->UpdateHeight();

            return newRoot;
        }

        Node *RotateLeft() noexcept
        {
            assert(right != nullptr);

            Node *newRoot = right;
            right = newRoot->left;
            newRoot->left = this;

            UpdateHeight();
            newRoot->UpdateHeight();

            return newRoot;
        }

        std::int8_t GetBalanceFactor() const noexcept
        {
            return std::int8_t(GetHeight(left)) - std::int8_t(GetHeight(right));
        }

        void UpdateHeight() noexcept
        {
            const auto leftHeight = GetHeight(left);
            const auto rightHeight = GetHeight(right);
            height = 1u + (std::max)(leftHeight, rightHeight);
        }

        static std::uint8_t GetHeight(Node *node) noexcept
        {
            return node ? node->height : 0;
        }
    };

    static Node *InsertImpl(Node *node, const Key &key, const Value &value)
    {
        if (!node)
        {
            return new Node(key, value);
        }
        if (key < node->key)
        {
            node->left = InsertImpl(node->left, key, value);
        }
        else if (node->key < key)
        {
            node->right = InsertImpl(node->right, key, value);
        }
        else // (key == node->key)
        {
            node->value = value;
        }
        return node->Balance();
    }

    static Node *RemoveImpl(Node *node, const Key &key) noexcept
    {
        if (!node)
        {
            return nullptr;
        }
        if (key < node->key)
        {
            node->left = RemoveImpl(node->left, key);
        }
        else if (node->key < key)
        {
            node->right = RemoveImpl(node->right, key);
        }
        else // (key == node->key)
        {
            Node *left = node->left;
            Node *right = node->right;
            node->left = nullptr;
            node->right = nullptr;
            delete node;

            if (!right)
            {
                return left;
            }
            Node *newRoot = right->FindLeftmostChild();
            newRoot->right = right->RemoveLeftmostChild();
            newRoot->left = left;

            return newRoot->Balance();
        }
        return node->Balance();
    }

    static void ListKeysRecursive(Node *node, std::vector<Key> &keys)
    {
        if (!node)
        {
            return;
        }
        ListKeysRecursive(node->left, keys);
        keys.push_back(node->key);
        ListKeysRecursive(node->right, keys);
    }

    static void ListValuesRecursive(Node *node, std::vector<Value> &values)
    {
        if (!node)
        {
            return;
        }
        ListValuesRecursive(node->left, values);
        values.push_back(node->value);
        ListValuesRecursive(node->right, values);
    }

    Node *root = nullptr;
};
