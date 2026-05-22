#line 1 "C_main.cpp"
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using VL  = vector<ll>;
using VVL = vector<VL>;
using VC  = vector<char>;
using VVC = vector<VC>;


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
    int h,w,s1,s2;
    cin>>h>>w>>s1>>s2;
    s1--;
    s2--;
    VVC hu(h,VC(w));
    int s;
    rep(i,h){
        rep(j,w){
            cin>>hu.at(i).at(j);
        }
    }
    s=getchar();
    s=getchar();
    while(s!=EOF){
        switch (s)
        {
        case 'L':
            
            if(s2-1>=0&&hu.at(s1).at(s2-1)=='.'){
                s2--;
            }
            break;
        case 'R':
            if(s2+1<w&&hu.at(s1).at(s2+1)=='.'){
                s2++;
            }
            break;
        case 'U':
            if(s1-1>=0&&hu.at(s1-1).at(s2)=='.'){
                s1--;
            }
            break;
        case 'D':
            if(s1+1<h&&hu.at(s1+1).at(s2)=='.'){
                s1++;
            }
            break;
        
        default:
            break;
        }
        s=getchar();
    }
    cout<<s1+1<<' '<<s2+1<<endl;

}
