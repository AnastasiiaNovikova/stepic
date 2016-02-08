#include <iostream>
#include <algorithm>

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
        balance_up(node);
        return node;
    }
    
    bool erase(const Key& key) {
        pair<bool, Node*> result = erase_internal(root_, key);
        if(result.first)
            balance_up(result.second);
        return result.first;
    }
    
    const Node* root() const { return root_; }
    
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
        else if( key < root->key )
            return erase_internal(root->right, key);
        
        return make_pair(true, delete_node(root));
    }
    
    Node* delete_node(Node*& node) {
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

template<typename K, typename N>
void get_num(const K k, const N* node, int& count, bool& found) {
    if(!node)
        return;
    
    get_num(k, node->right, count, found);
    if( node->key == k ) found = true;
    if(!found) {
        count++;
        get_num(k, node->left, count, found);
    }
}

template<typename Node>
int findKthLargest(Node *root, int k) {
    Node *prev = NULL;
    Node *current = root;

    while(current->right != NULL) {
        prev = current;
        current = current->right;
    }

    while(k != 0) {
        if (current == NULL)
            return -1;

        if(prev == current->right || prev == NULL)
        {
            --k;
            prev = current;
            if(current->left != NULL)
                current = current->left;
            else
                current = current->parent;
        }
        else if(prev == current->left)
        {
            prev = current;
            current = current->parent;
        }
        else if(prev == current->parent)
        {
            prev = current;
            if(current->right != NULL)
                current = current->right;
            else if(current->left != NULL) {
                --k;
                current = current->left;
            } else {
                --k;
                current = current->parent;
            }
        }
    }

    return prev->key;
}

template<typename N>
void print_all(const N* node) {
    if(!node)
        return;
    
    print_all(node->left);
    cout << node->key << " : (" << node->val << "), ";
    print_all(node->right);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    avl_tree<unsigned long,int> avl;
    
    long N;
    cin >> N;
    int c, x;
    for(int i=0; i<N; ++i)
    {
        cin >> c >> x;
        if (c == 1) {
            avl.insert(make_pair(x,0));
            int count  = 0;
            bool found = false;
            get_num(x,avl.root(),count, found);
            cout << count << " ";
        }
        if (c == 2) {
            avl.erase(findKthLargest(avl.root(), x));
        }
        
        /*
        cout << std::endl;
        print_all(avl.root());
        cout << std::endl;
        */
    }
    
    return 0;
}