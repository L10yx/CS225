/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node *r = t->right;
    t->right = r->right;
    r->right = r->left;
    r->left = t->left;
    t->left = r;
    swap(t, r);
    updateHeight(root);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
    updateHeight(root);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node *r = t->left;
    t->left = r->left;
    r->left = r->right;
    r->right = t->right;
    t->right = r;
    swap(t, r);
    updateHeight(root);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
    updateHeight(root);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == nullptr) return;
    if (heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) > -2
        && heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) < 2) return;
    else if (heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) == 2) {
        if (heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right) == 1)
            rotateRight(subtree);
        else rotateLeftRight(subtree);
    }
    else if (heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) == -2) {
        if (heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right) == 1)
            rotateRightLeft(subtree);
        else rotateLeft(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == nullptr) subtree = new Node(key, value);
    else if (key < subtree->key) {
        insert(subtree->left, key, value);
    }
    else if (key > subtree->key) {
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
    subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node *p = subtree;
            Node *t = p->left;
            while (t->right != nullptr) {
                p = t;
                t = t->right;
            }
            subtree->key = t->key;
            subtree->value = t->value;
            if (p != subtree) p->right = t->left;
            else p->left = t->left;
            delete t;
            t = nullptr;
            rebalance(p);
        } else {
            /* one-child remove */
            // your code here
            Node *t = subtree->right;
            if (subtree->left != NULL) t = subtree->left;
            subtree->right = t->right;
            subtree->left = t->left;
            subtree->key = t->key;
            subtree->value = t->value;
            delete t;
            t = nullptr;
        }
        // your code here
    }
    rebalance(subtree);
}

template <class K, class V>
int AVLTree<K, V>::max(int a, int b) {
    if (a >= b) return a;
    else return b;
}
template <class K, class V>
int AVLTree<K, V>::updateHeight(Node * subRoot) {
    if (subRoot == nullptr) return -1;
    subRoot->height = 1 + max(updateHeight(subRoot->left), updateHeight(subRoot->right));
    return subRoot->height;
}
