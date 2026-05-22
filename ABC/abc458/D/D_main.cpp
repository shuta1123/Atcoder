#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using VL  = vector<ll>;
using VVL = vector<VL>;

#define rep(i, n)      for (ll i = 0; i < (ll)(n); i++)
#define rep1(i, n)     for (ll i = 1; i <= (ll)(n); i++)
#define repi(i, a, b)  for (ll i = (ll)(a); i < (ll)(b); i++)
#define repr(i, n)     for (ll i = (ll)(n) - 1; i >= 0; i--)
#define all(x)         (x).begin(), (x).end()
#define rall(x)        (x).rbegin(), (x).rend()
#define sz(x)          ((ll)(x).size())

#ifdef LOCAL
#define dbg(x)   cerr << #x << " = " << (x) << "\n"
#define dbgv(v)  { cerr << #v << " = ["; for (auto& _x : (v)) cerr << _x << ", "; cerr << "]\n"; }
#define dbgvv(v) { cerr << #v << ":\n"; for (auto& _row : (v)) { for (auto& _x : _row) cerr << _x << " "; cerr << "\n"; } }
#else
#define dbg(x)
#define dbgv(v)
#define dbgvv(v)
#endif

const string YN[2] = {"yes", "no"};

int main() {
    ll q,mid,a,b;
    cin>>mid>>q;
    priority_queue<ll> small;
    priority_queue<ll,VL,greater<ll>> big;
    for(int i=0;i<q;i++){
        int mb=0,ms=0,t=0;
        ll tmp;
        cin>>a>>b;
        tmp=a;
        if(tmp>mid){
            mb++;
            big.push(tmp);
        }else if(tmp<mid){
            ms++;
            small.push(tmp);
        }else{
            t++;
        }
        
        tmp=b;
        if(tmp>mid){
            mb++;
            big.push(tmp);
        }else if(tmp<mid){
            ms++;
            small.push(tmp);
        }else{
            t++;
        }
        // cout<<<<endl;
        if(t==2){
            big.push(mid);
            small.push(mid);
        }else if(t==1){
            if(ms==1){
                big.push(mid);
            }else{
                small.push(mid);
            }
        }else  if(ms==2){
            big.push(mid);
            mid=small.top();
            small.pop();
        }else if(mb==2){
            small.push(mid);
            mid=big.top();
            big.pop();
        }
        cout<<mid<<endl;


    }



}