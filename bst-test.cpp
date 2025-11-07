#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<int,int> bt;
    bt.insert(std::make_pair(-94,1));
    bt.insert(std::make_pair(-52,1));
    bt.insert(std::make_pair(77,1));
    bt.insert(std::make_pair(36,1));
    bt.insert(std::make_pair(64,1));
    bt.insert(std::make_pair(54,1));
    bt.insert(std::make_pair(-73,1));
    bt.insert(std::make_pair(52,1));
    bt.insert(std::make_pair(51,1));
    bt.insert(std::make_pair(8,1));
    bt.insert(std::make_pair(-81,1));
    bt.insert(std::make_pair(-43,1));
    bt.insert(std::make_pair(129,1));
    bt.insert(std::make_pair(9,1));
    bt.insert(std::make_pair(117,1));
    bt.insert(std::make_pair(-38,1));
    bt.insert(std::make_pair(21,1));
    bt.insert(std::make_pair(131,1));
    bt.insert(std::make_pair(-90,1));
    bt.insert(std::make_pair(34,1));
    bt.insert(std::make_pair(5,1));
    bt.insert(std::make_pair(-131,1));
    bt.insert(std::make_pair(45,1));
    bt.insert(std::make_pair(-4,1));
    bt.insert(std::make_pair(130,1));
    bt.insert(std::make_pair(13,1));
    bt.insert(std::make_pair(10,1));
    bt.insert(std::make_pair(72,1));
    bt.insert(std::make_pair(-134,1));
    bt.insert(std::make_pair(95,1));
    bt.insert(std::make_pair(100,1));
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<int,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find(90) != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove(90);

    // AVL Tree Tests
    // AVLTree<char,int> at;
    // at.insert(std::make_pair('a',1));
    // at.insert(std::make_pair('b',2));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');

    return 0;
}
