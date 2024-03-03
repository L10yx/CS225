/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#define INI_MIN -0x7fffffff - 1
template <typename T>
const T BinaryTree<T>::imp = T(INI_MIN);
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node *subRoot)
{
    if (subRoot == NULL) return;
    Node *t = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = t;
    mirror(subRoot->left);
    mirror(subRoot->right);
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    vector<T> v = {0};
    return isOrdered(root, v);
}

template <typename T>
bool BinaryTree<T>::isOrdered(Node *subRoot, vector<T> &v) const
{
    bool flag = true;
    if(subRoot != NULL){
      flag = flag && isOrdered(subRoot->left, v);
      if (subRoot->elem < v.back()) flag = false;
      v.push_back(subRoot->elem);
      flag = flag && isOrdered(subRoot->right, v);
    }
    return flag;
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    paths = vector<vector<T>>(1);
    paths[0] = vector<T>(0);
    if (root->left != nullptr) {
        paths.back().push_back(root->elem);
        printPaths(paths, root->left);       
    }
    if (root->right != nullptr) {
        printPaths(paths, root->right);       
    }
    paths.pop_back();
}

template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths, Node *subRoot) const
{
    paths.back().push_back(subRoot->elem);
    if (subRoot->left != nullptr) {
        printPaths(paths, subRoot->left);
        if (subRoot->right == nullptr) {
            paths.back().pop_back();
            return;
        }
    }

    if (subRoot->right != nullptr) {
        printPaths(paths, subRoot->right);
        paths.back().pop_back();
        return;       
    }
    else {
        paths.push_back(vector<T>(paths.back().begin(),paths.back().end()));
        paths.back().pop_back();
        return;
    }
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    return sumDistances(root);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node *subRoot) const
{
    unsigned d = 0;
    if(subRoot != NULL){
      if (subRoot->left != nullptr) 
      d += sumDistances(subRoot->left) + sumSons(subRoot->left) + 1;
      if (subRoot->right != nullptr)
      d += sumDistances(subRoot->right) + sumSons(subRoot->right) + 1;
    }
    return d;
}

template <typename T>
int BinaryTree<T>::sumSons(Node *subRoot) const
{
    unsigned s = 0;
    if(subRoot != NULL){
      if (subRoot->left != nullptr) s += sumSons(subRoot->left) + 1;
      if (subRoot->right != nullptr) s += sumSons(subRoot->right) + 1;
    }
    return s;
}

template <typename T>
T BinaryTree<T>::kthSmallest(int order) const
{
    if (order <= 0 || order > sumSons(root) + 1) return imp;
    return kthSmallest(root, order);
}

template <typename T>
T BinaryTree<T>::kthSmallest(Node *subRoot, int order) const
{
    if (!subRoot) return imp;
    if (order <= 0 || order > sumSons(root) + 1) return imp;
    if (subRoot->left != nullptr){
        if (sumSons(subRoot->left) < order - 2) {
            return kthSmallest(subRoot->right, order - sumSons(subRoot->left) - 2);
        }
        else if (sumSons(subRoot->left) == order - 2) {
            return subRoot->elem;
        }
        else {
            return kthSmallest(subRoot->left, order);
        }
    }
    if (order == 1) return subRoot->elem;
    return kthSmallest(subRoot->right, order - 1);
}
