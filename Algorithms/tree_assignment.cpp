#include <iostream>

using namespace std;

template<typename Key, typename Value>
class avl_tree {
public:
    struct Node {
        Key key;
        Value val;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
        size_t depth = 0;
        
        Node() {}
        
        Node(const Key& key, const Value& val): key(key), val(val) {}
        
        Node(const Key& key, const Value& val, const Node* left, const Node* right):
            key(key), val(val), left(left), right(right) {}            
            
        Node(const Key& key, const Value& val, const Node* left,
             const Node* right, Node* parent):
            key(key), val(val), left(left), right(right),
            parent(parent) {}
            
        Node(const Key& key, const Value& val, Node* parent):
            key(key), val(val), parent(parent) {}
    };
    
    Node* insert(const pair<Key, Value>& kv) {
        Node *node = insert_internal(root_, nullptr, kv);
        //balance_up(node);
        
        return node;
    }
    
    bool erase(const Key& key) {
        pair<bool, Node*> result = erase_internal(root_, key);
        //if(result.first)
        //    balance_up(result.second);
        return result.first;
    }
    
    bool erase(Node *node) {
        delete_node(node);
        return true;
    }
    
    const Node* root() const { return root_; }
    
    Node* root_not_safe() const { return root_; }
    
private:
    Node* root_ = nullptr;
    
    Node* insert_internal(Node*& root, Node* parent, const pair<Key, Value>& kv) {
        if(!root) {
            root = new Node(kv.first, kv.second, parent);
            return root;
        }
        
        if( kv.first < root->key )
            return insert_internal(root->left, root, kv);
        else if ( kv.first > root->key )
            return insert_internal(root->right, root, kv);
         
        root->val = kv.second;
        return root;
    }
    
    pair<bool, Node*> erase_internal(Node*& root, const Key& key) {
        if(!root)
            return make_pair(false,nullptr);
        
        if( key < root->key )
            return erase_internal(root->left, key);
        else if( key > root->key )
            return erase_internal(root->right, key);
        
        return make_pair(true, delete_node(root));
    }
    
    Node* delete_node(Node*& node) {
        if ( !node->left ) {
            Node *right = node->right;
            Node *parent = node->parent;
            delete node;
            node = right;
            if(node)
                node->parent = parent;
        } else if ( !node->right ) {
            Node *left = node->left;
            Node *parent = node->parent;
            delete node;
            node = left;
            if(node)
                node->parent = parent;
        } else {
            Node* min = node->right;
            while( min->left )
                min = min->left;
            (min->parent->left == min ? min->parent->left : min->parent->right) = min->right;
            if(min->right) min->right->parent = min->parent;
            node->key = min->key;
            node->val = min->val;
            delete min;
        }
        return node;
    }
    
    size_t max_depth(Node* left, Node *right) {
        if(!left && !right)
            return 0;
        else if(left && !right)
            return left->depth;
        else if(!left && right)
            return right->depth;
        else        
            return max(left->depth, right->depth);
    }
    
    void rotate_small_left(Node *&node) {
        Node* a = node;
        Node* b = a->right;
        a->right = b->left;
        b->left = a;
        
        if(a->right) a->right->parent = a;
        b->parent = a->parent;
        a->parent = b;
        
        a->depth = max_depth(a->left, a->right);
        b->depth = max_depth(b->left, b->right);
        
        node = b;
    }
    
    void rotate_small_right(Node *&node) {
        Node* b = node;
        Node* a = b->left;
        b->left = a->right;
        a->right = b;
        
        if(b->left) b->left->parent = b;
        a->parent = b->parent;
        b->parent = a;
        
        b->depth = max_depth(b->left, b->right);
        a->depth = max_depth(a->left, a->right);
        
        node = a;
    }
    
    void rotate_big_left(Node*& node) {
        rotate_small_right(node->right);
        rotate_small_left(node);
    }
    
    void rotate_big_right(Node*& node) {
        rotate_small_left(node->left);
        rotate_small_right(node);
    }
    
    void balance(Node*& node) {
        //small
        //высота(R) = высота(L) + 2 и высота(C)<=высота R
        //big
        //высота(R) = выоста(L) + 1 и высота(C)=высота(L)+2
        size_t l=0,r=0,c=0;
        if(node->left)
            l = node->left->depth;
        if(node->right)
            l = node->right->depth;
        if( r > l ) {
            if( node->right->left )
                c = node->right->left->depth;
            if (r == l+2 && c <= r)
                rotate_small_left(node);
            else if (r == l+1 && c == l+2)
                rotate_big_left(node);
        } else if ( l > r) {
            if( node->left->right )
                c = node->left->right->depth;
            if (l == r+2 && c <= l)
                rotate_small_right(node);
            else if (l == r+1 && c == r+2)
                rotate_big_right(node);
        }
    }
    
    void balance_up(Node* node) {
        if (!node)
            return;        
        while(node->parent != nullptr) {
            Node* parent = node->parent;
            if(parent->left == node)
                balance(parent->left);
            else
                balance(parent->right);
            node = parent;
        }
        balance(root_);        
    }
};

template<typename N>
void print_all(const N* node) {
    if(!node)
        return;
    
    print_all(node->left);
    cout << node->key << " (" << (node->left ? node->left->key : -1)
        << ", " << (node->right? node->right->key : -1)<< ")"
        << " : " << node->val << ", ";
    print_all(node->right);
}

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

using AVL = avl_tree<int,int>;

int insert(AVL& avl, int key ) {
    auto node = avl.insert(make_pair(key, 0));
    
    int count = 0;
        
    while(node->parent) {
        auto temp = node;
        node = node->parent;
        if(node->right == temp)
            node->val++;
        if(node->left == temp)
            count += node->val + 1;
    }
    
    return count;
}

void remove(AVL& avl, int pos ) {
    auto node = avl.root_not_safe();
    while(node->val != pos) {
        if(node->val > pos) {
            node = node->right;
        } else {
            pos = pos-node->val-1;
            node = node->left;
        }
    }
    
    auto key = node->key;
        
    while(node->parent) {
        auto temp = node;
        node = node->parent;
        if(node->right == temp)
            node->val--;
    }
    
    avl.erase(key);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    avl_tree<int ,int> avl;
    
    long N;
    cin >> N;
    int c, x;
    for(int i=0; i<N; ++i)
    {
        cin >> c >> x;
        if (c == 1) {
            cout << insert(avl, x) << " ";
        }
        if (c == 2) {
            remove(avl, x);
        }
        
        /*
        cout << std::endl;
        print_all(avl.root());
        cout << std::endl;
        */
    }
    
    return 0;
}