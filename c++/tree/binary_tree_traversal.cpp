//
// Created by Hong,Jian on 2018/2/2.
//

#include <vector>
#include <stack>

using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    /**
     * 前序遍历
     *
     * @param root
     * @return
     */
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> node;
        vector<int> ret;
        TreeNode* temp;

        if (root == NULL) {
            return ret;
        }

        node.push(root);
        while (! node.empty()) {
            temp = node.top();
            node.pop();

            ret.push_back(temp->val);
            if (temp->right != NULL) {
                node.push(temp->right);
            }
            if (temp->left != NULL) {
                node.push(temp->left);
            }
        }

        return ret;
    }

    /**
     * 中序遍历
     *
     * @param root
     * @return
     */
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> node;
        vector<int> ret;

        if (root == NULL) {
            return ret;
        }

        TreeNode* temp;
        TreeNode* ptr = root->left;

        node.push(root);
        while (! node.empty() || ptr != NULL) {
            if (ptr == NULL) {
                temp = node.top();
                node.pop();
                ret.push_back(temp->val);
                if (temp->right != NULL) {
                    ptr = temp->right;
                } else {
                    ptr = NULL;
                }
            } else {
                node.push(ptr);
                ptr = ptr->left;
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
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> node;
        vector<int> ret;
        TreeNode* temp;
        TreeNode* last = root;

        if (root == NULL) {
            return ret;
        }

        node.push(root);
        while (! node.empty()) {
            temp = node.top();

            //已在出栈中，避免重复节点入栈
            if (temp->left == last || temp->right == last) {
                node.pop();
                ret.push_back(temp->val);
                last = temp;
                continue;
            }
            //如果左右皆为空，同样出栈
            if (temp->left == NULL && temp->right == NULL) {
                node.pop();
                ret.push_back(temp->val);
                last = temp;
                continue;
            }
            if (temp->right != NULL) {
                node.push(temp->right);
            }
            if (temp->left != NULL) {
                node.push(temp->left);
            }
        }

        return ret;
    }

    /**
     * 层序遍历
     *
     * @param root
     * @return
     */
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<TreeNode*>> node;
        vector<vector<int>> ret;

        if (root == NULL) {
            return ret;
        }

        vector<TreeNode*> empty_n;
        vector<int> empty_i;
        node.push_back(empty_n);
        int depth = 0;
        node[depth].push_back(root);
        while (true) {
            //如果没有新的节点，则不再遍历
            int more = 0;
            for (int i = 0; i < node[depth].size(); i++) {
                if (depth >= ret.size()) {
                    ret.push_back(empty_i);
                }
                ret[depth].push_back(node[depth][i]->val);
                //如果左右子树不为空，则插入node中
                if (node[depth][i]->left != NULL || node[depth][i]->right != NULL) {
                    if (depth + 1 >= node.size()) {
                        node.push_back(empty_n);
                    }
                    more = 1;
                }

                if (node[depth][i]->left != NULL) {
                    node[depth+1].push_back(node[depth][i]->left);
                }

                if (node[depth][i]->right != NULL) {
                    node[depth+1].push_back(node[depth][i]->right);
                }
            }

            if (! more) {
                break;
            }

            depth ++;
        }

        return ret;
    }
};

int main() {
    struct TreeNode a = {3};
    struct TreeNode b = {9};
    struct TreeNode c = {20};
    struct TreeNode d = {15};
    struct TreeNode e = {17};
    a.left = &b;
    a.right = &c;
    c.left = &d;
    c.right = &e;

    Solution s = Solution();
    vector<vector<int>> ret = s.levelOrder(&a);
}