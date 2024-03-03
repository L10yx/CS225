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
  	if (first[curDim] == second[curDim]) return (first < second); // if equal in curDim, tiebreak 
  	return (first[curDim] < second[curDim]);  
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target, const Point<Dim>& currentBest, const Point<Dim>& potential) const
{
    double dcur = distancesquare(target, currentBest);
    double dpot = distancesquare(target, potential);
    if(dpot == dcur) return (potential < currentBest);  // if equal in curDim, tiebreak
    return (dpot < dcur);
}

template <int Dim>
double KDTree<Dim>::distancesquare(const Point<Dim>& target, const Point<Dim>& point) const {
  double dis = 0;
  for(int i = 0; i < Dim; i++) {
    dis += (target[i] - point[i]) *(target[i] - point[i]); // calculate sum distance square
  }
  return dis;
}

template <int Dim>
void KDTree<Dim>::swap(Point<Dim>& a, Point<Dim>& b) {
	Point<Dim> temp = a;
	a = b;
	b = temp;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::select(vector<Point<Dim>>& list, unsigned left, unsigned right, unsigned k, int dim) {
  	if (left >= right) return list[left];
  	Point<Dim> pvalue = list[k];
  	swap(list[k], list[right]); //swap pivot value and end of list
  	unsigned t = left; // temperary store index
  	for (unsigned i = left; i < right; i++){ //traverse points moving those less than pivot value
    	if (smallerDimVal(list[i], pvalue, dim)) { //swap if less than
			swap(list[t], list[i]);
			t++;
    	}
  	}
	swap(list[t], list[right]);
  	if (k == t) return list[k];
  	else if (k < t) return select(list, left, t - 1, k, dim); // Traverse left
  	else return select(list, t + 1, right, k, dim); // Traverse right
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDTreeHelper(vector<Point<Dim>>& Points, unsigned left, unsigned right, int dim) {
    if (Points.empty() || left > right || 
		left < 0 || right >= Points.size() || 
		right < 0 || left >= Points.size()) return nullptr;   // check if in range
    unsigned mid = (left + right) / 2;  // middle one
    KDTreeNode* subroot_ = new KDTreeNode(select(Points, left, right, mid, dim % Dim));
    size++;
    dim++;
    subroot_->left = KDTreeHelper(Points, left, mid - 1, dim);  // recurse left 
    subroot_->right = KDTreeHelper(Points, mid + 1, right, dim);  // recurse right 
    return subroot_;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    size = 0;
    vector<Point<Dim>> Points;
    Points.assign(newPoints.begin(), newPoints.end());
    root = KDTreeHelper(Points, 0, Points.size()-1, 0);
}

template <int Dim>
void KDTree<Dim>::_copy(KDTreeNode* subroot, KDTreeNode* otherroot) {
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
  	if (this != rhs) {
		_clear(root);
		_copy(root, rhs.root);		
	}
  	return *this;
}

template <int Dim>
void KDTree<Dim>::_clear(KDTreeNode * subroot) {
	if (subroot == nullptr) return;
	_clear(subroot->left); // recurse left
	_clear(subroot->right); // recurse right
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
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode* subroot, const Point<Dim>& query, int dim) const {
	if (subroot->left == nullptr && subroot->right == nullptr) return subroot->point;
	Point<Dim> currentBest = subroot->point;
	bool flag = smallerDimVal(query, subroot->point, dim);
	if ((flag && subroot->left != nullptr) || subroot->right == nullptr) 
		currentBest = findNearestNeighbor(subroot->left, query, (dim + 1) % Dim); //traverse left
	else 
		currentBest = findNearestNeighbor(subroot->right, query, (dim + 1) % Dim); // traverse right
	if (shouldReplace(query, currentBest, subroot->point)) currentBest = subroot->point; // Check if swap needed
	double r = distancesquare(query, currentBest);
	double dis = (subroot->point[dim] - query[dim]) * (subroot->point[dim] - query[dim]);
	if (dis <= r) { // Check if traverse the other subtree
		KDTreeNode* node;
		if (flag) node = subroot->right;
		else node = subroot->left;
		if (node != nullptr) {  // If we can traverse other subtree, then traverse
			Point<Dim> otherBest = findNearestNeighbor(node, query, (dim + 1) % Dim);
			if (shouldReplace(query, currentBest, otherBest)) currentBest = otherBest; // Check if replace needed
		}
	}
	return currentBest;
}