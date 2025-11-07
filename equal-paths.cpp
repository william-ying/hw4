#ifndef RECCHECK
#include <algorithm>
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    if (root == NULL) return true;
    if (root->left == NULL || root->right == NULL) return true;
    return (depth(root->left) == depth(root->right));

}

int depth(Node * root) {
    if (root == nullptr) {
        return 0;
    }
    return std::max(depth(root->left), depth(root->right)) + 1;
}
