#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;  
typedef pair<int,int> ii;  
typedef vector<ii> vii;  
typedef list<int> li;  
typedef map<int,int> mii;
  
#define rep(i,n) for (int i = 0; i < (n); i++)  
#define rrep(i,n) for (int i = (n)-1; i >= 0; i--)
#define rap(i,a,n) for (int i = a; i < (n); i++) 
#define rrap(i,n,a) for (int i = (n)-1; i >= a; i--) 

#define RED		1
#define BLACK	2

class AugRBBST {

    struct node {
        int data;
        int color;
        int size;
        struct node *left, *right, *parent;
    };

    node *root; //tree with n nodes
    node null;
    struct node *nullp = &null;

    //removes the tree from memory
    //input: root of tree
    //O(n) complexity
    void deleteTree(node* t) {
        if (t == NULL) return;
        deleteTree(t -> left);
        deleteTree(t -> right);
        delete t;
    }

    //prints the elements of the tree in-order.
    //input: root of tree
    //O(n) complexity
    void inorder(node *t) {
        if (t == nullp) return;
        inorder(t -> left);
        cout << (t -> data) << " ";
        inorder(t -> right);
    }

    //returns NULL if not found, or the node that contains the key if found
    //input: root of tree
    //O(logn) complexity
    node* search(node *t, int x) {
        if (t == nullp || t -> data == x) return t;
        if (x < t -> data) return search(t -> left, x);
        return search(t -> right, x);
    }

    //returns the node containing the minimum element. can be solved with kthsmallest
    //input: root of tree
    //O(logn) complexity
    node* minimum(node *t) {
        while (t -> left != nullp) t = t -> left;
        return t;
    }

    //returns the node containing the maximum element. can be solved with kthsmallest
    //input: root of tree
    //O(logn) complexity
    node* maximum(node *t) {
        while (t -> right != nullp) t = t -> right;
        return t;
    }

    //returns the node containing the next smallest element in the tree
    //input: node containing an element
    //O(logn) complexity
    node* nextsmallest(node *t) {
        if (t -> right != nullp) return nextsmallest(t -> right);
        node* y = t -> parent;
        while (y != nullp && t == y -> right) {
            t = y;
            y = y -> parent;
        }
        return y;
    }

    //helper function for insertion and deletion
    void leftrotation(node *x) {
        node *y = x -> right;
        x -> right = y -> left;
        if (y -> left != nullp) y -> left -> parent = x;
        y -> parent = x -> parent;
        if (x -> parent == nullp) root = y;
        else if (x == x -> parent -> left) x -> parent -> left = y;
        else x -> parent -> right = y;
        y -> left = x;
        x -> parent = y;
        y -> size = x -> size;
        x -> size = x -> left -> size + x -> right -> size + 1;
    }

    //helper function for insertion and deletion
    void rightrotation(node *x) {
        node *y = x -> left;
        x -> left = y -> right;
        if (y -> right != nullp) y -> right -> parent = x;
        y -> parent = x -> parent;
        if (x -> parent == nullp) root = y;
        else if (x == x -> parent -> right) x -> parent -> right = y;
        else x -> parent -> left = y;
        y -> right = x;
        x -> parent = y;
        y -> size = x -> size;
        x -> size = x -> left -> size + x -> right -> size + 1;
    }

    //helper function for insertion
    void insertfix(node *z) {
        node *y;
        while (z -> parent -> color == RED) {
            if (z -> parent == z -> parent -> parent -> left) {
                y = z -> parent -> parent -> right;
                if (y -> color == RED) {
                    z -> parent -> color = BLACK;
                    y -> color = BLACK;
                    z -> parent -> parent -> color = RED;
                    z = z -> parent -> parent;
                }
                else {
                    if (z == z -> parent -> right) {
                        z = z -> parent;
                        leftrotation(z);
                    }
                    z -> parent -> color = BLACK;
                    z -> parent -> parent -> color = RED;
                    rightrotation(z -> parent -> parent);
                }
            }
            else {
                y = z -> parent -> parent -> left;
                if (y -> color == RED) {
                    z -> parent -> color = BLACK;
                    y -> color = BLACK;
                    z -> parent -> parent -> color = RED;
                    z = z -> parent -> parent;
                }
                else {
                    if (z == z -> parent -> left) {
                        z = z -> parent;
                        rightrotation(z);
                    }
                    z -> parent -> color = BLACK;
                    z -> parent -> parent -> color = RED;
                    leftrotation(z -> parent -> parent);
                }
            }
        }
        root -> color = BLACK;
    }

    //inserts a node in the tree. size is modified accordingly
    //input: the element to be inserted
    //O(logn) complexity
    void insertion(int k) {
        node *x = root, *y = nullp, *z = (node*)malloc(sizeof(struct node));
        z -> data = k;
        z -> size = 1;
        while (x != nullp) {
            x -> size += 1;
            y = x;
            if (z -> data < x -> data) x = x -> left;
            else if (z -> data > x -> data) x = x -> right;
            else {
                node *tm = x;
                while (tm != root) {
                    tm -> size --;
                    tm = tm -> parent;
                }
                tm -> size --;
                free(z);
                return;
            }
        }
        z -> parent = y;
        if (y == nullp) root = z;
        else if (z -> data < y -> data) y -> left = z;
        else y -> right = z;
        z -> left = nullp;
        z -> right = nullp;
        z -> color = RED;
        insertfix(z);
    }

    //helper function for deletion
    void transplant(node *u, node *v) {
        if (u -> parent == nullp) root = v;
        else if (u == u -> parent -> left) u -> parent -> left = v;
        else u -> parent -> right = v;
        v -> parent = u -> parent;
    }

    //helper function for deletion
    void deletionfix(node *x) {
        node *w;
        while (x != root && x -> color == BLACK) {
            if (x == x -> parent -> left) {
                w = x -> parent -> right;
                if (w -> color == RED) {
                    w -> color = BLACK;
                    x -> parent -> color = RED;
                    leftrotation(x -> parent);
                    w = x -> parent -> right;
                }
                if (w -> left -> color == BLACK && w -> right -> color == BLACK) {
                    w -> color = RED;
                    x = x -> parent;
                }
                else {
                    if (w -> right -> color == BLACK) {
                        w -> left -> color = BLACK;
                        w -> color = RED;
                        rightrotation(w);
                        w = x -> parent -> right;
                    }
                    w -> color = x -> parent -> color;
                    x -> parent -> color = BLACK;
                    w -> right -> color = BLACK;
                    leftrotation(x -> parent);
                    x = root;
                }
            }
            else {
                w = x -> parent -> left;
                if (w -> color == RED) {
                    w -> color = BLACK;
                    x -> parent -> color = RED;
                    rightrotation(x -> parent);
                    w = x -> parent -> left;
                }
                if (w -> right -> color == BLACK && w -> left -> color == BLACK) {
                    w -> color = RED;
                    x = x -> parent;
                }
                else {
                    if (w -> left -> color == BLACK) {
                        w -> right -> color = BLACK;
                        w -> color = RED;
                        leftrotation(w);
                        w = x -> parent -> left;
                    }
                    w -> color = x -> parent -> color;
                    x -> parent -> color = BLACK;
                    w -> left -> color = BLACK;
                    rightrotation(x -> parent);
                    x = root;
                }
            }
            x -> color = BLACK;
        }
    }

    //deletes a node from the tree and rearranges the tree
    //input: the node to be deleted
    //O(logn) complexity
    void deletion(node *z) {
        node *y = z, *x, *tm;
        if (z == NULL) return;
        if (z != root) {
            tm = z -> parent;
            while (tm != root) {
                tm -> size --;
                tm = tm -> parent;
            }
            root -> size --;
        }
        int initcolor = y -> color;
        if (z -> left == nullp) {
            x = z -> right;
            transplant(z, z -> right);
        }
        else if (z -> right == nullp) {
            x = z -> left;
            transplant(z, z -> left);
        }
        else {
            y = minimum(z -> right);
            initcolor = y -> color;
            x = y -> right;
            if (y -> parent == z) x -> parent = y;
            else {
                transplant(y, y -> right);
                y -> right = z -> right;
                y -> right -> parent = y;
                tm = x -> parent;
			    while (tm != y) {
				    tm -> size --;
				    tm = tm -> parent;
			    }
			    y -> size = y -> left -> size + 1;
            }
            transplant(z, y);
            y -> left = z -> left;
            y -> left -> parent = y;
            y -> color = z -> color;
            y -> size = y -> left -> size + y -> right -> size + 1;
        }
        if (initcolor == BLACK) deletionfix(x);
    }

    //returns the node including the k-th smallest element in the tree.
    //input: the number i
    //O(logn) complexity
    node* kthsmallest(node *t, int k) {
        if (k > t -> size || k <= 0) return nullp;
        int r = t -> left -> size + 1;
        if (k == r) return t;
        else if (k < r) return kthsmallest(t -> left, k);
        else return kthsmallest(t -> right, k - r);
    }

    //returns the rank of the given node, in the increasing order of the elements of the tree.
    //input: the given node
    //O(logn) complexity
    int ranki(node *t) {
        if (t == nullp) return -1;
        int r = t -> left -> size + 1;
        node *y = t;
        while (y != root) {
            if (y == y -> parent -> right) r = r + y -> parent -> left -> size + 1;
            y = y -> parent;
        }
        return r;
    }

public:
    AugRBBST() {
        null.left = null.right = null.parent = nullp;
        null.color = BLACK;
        null.size = 0;
        root = nullp;
    }

    bool exists(int x) {
        node *X = search(root, x);
        if (X == nullp) return false;
        return true;
    }

    int minno() {
        return minimum(root) -> data;
    }

    int maxno() {
        return maximum(root) -> data;
    }

    void insert(int x) {
        insertion(x);
    }

    bool remove(int x) {
        node* X = search(root, x);
        if (X == NULL || X == nullp) return false;
        deletion(X);
        return true;
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    int kth(int k) {
        node* X = kthsmallest(root, k);
        if (X == nullp) return -1;
        return kthsmallest(root, k) -> data;
    }

    int rank(int k) {
        node *x = search(root, k);
        return ranki(x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    AugRBBST t;
    t.insert(10);
    t.insert(12);
    t.insert(11);
    t.insert(20);
    t.insert(16);
    t.display();
    cout << t.kth(4) << endl;
    cout << t.kth(5) << endl;
    cout << t.remove(15) << endl;
    cout << t.kth(5) << endl;
    t.remove(11);
    cout << t.rank(8) << endl;
    cout << t.rank(10) << endl;
    cout << t.rank(20) << endl;
    t.display();
    cout << t.kth(5) << endl;
    cout << t.kth(4) << endl;
    return 0;

    //compile: g++ -std=c++14 -O2 -Wall NAME.cpp -o NAME
}