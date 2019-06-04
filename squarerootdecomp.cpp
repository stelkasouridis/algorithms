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

vi v; //vector of elements
vi sums; //vector of bucket sums

int k; //floor of sqrt(n)

//initialization of the square root decomposition sum array.
//the vector of elements MUST be already filled.
void sqrtd_init(int n) {
    k = (int)sqrt(n);
    sums.assign(k,0);
    rep(i,(int)sums.size() - 1) {
        rap(j, (i*n)/k, (i+1)*n/k) sums[i] += v[j];
    }
    rap(j, ((k-1)*n)/k, (int)v.size()) sums[k-1] += v[j];
}

//update the j-th (starting from 0) element in v to value val.
//complexity: O(1)
void sqrtd_update(int j, int val) {
    int i = j/k;
    if (i >= k) i = k-1; //fixing bucket of element j, in the only case it can be wrong
    sums[i] -= v[j];
    v[j] = val;
    sums[i] += v[j];
}

//query the sum from j1 to j2 closed (starting from 0).
//complexity: O(sqrt(n))
int sqrtd_query(int j1, int j2) {
    if (j1 > j2 || j1 < 0 || j2 >= (int)v.size()) return -42424242;
    else if (j1 == j2) return v[j1];
    int s = 0;
    int i1 = j1/k;
    int i2 = j2/k;
    if (i1 >= k) i1 = k-1; //fixing bucket of element j1, in the only case it can be wrong
    if (i2 >= k) i2 = k-1; //fixing bucket of element j2, in the only case it can be wrong
    if (i1 == i2) {
        rap(j, j1, j2+1) s += v[j];
        return s;
    }
    rap(j, j1, k*(i1+1)) s += v[j]; //first bucket, from j1 onward
    rap(j, k*i2, j2 + 1) s += v[j]; //last bucket, until j2
    rap(i, i1+1, i2) s += sums[i]; //in between buckets, all elements of them
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    v.resize(N);
    rep(n,N) {
        cin >> v[n];
    }
    sqrtd_init(N);
    rep(i,(int)v.size()) {
        cout << v[i] << " ";
    }
    cout << endl;
    rep(i,(int)sums.size()) {
        cout << sums[i] << " ";
    }
    cout << endl;
    sqrtd_update(4,8);
    rep(i,(int)sums.size()) {
        cout << sums[i] << " ";
    }
    cout << sqrtd_query(1,9) << endl; //44
    cout << sqrtd_query(8,3) << endl; //-42424242
    cout << sqrtd_query(5,5) << endl; //5
    cout << sqrtd_query(0,1) << endl; //7
    cout << sqrtd_query(9,10) << endl; //-42424242
    cout << sqrtd_query(8,9) << endl; //4
    cout << sqrtd_query(9,9) << endl; //2
    cout << sqrtd_query(4,5) << endl; //13
    cout << sqrtd_query(2,7) << endl; //34
    cout << sqrtd_query(2,3) << endl; //11
    cout << sqrtd_query(5,6) << endl; //11
    return 0;
    //compile: g++ -std=c++14 -O2 -Wall NAME.cpp -o NAME
}