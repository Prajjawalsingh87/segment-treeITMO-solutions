#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Assignment to Segment (ITMO Segment Tree part 2, step 1, C)
 * Description:
 * Range assignment a[l..r-1] = v, point query a[i].
 * Lazy propagation with -1 meaning "no pending assignment".
 */

typedef long long ll;

class segmenttree{
public:
  vector<ll>tree;
  vector<ll>lazy;
  ll n;
  segmenttree(ll size){
    n=size;
    tree.resize(4*n);
    lazy.resize(4*n,-1);
  }
  void push(ll l,ll r,ll idx){
    if(lazy[idx]==-1) return ;
    if(l!=r){
        tree[2*idx]=tree[idx];
        tree[2*idx+1]=tree[idx];
        lazy[2*idx]=lazy[idx];
        lazy[2*idx+1]=lazy[idx];
    }
    lazy[idx]=-1;
  }
  void build(vector<ll>&arr,ll l,ll r,ll idx){
    if(l==r){
        tree[idx]=arr[l];
        return;
    }
    ll mid=(l+r)/2;
    build(arr,l,mid,2*idx);
    build(arr,mid+1,r,2*idx+1);
  }
  void update(ll idx,ll l,ll r,ll lq,ll rq,ll val){
    push(l,r,idx);
    if(r<lq || l>rq) return ;
    if(l>=lq && r<=rq){
        tree[idx]=val;
        lazy[idx]=val;
        return ;
    }
    ll mid=(l+r)/2;
    update(2*idx,l,mid,lq,rq,val);
    update(2*idx+1,mid+1,r,lq,rq,val);
  }
  ll query(ll idx,ll l,ll r,ll pos){
    push(l,r,idx);
    if(pos<l || pos>r) return 0;
    if(l==r) return tree[idx];
    ll mid=(l+r)/2;
    if(pos<=mid) return query(2*idx,l,mid,pos);
    else return query(2*idx+1,mid+1,r,pos);
  }
  void build(vector<ll>&arr){
     build(arr,0,n-1,1);
  }
  void update(ll lq,ll rq,ll val){
    update(1,0,n-1,lq,rq,val);
  }
  ll query(ll pos){
    return query(1,0,n-1,pos);
  }
};
int main()
{
    ll n,q;
    cin>>n>>q;
    vector<ll>arr(n,0);
    segmenttree sg(n);
    sg.build(arr);
    while(q--){
      ll pos;
      cin>>pos;
      if(pos==1){
        ll lq,rq,val;
        cin>>lq>>rq>>val;
        sg.update(lq,rq-1,val);
      }
      else{
        ll pos;
        cin>>pos;
        cout<<sg.query(pos)<<endl;
      }
    }

    return 0;
}