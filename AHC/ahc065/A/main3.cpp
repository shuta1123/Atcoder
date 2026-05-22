#include <bits/stdc++.h>
using namespace std;

const int N     = 20;
const int MB    = N/2 + 1;  // 11個のベルト
const int HALF  = N/2;
const int EMPTY = N*N;

int g[N][N];
pair<int,int> pos[EMPTY + 1];
bool gone[EMPTY];
vector<pair<int,int>> belt[MB];

void build_belts() {
    // Belt 0: 行0-1水平ループ (40マス)
    for (int j = 0; j < N; j++) belt[0].push_back({0, j});
    for (int j = N-1; j >= 0; j--) belt[0].push_back({1, j});
    
    // Belts 1-10: 列対垂直ループ (各40マス)
    for (int k = 0; k < N/2; k++) {
        for (int r = 0; r < N; r++)     belt[k+1].push_back({r, 2*k});
        for (int r = N-1; r >= 0; r--) belt[k+1].push_back({r, 2*k+1});
    }
}

void shift(int b, int d) {
    int l = belt[b].size();
    int tmp[2*N];
    for (int x = 0; x < l; x++) 
        tmp[x] = g[belt[b][x].first][belt[b][x].second];
    for (int x = 0; x < l; x++) {
        int nx = ((x + d) % l + l) % l;
        auto [r, c] = belt[b][nx];
        g[r][c] = tmp[x];
        if (tmp[x] != EMPTY) pos[tmp[x]] = {r, c};
    }
}

int dist(int box) {
    if (gone[box]) return 0;
    auto [r, c] = pos[box];
    return r + abs(c - HALF);
}

pair<int,int> next_op(int box) {
    if (gone[box]) return {-1, 0};
    auto [r, c] = pos[box];
    if (r > 0) return {c/2 + 1, c%2 == 0 ? -1 : 1};
    if (c != HALF) return {0, c < HALF ? 1 : -1};
    return {-1, 0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nn; cin >> nn;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            cin >> g[i][j];
            pos[g[i][j]] = {i, j};
        }

    build_belts();

    // ベルト定義出力
    cout << MB << '\n';
    for (int b = 0; b < MB; b++) {
        cout << (int)belt[b].size();
        for (auto [r, c] : belt[b]) cout << ' ' << r << ' ' << c;
        cout << '\n';
    }

    vector<pair<int,int>> ops;
    int n2 = EMPTY, a = 0;

    auto try_remove = [&]() {
        while (a < n2 && g[0][HALF] == a) {
            gone[a] = true;
            g[0][HALF] = EMPTY;
            a++;
        }
    };
    try_remove();

    const int K    = 5;
    const int W[K] = {2000, 200, 20, 5, 1};

    while (a < n2 && (int)ops.size() < 100000) {  // T ≤ 100,000
        auto [ba, da] = next_op(a);
        if (ba < 0) break;

        // 候補ベルト列挙 (0 ≤ m_t < M)
        vector<pair<int,int>> cands = {{ba, da}};
        for (int k = 1; k < K; k++) {
            if (a + k < n2 && !gone[a + k]) {
                auto [bk, dk] = next_op(a + k);
                if (bk >= 0) cands.push_back({bk, dk});
            }
        }
        sort(cands.begin(), cands.end());
        cands.erase(unique(cands.begin(), cands.end()), cands.end());

        int best_b = ba, best_d = da, best_sc = INT_MIN;
        for (auto [b, d] : cands) {
            if (b < 0 || b >= MB) continue;  // 0 ≤ m_t < M
            if (d != -1 && d != 1) continue;  // d_t ∈ {-1, 1}
            
            int before[K], after[K];
            for (int k = 0; k < K; k++)
                before[k] = (a+k < n2 && !gone[a+k]) ? dist(a+k) : 0;

            shift(b, d);
            bool at_exit = (!gone[a] && g[0][HALF] == a);
            for (int k = 0; k < K; k++)
                after[k] = (a+k < n2 && !gone[a+k]) ? dist(a+k) : 0;
            shift(b, -d);

            int sc = (at_exit ? 500000 : 0);
            for (int k = 0; k < K; k++) 
                sc += W[k] * (before[k] - after[k]);

            if (sc > best_sc) {
                best_sc = sc;
                best_b  = b;
                best_d  = d;
            }
        }

        shift(best_b, best_d);
        ops.push_back({best_b, best_d});
        try_remove();
    }

    cout << (int)ops.size() << '\n';
    for (auto [b, d] : ops) cout << b << ' ' << d << '\n';
    return 0;
}