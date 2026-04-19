#include "OrderedSet.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;
namespace orderedset{
    DuplicateValueException::DuplicateValueException(const string& value)
        : logic_error("Duplicate value: " + value + " already exists in the set."){}

    struct Node{
        int value;
        Node *left;
        Node *right;
        int height;
            
        Node(int v) : value(v), left(nullptr), right(nullptr),  height(1) {}
    };   

class OrderedSet::Impl{
    public:
        Node *root;
        int nodeCount;

        Impl() : root(nullptr), nodeCount(0){}
        ~Impl() {
            destroyTree(root);
        }

        Impl(const Impl &other) : root(nullptr), nodeCount(0){
            root = copyTree(other.root);
            nodeCount = other.nodeCount;
        }

        static int nodeHeight(Node *n){
            if(n != nullptr){                   
                return n->height;
            } else 
                return 0;
        }

        static int balance(Node *n){
            if(n != nullptr){
                return (nodeHeight(n->left) - nodeHeight(n ->right));
            }else
                return 0;
        }
        
        static void updateHeight(Node *n){
            if(n != nullptr){
                n->height = 1 + std::max(nodeHeight(n->left), nodeHeight(n->right));
                }
        }
        static Node *rotateRight(Node *y){
            Node *x = y->left;
            Node *temp = x->right;
            x->right = y;
            y->left = temp;
            updateHeight(y);
            updateHeight(x);
            return x;
        }
            
        static Node *rotateLeft(Node *x){
            Node *y = x->right;
            Node *temp = y->left;               
            y->left = x;
            x->right = temp;
            updateHeight(x);
            updateHeight(y);
            return y;
        }
           
        static Node *rebalance(Node *n){
            updateHeight(n);
            int factor = balance(n);

            //left-left
            if(factor > 1 && balance(n->left) >= 0){
                return rotateRight(n);
            }
            //left-right
            if(factor > 1 && balance(n->left) < 0){
                n->left = rotateLeft(n->left);
                return rotateRight(n);
            }
            //right-right
            if(factor < -1 && balance(n->right) <= 0){
                return rotateLeft(n);
            }
                
            //right-left
            if(factor < -1 && balance(n->right) > 0){
                n->right = rotateRight(n->right);
                return rotateLeft(n);
            }
            return n;
        }

        Node *insertNode(Node *n, int value, bool &inserted){
            if(n == nullptr){
                inserted = true;
                return new Node(value);
            }
            if(value < n->value){
                n->left = insertNode(n->left, value, inserted);
            } else 
                if(value > n->value){
                    n->right = insertNode(n->right, value, inserted);
                }else {
                    inserted = false;
                    return n;
                }
            return rebalance(n);

        }

        Node *deleteNode(Node *n, int value, bool &removed){
            if(n == nullptr){
                removed = false;
                return nullptr;
            }
            if(value < n->value){
                n->left = deleteNode(n->left, value, removed);
            } else 
                if(value > n->value){
                    n->right = deleteNode(n->right, value, removed);
                } else {
                    removed = true;
                    if(!n->left || !n->right){
                        Node *child;
                        if(n->left){
                            child = n->left;
                        } else 
                            child = n->right;

                        delete n;
                        return child;
                    }
                    Node *replace = minNode(n->right);
                    n->value = replace->value;
                    bool ignored = false;
                    n->right = deleteNode(n->right, replace->value, ignored);
                }
                return rebalance(n);
        }
            
        static Node *minNode(Node *n){
            while(n->left){
                n = n->left;
            }
            return n;
        }

        static bool searchNode(Node *n, int value){
            while(n){
                if(value < n->value){
                    n = n->left;
                } else 
                    if(value > n->value){
                        n = n->right;
                    } else 
                        return true;
            }
            return false;
        }

        static void inorder(Node *n, vector<int>& out){
            if(n == nullptr) return;
            inorder(n->left, out);
            out.push_back(n->value);
            inorder(n->right, out);
        }
            
        static Node *copyTree(Node *n){
            if(n == nullptr) return nullptr;
            Node *newNode = new Node(n->value);
            newNode->height = n->height;
            newNode->left = copyTree(n->left);
            newNode->right = copyTree(n->right);
            return newNode;

        }
            
        static void destroyTree(Node *n){
            if(n == nullptr) return;
            destroyTree(n->left);
            destroyTree(n->right);
            delete n;
        }
            
        void clear(){
            destroyTree(root);
            root = nullptr;
            nodeCount = 0;
        }
};

    OrderedSet::OrderedSet() 
        : pImpl(new Impl()){}

    OrderedSet::OrderedSet(const OrderedSet &other)
        : pImpl(new Impl(*other.pImpl)){}

    OrderedSet::OrderedSet(OrderedSet&& other) noexcept {
        if (other.pImpl) {
            pImpl = other.pImpl;
            other.pImpl = new Impl(); 
        } else {
            pImpl = new Impl();
        }
    }
    OrderedSet::~OrderedSet(){
        delete pImpl;
    }
    OrderedSet &OrderedSet::operator=(const OrderedSet &other){
        if(this != &other){
            Impl* newImpl = new Impl(*other.pImpl);
            delete pImpl;
            pImpl = newImpl;
        }
        return *this;
    }
    void OrderedSet::insert(int value){
        bool inserted = false;
        pImpl->root = pImpl->insertNode(pImpl->root, value, inserted);
        if(inserted == false){
            throw DuplicateValueException(to_string(value));
        }
        ++pImpl->nodeCount;
    }
    OrderedSet &OrderedSet::operator+=(int value){
        insert(value);
        return *this;
    }
    bool OrderedSet::contains(int value) const{
        return !Impl::searchNode(pImpl->root, value);
    }
    int OrderedSet::operator[](int value) const{
        if (contains(value)){
            return 1;
        } else
            return 0;
    }
    int OrderedSet::size() const{
        return pImpl->nodeCount;
    }
    bool OrderedSet::empty() const{
        return pImpl->nodeCount == 0;
    }
    string OrderedSet::toString() const {
        if (!pImpl || !pImpl->root) {
            return "OrderedSet { size=0, height=0, elements=[ ] }";
        }

        vector<int> elements = getElements(); 
        stringstream ss;
        
        ss << "OrderedSet { size=" << pImpl->nodeCount  << ", height=" << height() << ", elements=[ ";

        if (elements.size() <= 10) {
            for (int v : elements) {
                ss << v << " ";
            }
        } else {
            for (size_t i = 0; i < 5; ++i) ss << elements[i] << " ";
            ss << "... ";
            for (size_t i = elements.size() - 5; i < elements.size(); ++i) {
                ss << elements[i] << " ";
            }
        }
        
        ss << "] }";
        return ss.str();
    }
    void OrderedSet::update(int oldValue, int newValue) {
        if (!contains(oldValue)){
            throw out_of_range("update(): value " + to_string(oldValue) + " not found in set.");
        }
        if (oldValue != newValue && contains(newValue)){
            throw DuplicateValueException(to_string(newValue));
        }
        remove(oldValue);
        insert(newValue);
    }
    vector <int> OrderedSet::getElements() const{
        vector <int> elements;
        Impl::inorder(pImpl->root, elements);
        return elements;

    }
    OrderedSet &OrderedSet::operator*=(const pair<int,int>& p) {
        update(p.first, p.second);
        return *this;
    }
    void OrderedSet::remove(int value) {
        bool removed = false;
        pImpl->root = pImpl->deleteNode(pImpl->root, value, removed);
        if (!removed){
            throw out_of_range("remove(): value " + to_string(value) + " not found in set");
        }
        --pImpl->nodeCount;
    }
    OrderedSet &OrderedSet::operator-=(int value) {
        remove(value);
        return *this;
    } 
    OrderedSet& OrderedSet::operator!() {
        pImpl->clear();
        return *this;
    }
    bool OrderedSet::operator==(const OrderedSet &other) const {
        if (pImpl->nodeCount != other.pImpl->nodeCount) return false;
        vector<int> a, b;
        Impl::inorder(pImpl->root, a);
        Impl::inorder(other.pImpl->root, b);
        return a == b;
    }
    bool OrderedSet::operator!=(const OrderedSet &other) const {
        return !(*this == other);
    }
    bool OrderedSet::operator<(const OrderedSet &other) const {
        if (*this == other) return false;
        vector<int> elements;
        Impl::inorder(pImpl->root, elements);
        for (int v : elements){
            if (!other.contains(v)) return false;
        }
        return true;
    }
    bool OrderedSet::operator<=(const OrderedSet &other) const {
        return (*this < other) || (*this == other);
    }
    bool OrderedSet::operator>(const OrderedSet& other) const {
        return other < *this;
    }
    bool OrderedSet::operator>=(const OrderedSet& other) const {
        return (*this > other) || (*this == other);
    }
    int OrderedSet::height() const {
        return Impl::nodeHeight(pImpl->root);
    }
 
}
