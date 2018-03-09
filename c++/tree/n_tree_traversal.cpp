//
// Created by Hong,Jian on 2018/2/1.
//

#include <iostream>
#include <queue>
#include <vector>
#include <stack>

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
    /**
     * 层序遍历
     *
     * @param Node* root
     * @return
     */
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<Node*>> mark;
        vector<vector<int>> ret;
        if (root == NULL) {
            return ret;
        }

        int depth = 0;
        vector<Node*> empty_n;
        vector<int> empty_i;
        mark.push_back(empty_n);
        mark[0].push_back(root);
        Node* temp;

        while (true) {
            int more = 0;
            for (int j = 0; j < mark[depth].size(); ++j) {
                if (mark.size() <= depth) {
                    mark.push_back(empty_n);
                }
                if (ret.size() <= depth) {
                    ret.push_back(empty_i);
                }
                temp = mark[depth][j];

                ret[depth].push_back(temp->val);
                if (temp->children.size() == 0) {
                    continue;
                }

                for (int i = 0; i < temp->children.size(); ++i) {
                    if (mark.size() <= depth + 1) {
                        mark.push_back(empty_n);
                    }
                    mark[depth+1].push_back(temp->children[i]);
                    more = 1;
                }
            }
            if (more == 0) {
                break;
            }
            depth ++;
        }

        return ret;
    }

    /**
     * 前序遍历
     *
     * @param root
     * @return
     */
    vector<int> preorder(Node *root)
        {
            vector<int> ret;

            if (root == NULL) {
                return ret;
            }

            stack<Node*> node_stack;
            //将根节点压入栈中
            node_stack.push(root);

            while (! node_stack.empty()) {
                Node* temp;
                temp = node_stack.top();
                node_stack.pop();
                ret.push_back(temp->val);

                if (temp->children.size() > 0) {
                    for (int i = (int)temp->children.size() - 1; i >= 0; i--) {
                        if (temp->children[i] == NULL) {
                            continue;
                        }
                        node_stack.push(temp->children[i]);
                    }
                }
            }

            return ret;
        }

    /**
     * 后序遍历
     *
     * @param root
     * @return
     */
    vector<int> postorder(Node* root) {
        vector<int> ret;

        if (root == NULL) {
            return ret;
        }

        stack<Node*> node_stack;
        //将根节点压入栈中
        node_stack.push(root);
        Node * last = root;

        while (! node_stack.empty()) {
            Node* temp;
            temp = node_stack.top();

            //要插入的节点，是否出现在上一次出栈的记录中，避免死循环
            bool out = false;

            if (temp->children.size() > 0) {
                for (int i = (int)temp->children.size() - 1; i >= 0; i--) {
                    if (temp->children[i] == last) {
                        out = true;
                        break;
                    }
                }
            } else {//如果无子节点，则应执行出栈
                out = true;
            }

            if (! out) {
                for (int i = (int)temp->children.size() - 1; i >= 0; i--) {
                    node_stack.push(temp->children[i]);
                }
            } else {
                ret.push_back(temp->val);
                last = temp;
                node_stack.pop();
            }
        }

        return ret;
    }
};

int main() {
    //初始化测试数据
    vector<Node*> empty_v;
    Node* root  = new Node(1, empty_v);
    Node* node3 = new Node(3, empty_v);
    Node* node2 = new Node(2, empty_v);
    Node* node4 = new Node(4, empty_v);
    Node* node5 = new Node(5, empty_v);
    Node* node6 = new Node(6, empty_v);
    vector<Node*> list56;
    list56.push_back(node5);
    list56.push_back(node6);

    vector<Node*> list3;
    list3.push_back(node3);
    list3.push_back(node2);
    list3.push_back(node4);

    root->children = list3;
    node3->children = list56;

    Solution* s = new Solution();
    vector<vector<int>> ret = s->levelOrder(root);

    return 0;
}