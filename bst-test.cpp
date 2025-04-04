#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    cout << "start" << endl;
    // // Binary Search Tree tests
    // BinarySearchTree<char,int> bt;
    // cout << "init" << endl;
    // bt.insert(std::make_pair('a',1));
    // bt.insert(std::make_pair('b',2));
    
    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // bt.remove('b');

    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');

    // zig-zag case

    cout << "\nZig-Zag Left-Right Rotation Test (c, a, b):" << endl;
    AVLTree<char, int> zigzagTree;
    zigzagTree.insert(std::make_pair('c', 1));
    zigzagTree.insert(std::make_pair('a', 2));
    zigzagTree.insert(std::make_pair('b', 3)); // This should trigger left-right rotation

    for(AVLTree<char, int>::iterator it = zigzagTree.begin(); it != zigzagTree.end(); ++it) 
    {
        cout << it->first << " => " << it->second << endl;
    }

        return 0;
}
