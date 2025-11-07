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
    return (depth(root) != -1);

}

int depth(Node * root) {
    if (root->left == NULL && root->right == NULL) return 0;
    else if (root->right == NULL) return depth(root->left);
    else if (root->left == NULL) return depth(root->right);
    else if (depth(root->left) == -1 || depth(root->right) == -1) return -1;
    else if (depth(root->left) == depth(root->right)) {return depth(root->left) + 1;}
    else {
        return -1;
    }
}
