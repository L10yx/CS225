#include "dsets.h"

using namespace std;

// Creates n unconnected root nodes at the end of the vector
void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++)
        _elems.push_back(-1);
}

// This function should compress paths and works as described in lecture.
int DisjointSets::find(int elem) {
	if (_elems[elem] < 0) return elem; // return root
	else {
		int root = find(_elems[elem]); // recurse until root
		_elems[elem] = root;
		return root;
	}
}

 /* This function should be implemented as union-by-size.
    That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) should point at the larger. 
    This function works as described in lecture, except that you should not assume that the arguments to setunion are roots of existing uptrees.
    Your setunion function SHOULD find the roots of its arguments before combining the trees. 
    If the two sets are the same size, make the tree containing the second argument point to the tree containing the first.*/
void DisjointSets::setunion(int a, int b) {
    a = find(a); // find root of a
    b = find(b); // find root of b
    int newSize = _elems[a] + _elems[b]; // add up size
    // If the two sets are the same size or the first is larger, 
    // make the tree containing the second argument point to the tree containing the first
    if (_elems[a] <= _elems[b]) { 
        _elems[b] = a;
        _elems[a] = newSize;
    }
    else { // Else, set first point to second
        _elems[a] = b;
        _elems[b] = newSize;
    }
}

// Return size of root
int DisjointSets::size(int elem) {
    elem = find(elem); // find root of elem
    return _elems[elem] * -1; //return size
}
