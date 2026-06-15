#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    string s;
    cin >> s;
    vector<string> words = {"dream", "dreamer", "erase", "eraser"};
    ll n = s.size();

    // dp[i] = 先頭 i 文字までを分解できるか
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (ll i = 0; i < n; i++) {
        if (!dp[i]) continue;
        for (const auto& w : words) {
            if (i + (ll)w.size() <= n && s.substr(i, w.size()) == w) {
                dp[i + w.size()] = true;
            }
        }
    }

    cout << (dp[n] ? "YES" : "NO") << endl;
}