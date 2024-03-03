#pragma once

#include <vector>

class DisjointSets {
public:
    // Creates n unconnected root nodes at the end of the vector
    void addelements(int num);

    // This function should compress paths and works as described in lecture.      
    int find(int elem);      

    /*This function should be implemented as union-by-size.
    That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) should point at the larger. 
    This function works as described in lecture, except that you should not assume that the arguments to setunion are roots of existing uptrees.
    Your setunion function SHOULD find the roots of its arguments before combining the trees. 
    If the two sets are the same size, make the tree containing the second argument point to the tree containing the first.*/
    void setunion(int a, int b);

    // Return size of root
    int size(int elem);

private:
    std::vector<int> _elems; 
};