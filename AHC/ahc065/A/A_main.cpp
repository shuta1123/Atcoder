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

ll n;
map<ll,VL> m;
VVL v;
vector<vector<pair<ll,ll>>> belts;

// ベルト belt_idx を方向 dir に1ステップ動かし、v と m を更新する
void ch(ll belt_idx, ll dir) {
    auto& belt = belts[belt_idx];
    ll l = belt.size();
    VL vals(l);
    for (ll x = 0; x < l; x++) {
        vals[x] = v[belt[x].first][belt[x].second];
    }
    for (ll x = 0; x < l; x++) {
        ll new_x = ((x + dir) % l + l) % l;
        ll val = vals[x];
        v[belt[new_x].first][belt[new_x].second] = val;
        if (val >= 0) m[val] = {belt[new_x].first, belt[new_x].second};
    }
}

int main() {
    ll t;
    cin >> n;
    v.assign(n, VL(n));
    rep(i,n){
        rep(j,n){
            cin >> t;
            m[t] = {i, j};
            v[i][j] = t;
        }
    }

    // ベルト定義を出力しながら belts に保存
    cout << n/2+1 << "\n";

    // Belt 0: 行0と行1の水平ループ
    {
        vector<pair<ll,ll>> belt0;
        rep(i,n) belt0.push_back({0, i});
        repr(i,n) belt0.push_back({1, i});
        belts.push_back(belt0);
    }
    cout << 2*n << ' ';
    rep(i,n) cout << 0 << ' ' << i << ' ';
    repr(i,n) cout << 1 << ' ' << i << ' ';
    cout << "\n";

    // Belt k+1: 列ペア k の垂直ループ
    rep(i,n/2){
        vector<pair<ll,ll>> belt;
        rep(j,n) belt.push_back({j, i*2});
        repr(j,n) belt.push_back({j, i*2+1});
        belts.push_back(belt);

        cout << 2*n << ' ';
        rep(j,n) cout << j << ' ' << i*2 << ' ';
        repr(j,n) cout << j << ' ' << i*2+1 << ' ';
        cout << "\n";
    }

    // 操作列を収集（T が先に必要なのでバッファリング）
    vector<pair<ll,ll>> ops;
    ll n2 = n*n;

    ll a = 0;
    // 初期状態で出口にある箱を取り出す
    while (a < n2 && v[0][n/2] == a) {
        v[0][n/2] = -1;
        m.erase(a);
        a++;
    }

    while (a < n2) {
        ll ni = m[a][0];
        ll nj = m[a][1];
        if (ni < 1) {
            if (nj < n/2) {
                ops.push_back({0, 1});
                ch(0, 1);   // 1箇所目
            } else {
                ops.push_back({0, -1});
                
                ch(0, -1);  // 2箇所目
            }
        } else {
            ll bv = nj/2+1;  // 列ペア nj/2 の垂直ベルト番号
            if (nj%2 == 0) {
                ops.push_back({bv, -1});
                ch(bv, -1); // 3箇所目
            } else {
                ops.push_back({bv, 1});
                ch(bv, 1);  // 4箇所目
            }
        }
        // 出口の箱を取り出す
        while (a < n2 && v[0][n/2] == a) {
            v[0][n/2] = -1;
            m.erase(a);
            a++;
        }
    }

    cout << ops.size() << "\n";
    for (auto& [mi, di] : ops) cout << mi << ' ' << di << "\n";
}
