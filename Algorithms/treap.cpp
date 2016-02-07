#include <iostream>
#include <random>
#include <queue>
#include <sstream>

using namespace std;

template<typename T>
void print_tree(T& tree) {
    queue<pair<const typename T::Node*, long>> q;
    q.push(make_pair(tree.get_root(), 0));
    
    long current_level = 0;
    cout << "=====\n";
    while(!q.empty()) {
        pair<const typename T::Node*, long> elem = q.front();
        q.pop();
        if(!elem.first)
            continue;
        if(elem.second != current_level) {
            cout << "\n";
            current_level = elem.second;
        }
        q.push(make_pair(elem.first->left, current_level+1));
        q.push(make_pair(elem.first->right, current_level+1));
        stringstream s;
        s << "(";
        if(elem.first->left) s << elem.first->left->key;
        s << ",";
        if(elem.first->right) s << elem.first->right->key;
        s << ")";
        cout << elem.first->key << s.str() << " ";
    }
    cout << "\n";
}

template<typename T, typename P=int>
class treap {
public:
    struct Node {
        T key = 0;
        P priority = 0;
        Node *left = nullptr;
        Node *right = nullptr;
        
        Node(): priority(get_random_priority()) {}
        Node(T key): key(key), priority(get_random_priority()) {}
        Node(T key, P priority): key(key), priority(priority) {}
        Node(T key, P priority, Node* left, Node* right): key(key), priority(priority), left(left), right(right) {}
    };
    
    treap() {}
    
    pair<Node*, Node*> split(T key) {
        Node *left;
        Node *right;
        split_internal(root_, key, left, right);
        return make_pair(left, right);
    }
    
    Node * merge(Node *left, Node *right) {
        return merge_internal(left, right);
    }
    
    void insert(T key) {
        insert(key, get_random_priority());
    }
    
    void insert(T key, P priority) {
        if (!root_) {
            root_ = new Node(key, priority);
            return;
        }
        
        Node * current = root_;
        Node * parent = nullptr;
        while(current && current->priority > priority) {
            parent = current;
            if(key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        
        if(!parent) {
            insert_internal(root_, key, priority);
            return;
        }
        
        if(key < parent->key)
            insert_internal(parent->left, key, priority);
        else
            insert_internal(parent->right, key, priority);
    }
    
    void insert2(T key, P priority) {
        Node* left, *right;
        split_internal(root_, key, left, right);
        root_ = merge(left, new Node(key, priority));
        root_ = merge(root_, right);
    }
    
    bool erase(T key) {
        Node *& current = root_;
        while(current && current->key != key) {
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        if(!current)
            return false;
        
        Node* temp = current;
        current = merge(current->left, current->right);
        delete temp;
        return true;
    }
    
    const Node* get_root() { return root_; }
private:
    Node* root_ = nullptr;
    
    static int get_random_priority() {
        static default_random_engine eng { (random_device())() };
        static uniform_int_distribution<P> dist { numeric_limits<P>::min(), numeric_limits<P>::max() };
    
        return dist(eng);
    }
    
    void split_internal(Node *node, T key, Node*& left, Node*& right) {
        if (!node) {
            left = nullptr;
            right = nullptr;
        } else if ( node->key <= key) {
            split_internal(node->right, key, node->right, right);
            left = node;
        } else {
            split_internal(node->left, key, left, node->left );
            right = node;
        }
    }
    
    Node* merge_internal(Node* left, Node* right) {
        if(!left || !right)
            return left ? left : right;
        
        if( left->priority > right->priority ) {
            left->right = merge_internal( left->right, right);
            return left;
        } 
        
        right->left = merge_internal(left, right->left );
        return right;
    }
    
    void insert_internal(Node*& root, T key, P priority) {
        Node *left, *right;
        split_internal(root, key, left, right);
        root = new Node(key, priority, left, right);
    }
};

template<typename T>
class naive_tree {
public:
    struct Node {
        T key;
        Node *left;
        Node *right;
        
        Node(T key): key(key), left(nullptr), right(nullptr) {}
    };
    
    void insert(T key) {
        if(!root_)
            root_ = new Node(key);
        else
            insert_internal(root_,key);
    }
    
    const Node* get_root() { return root_; }
    
private:
    Node *root_ = nullptr;
    
    void insert_internal(Node *root, T key) {
        if(root->key <= key) {
            if(root->right != nullptr)
                insert_internal(root->right, key);
            else
                root->right = new Node(key);
        } else {
            if(root->left != nullptr)
                insert_internal(root->left, key);
            else
                root->left = new Node(key);
        }
    }
};

template<typename T>
long get_depth(const T* root) {
    long depth = 0;
    get_depth(root, 0, depth);
    return depth;
}

template<typename T>
void get_depth(const T* root, long current_depth, long& max_depth) {
    if(root == nullptr)
        return;
    
    current_depth++;
    if(max_depth < current_depth) max_depth = current_depth;
    
    get_depth(root->left, current_depth, max_depth);
    get_depth(root->right, current_depth, max_depth);
}

template<typename T>
void dfs(const T* root) {
    if(root == nullptr)
        return;
    dfs(root->left);
    dfs(root->right);
    cout << root->key << " ";
}



int main() {
    treap<long> t1;
    naive_tree<long> t2;
    
    long N;
    cin >> N;
    int x, p;
    for(int i=0; i<N; ++i) {
        cin >> x >> p;
        t1.insert(x,p);
        t2.insert(x);
    }
    
    cout << get_depth(t2.get_root()) - get_depth(t1.get_root()) << endl;
    
    return 0;
}