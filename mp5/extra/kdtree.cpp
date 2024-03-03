/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first, const Point<Dim>& second, int curDim) const
{
	if (curDim < 0 || curDim >= Dim) return false;  // if curDim not in range
  if(first[curDim] == second[curDim]) return (first < second); // if equal in curDim, tiebreak 
  return (first[curDim] < second[curDim]);  
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target, const Point<Dim>& currentBest, const Point<Dim>& potential) const
{
    double dcur = 0;
    double dpot = 0;
    for(int i = 0; i < Dim; i++) {
       	dcur += (target[i] - currentBest[i]) *( target[i] - currentBest[i]); // axxumulate distance to currentBest
       	dpot += (target[i] - potential[i]) * (target[i] - potential[i]); // accumulate distance to potential
    }
    if(dcur == dpot) return (potential < currentBest);  // if equal in curDim, tiebreak
    return (dpot < dcur);
}

template <int Dim>
Point<Dim>& KDTree<Dim>::select(vector<Point<Dim>>& list, int dim, unsigned left, unsigned right, unsigned k){
  	if (left == right) return list[left];
  	Point<Dim> pvalue = list[k];
  	Point<Dim> temp = list[k];
  	list[k] = list[right];
  	list[right] = temp; //swap pivot value and end of list
  	unsigned t = left; // temperary store index
  	for (unsigned i = left; i < right; i++){ //traverse points moving those less than pivot value
    	if(smallerDimVal(list[i], pvalue, dim)){ //swap if less than
        temp = list[t];
        list[t] = list[i];
        list[i] = temp;
        t++;
    	}
  	}
  	temp = list[t];
  	list[t] = list[right];
  	list[right] = temp;

  	if (k == t) return list[k];
  	else if(k < t) return select(list, dim, left, t - 1, k); // Traverse left
  	else return select(list, dim, t + 1, right, k); // Traverse right
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDTreeHelper(vector<Point<Dim>>& Points, int dim, unsigned left, unsigned right){
    if (Points.empty()) return nullptr;
    if (left < 0 || right >= Points.size() || right < 0 || left >= Points.size()) return nullptr;  
    if (left > right) return nullptr; // check if left <= right
    unsigned mid = (left+right)/2;  // middle one
    KDTreeNode* subroot_ = new KDTreeNode(select(Points, dim % Dim, left, right, mid));
    size++;
    dim++;
    subroot_->left = KDTreeHelper(Points, dim, left,mid - 1);  // recurse left 
    subroot_->right = KDTreeHelper(Points, dim, mid + 1, right);  // recurse right 
    return subroot_;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    size = 0;
    vector<Point<Dim>> Points;
    Points.assign(newPoints.begin(), newPoints.end());
    root = KDTreeHelper(Points, 0, 0, Points.size()-1);
}

template <int Dim>
void KDTree<Dim>::_copy(KDTreeNode * subroot, KDTreeNode * otherroot) {
  if (otherroot == nullptr) return;
	subroot = new KDTreeNode();
	subroot->point = otherroot->point;
	_copy(subroot->left, otherroot->left); // recurse left
	_copy(subroot->right, otherroot->right); // recurse right
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
	_copy(this->root, other.root);
	size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  	if (this != nullptr) _clear(root);
  	_copy(this->root, rhs.root);
  	size = rhs.size;
  	return *this;
}

template <int Dim>
void KDTree<Dim>::_clear(KDTreeNode * subroot) {
	if (subroot == nullptr) return;
	if (subroot->left != nullptr) _clear(subroot->left); // recurse left
	if (subroot->right != nullptr) _clear(subroot->right); // recurse right
	delete subroot;
	subroot = nullptr;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  	_clear(root);
    size = 0;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const {
    return findNearestNeighbor(root, query, 0); // helperfunction to recurse
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode * subroot, const Point<Dim>& query, int dim) const {
	Point<Dim> currentBest = subroot->point;
	bool flag;
	if (subroot->left == nullptr && subroot->right == nullptr) return subroot->point;

	if (smallerDimVal(query, subroot->point, dim)) { // Check if traverse left
		if (subroot->left == nullptr)  // traverse right
			currentBest = findNearestNeighbor(subroot->right, query, (dim + 1) % Dim);
		else  // traverse left
			currentBest = findNearestNeighbor(subroot->left, query, (dim + 1) % Dim);
		flag = true;
	}
	else { // Check if traverse right
		if (subroot->right == nullptr)  // traverse left
			currentBest = findNearestNeighbor(subroot->left, query, (dim + 1) % Dim);
		else  // traverse right
			currentBest = findNearestNeighbor(subroot->right, query, (dim + 1) % Dim);
		flag = false;
	}

	if (shouldReplace(query, currentBest, subroot->point)) currentBest = subroot->point; // Check if swap needed
	double r = 0;
	for (int i = 0; i < Dim; i++) { // Calculate radius of closest point
		r += (query[i] - currentBest[i]) * (query[i] - currentBest[i]);
	}
	double dis = subroot->point[dim] - query[dim];
	dis = dis * dis;

	if (dis <= r) { // Check if traverse the other subtree
		KDTreeNode* tnode;
    if (flag) tnode = subroot->right;
    else tnode = subroot->left;
		if (tnode != nullptr) {  // If we can traverse other subtree, then traverse
			Point<Dim> otherBest = findNearestNeighbor(tnode, query, (dim + 1) % Dim);
			if (shouldReplace(query, currentBest, otherBest)) currentBest = otherBest; // Check if replace needed
		}
	}
	return currentBest;
}

