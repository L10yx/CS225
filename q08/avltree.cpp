/**
 * CS 225 e08
 * @file avltree.cpp
 * @author NEW
 * Definitions of the binary tree functions you'll be writing for this exam.
 * You'll need to modify this file.
 */


// TODO
/* attach a given subtree (t) to the existing tree (this)
 * assumption 1: both trees are AVL
 * assumption 2: all nodes in tree (t) have values strictly larger that the nodes in the existing tree (this)
 */
template <class K, class V>
void AVLTree<K, V>::join(const AVLTree<K, V> &t)
{
    // write your AVLTree::join code here
    if (this->root == nullptr) {
        *this = t;
        return;
    }
    AVLTree<K, V> temp = t;
    temp.getInorderTraversal();
    temp.getInorderV();
    for (int i = 0; i < (int)temp.inorder.size(); i++) {
        this->insert(temp.inorder[i], temp.inorderV[i]);
    }
}

template <class K, class V>
vector<V> AVLTree<K,V>::getInorderV()
{
    getInorderV(root);
    return inorderV;
}

template <class K, class V>
void AVLTree<K,V>::getInorderV(const Node* subRoot)
{
    if (subRoot == NULL) {
        return;
    }
    getInorderV(subRoot->left);
    inorderV.push_back(subRoot->value);
    getInorderV(subRoot->right);
}


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
void AVLTree<K, V>::insert(const K & key, const V & value)
{
	if (root == NULL) {
		root = new Node(key, value);
		return;
	}

	vector<Node*> path;
	Node* walk = root;

	while (walk != NULL) {
		path.push_back(walk);
		if (walk->key == key)
			return;
		if (key < walk->key) {
			walk = walk->left;
		}
		else {
			walk = walk->right;
		}
	}

	if (key < path.back()->key) {
		path.back()->left = new Node(key, value);
	}
	else {
		path.back()->right = new Node(key, value);
	}

	while (!path.empty()) {
		rebalance(path.back()->left);
		rebalance(path.back()->right);
		path.pop_back();
	}

	rebalance(root);
}


template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    /*  a                            b
       / \                         /   \
      al  b                       a     c
         / \         -->         / \   / \
        bl  c                   al bl cl cr
           / \
          cl cr
        */
    Node* newroot = t->right;
    t->right = newroot->left;
    newroot->left = t;
    t = newroot;
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    /*          a                          b
               / \                       /   \
              b  ar                     c     a
             / \         -->           / \   / \
            c   br                    cl cr br ar
           / \
          cl cr
    */
    Node* newroot = t->left;
    t->left = newroot->right;
    newroot->right = t;
    t = newroot;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    Node* y = t->left;
    Node* z = y->right;
    y->right = z->left;
    z->left = y;
    t->left = z->right;
    z->right = t;
    t = z; 
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    Node* y = t->right;
    Node* z = y->left;
    y->left = z->right;
    z->right = y;
    t->right = z->left;
    z->left = t;
    t = z; 
}


template <class K, class V>
int AVLTree<K, V>::height(Node* subtree)
{
   if (subtree == NULL)
        return -1;
    subtree->height = 1 + max(height(subtree->left), height(subtree->right));
    return subtree->height;
}


template <class K, class V>
int AVLTree<K, V>::balance(Node* subtree)
{
    if (subtree == NULL)
        return 0;
    return height(subtree->right) - height(subtree->left);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    int curBF = balance(subtree);
    
    if(curBF > 1)
    {
        if(balance(subtree->right) == 1)
        	rotateLeft(subtree);
        else
            rotateRightLeft(subtree);
    }
    else if(curBF < -1)
    {
        if(balance(subtree->left) == -1)
            rotateRight(subtree);
        else
            rotateLeftRight(subtree);
    }
    height(root);
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
