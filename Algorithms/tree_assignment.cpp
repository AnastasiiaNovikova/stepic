#include <iostream>
#include <functional>

using namespace std;

struct Payload {
    unsigned long lcount = 0;
    unsigned long rcount = 0;
};

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
        return insert_internal(root_, nullptr, kv, nullptr);
    }
    
    Node* insert(const pair<Key, Value>& kv, function<void(Key, Value&)> func) {
        return insert_internal(root_, nullptr, kv, func);
    }
    
    bool erase(const Key& key) {
        pair<bool, Node*> result = erase_internal(root_, key, nullptr);
        return result.first;
    }
    
    bool erase(const Key& key, function<void(Key, Value&)> func) {
        pair<bool, Node*> result = erase_internal(root_, key, func);
        return result.first;
    }
    
    const Node* root() const { return root_; }
    
private:
    Node* root_ = nullptr;
    
    Node* insert_internal(Node*& root, Node* parent, const pair<Key, Value>& kv,
        function<void(Key, Value&)> func) {
        if(!root) {
            root = new Node(kv.first, kv.second, parent);
            return root;
        }
        
        if(func) func(root->key, root->val);
        
        if( kv.first < root->key )
            return insert_internal(root->left, root, kv, func);
        else if ( kv.first > root->key )
            return insert_internal(root->right, root, kv, func);
         
        root->val = kv.second;
        return root;
    }
    
    pair<bool, Node*> erase_internal(Node*& root, const Key& key, function<void(Key, Value&)> func) {
        if(!root)
            return make_pair(false,nullptr);
        
        if(func) func(root->key, root->val);
        
        if( key < root->key )
            return erase_internal(root->left, key, func);
        else if( key < root->key )
            return erase_internal(root->right, key, func);
        
        return make_pair(true, delete_node(root, func));
    }
    
    Node* delete_node(Node*& node, function<void(Key, Value&)> func) {
        if ( !node->left ) {
            Node *right = node->right;
            Node *parent = node->parent;
            delete node;
            node = right;
            node->parent = parent;
        } else if ( !node->right ) {
            Node *left = node->left;
            Node *parent = node->parent;
            delete node;
            node = left;
            node->parent = parent;
        } else {
            Node* min = node->right;
            while( min->left )
                min = min->left;
            (min->parent->left == min ? min->parent->left : min->parent->right) = min->right;
            if(min->right) min->right->parent = min->parent;
            node->key = min->key;
            if(func) func(node->key, node->val);
            else node->val = min->val;
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
};

template<typename N>
void print_all(const N* node) {
    if(!node)
        return;
    
    print_all(node->left);
    cout << node->key << " : (" << node->val.lcount << "," << node->val.rcount << "), ";
    print_all(node->right);
}

template<typename N>
int count(const N* node, int accum) {
    if(!node)
        return accum;
    
    if(node->parent && node->parent->left != node)
        return accum;
    
    return count(node->parent, 1 + node->val.rcount + accum);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    avl_tree<unsigned long, Payload> avl;
    
    auto incr = [&avl](unsigned long ikey) {
        avl_tree<unsigned long, Payload>::Node* node =
            avl.insert(make_pair(ikey, Payload()), [&ikey](unsigned int key, Payload &pd) {
                if( ikey < key )
                    pd.lcount++;
                else
                    pd.rcount++;
            });
        return count(node, 0);
    };
    
    auto decr = [&avl](unsigned long ikey) {
        avl.erase(ikey, [&ikey](unsigned int key, Payload &pd){
            if( ikey < key )
                pd.lcount--;
            else
                pd.rcount--;
        });
    };
    
    long N;
    cin >> N;
    int c, x;
    while(cin >> c) {
        cin >> x;
        if (c == 1) {
            cout << incr(x) << " ";
        }
        if (c == 2) {
            decr(x);
        }
        cout << std::endl;
        print_all(avl.root());
        cout << std::endl;
    }
    
    return 0;
}