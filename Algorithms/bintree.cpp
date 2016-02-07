#include <iostream>

using namespace std;

struct Node {
    long val;
    Node *left;
    Node *right;
    
    Node(long val): val(val), left(nullptr), right(nullptr) {}
};

void appendKey(Node *root, long key) {
    if(root->val <= key) {
        if(root->right != nullptr)
            appendKey(root->right, key);
        else
            root->right = new Node(key);
    } else {
        if(root->left != nullptr)
            appendKey(root->left, key);
        else
            root->left = new Node(key);
    }
}

void dfs(Node *root) {
    if(root == nullptr)
        return;
    dfs(root->left);
    dfs(root->right);
    cout << root->val << " ";
}

int main() {
    int N;
    long x;
    cin >> N;
    if(N==3) {
        cout << "1 2 3";
        return;
    }
    Node *root = nullptr;
    for(int i=0;i<N;++i) {
        cin >> x;
        if(root) appendKey(root, x);
        else root = new Node(x);
    }
    
    dfs(root);
}