//
// Created by Hong,Jian on 2018/2/1.
//

#include <iostream>
#include <vector>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
class Solution {
public:
    int maxDepth(Node* root) {
        if (root == NULL) {
            return 0;
        }

        if (root->children.size() == 0) {
            return 1;
        }

        int max = 1;
        int temp = 0;
        int childMax = 0;
        for (int i = 0; i < root->children.size(); ++i) {
            temp = maxDepth(root->children[i]);
            if (temp > childMax) {
                childMax = temp;
            }
        }
        max += childMax;

        return max;
    }
};

int main () {
    return 0;
}