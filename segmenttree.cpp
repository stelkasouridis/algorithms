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

class segtree {
    struct segment_tree {
        segment_tree *left, *right;
        int from, to, value;
        segment_tree(int from1, int to1) {
            from = from1;
            to = to1;
            left = NULL;
            right = NULL;
            value = 0;
        }
    };

    segment_tree *root;

    segment_tree* build(const vector<int> &arr, int l, int r) {
        if (l > r) return NULL;
        segment_tree *res = new segment_tree(l, r);
        if (l == r) {
            res->value = arr[l];
        } else {
            int m = (l + r) / 2;
            res->left = build(arr, l, m);
            res->right = build(arr, m + 1, r);
            if (res->left != NULL) res->value += res->left->value;
            if (res->right != NULL) res->value += res->right->value;
        }
        return res;
    }

    int sumquery(segment_tree *tree, int l, int r) {
        if (tree == NULL) return 0;
        if (l <= tree->from && tree->to <= r) return tree->value;
        if (tree->to < l) return 0;
        if (r < tree->from) return 0;
        return sumquery(tree->left, l, r) + sumquery(tree->right, l, r);
    }

    int update(segment_tree *tree, int pos, int val) {
        if (tree == NULL) return 0;
        if (tree->to < pos) return tree->value;
        if (pos < tree->from) return tree->value;
        if (tree->from == tree->to && tree->from == pos) {
             tree->value = val;
        } else {
            tree->value = update(tree->left, pos, val) + update(tree->right, pos, val);
        }
        return tree->value;
    }

    public:
    
    //build the segment tree (IF LENGTH IS N, L MUST BE 0 AND R MUST BE N-1)
    //O(n) complexity
    void segbuild(vector<int> &arr, int l, int r) {
        root = build(arr, l, r);
    }

    //position pos is updated with value val
    //O(logn) complexity
    //value of root is returned
    int segupdate(int pos, int val) {
        return update(root, pos, val);
    }

    //a sum query on a range [l,r] inclusive is made
    //O(logn) complexity
    //can be modified to hold min/max/gcd/lcm/... queries
    int segquery(int l, int r) {
        return sumquery(root,l,r);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    segtree t;
    vi v;
    v.assign(13,3);
    t.segbuild(v,0,12); //segment tree includes 13 times the number 3
    cout << t.segquery(0,12) << endl; //39
    t.segupdate(12,4);
    v[12] = 4; //it's better to update it in both the vector and the tree, but not necessary
    t.segupdate(0,7);
    t.segupdate(3,5);
    cout << t.segquery(0,12) << endl; //46
    cout << t.segquery(1,11) << endl; //35
    t.segupdate(3,12);
    cout << t.segquery(0,11) << endl; //49
    return 0;

    //compile: g++ -std=c++14 -O2 -Wall NAME.cpp -o NAME
}