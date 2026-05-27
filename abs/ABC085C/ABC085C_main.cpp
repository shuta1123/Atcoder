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

const string YN[2] = {"Yes", "No"};

int main() {
    ll n,x;
    cin>>n>>x;
    x/=1000;
    if(x>n*10){
        cout<<-1<<' '<<-1<<' '<<-1<<endl;
        return 0;
    } 
    ll f=0;
    rep(i,n+1){
        rep(j,n-i+1){
            
                
            if(i*10+j*5+n-i-j==x){
                cout<<i<<' '<<j<<' '<<n-i-j<<endl;
                f=1;
                
            }
            
        }
        if(f==1||i*10>x){
            break;
        }
    }
    if(f==0){
        cout<<-1<<' '<<-1<<' '<<-1<<endl;
    }
}