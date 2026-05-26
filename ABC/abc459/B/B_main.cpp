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
    ll n;
    cin>>n;
    string s;
    rep(i,n){
        cin>>s;
        
        switch (s.at(0))
        {
        case 'a':
        case 'b':
        case 'c':
            cout<<2;
            break;
        case 'd':
        case 'e':
        case 'f':
            cout<<3;
            break;
        case 'g':
        case 'h':
        case 'i':
            cout<<4;
            break;
        case 'j':
        case 'k':
        case 'l':
            cout<<5;
            break;
        case 'm':
        case 'n':
        case 'o':
            cout<<6;
            break;
        case 'p':
        case 'q':
        case 'r':
        case 's':
            cout<<7;
            break;
        case 't':
        case 'u':
        case 'v':
            cout<<8;
            break;
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            cout<<9;
            break;
        
        default:
            break;
        }

    }
    cout<<endl;
    
}