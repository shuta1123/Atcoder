#include <bits/stdc++.h>
using namespace std;

const int N     = 20;
const int MB    = N/2 + 1;  // belts: 1 horizontal + 10 vertical = 11
const int HALF  = N/2;      // exit column = 10
const int EMPTY = N*N;      // sentinel value for empty cell

int g[N][N];
pair<int,int> pos[EMPTY + 1];  // pos[box] = (row, col)
bool gone[EMPTY];              // gone[box] = already removed
vector<pair<int,int>> belt[MB];

void build_belts() {
    // Belt 0: rows 0,1 horizontal loop
    for (int j = 0; j < N; j++) belt[0].push_back({0, j});
    for (int j = N-1; j >= 0; j--) belt[0].push_back({1, j});
    // Belts 1..N/2: column-pair vertical loops
    for (int k = 0; k < N/2; k++) {
        for (int r = 0; r < N; r++)     belt[k+1].push_back({r, 2*k});
        for (int r = N-1; r >= 0; r--) belt[k+1].push_back({r, 2*k+1});
    }
}

void shift(int b, int d) {
    int l = belt[b].size();
    int tmp[2*N];
    for (int x = 0; x < l; x++) tmp[x] = g[belt[b][x].first][belt[b][x].second];
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

    // --- Output belt definitions ---
    cout << MB << '\n';
    for (int b = 0; b < MB; b++) {
        cout << (int)belt[b].size();
        for (auto [r, c] : belt[b]) cout << ' ' << r << ' ' << c;
        cout << '\n';
    }

    // --- Collect operations ---
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

    // 2-step lookahead: for each of 22 first ops, find the best follow-up
    // among all 22 second ops (plus no-op baseline).
    // Score = exit bonuses + sum W[k] * (before[k] - after[k])
    const int K    = 10;
    const int W[K] = {10000, 3000, 1000, 300, 100, 30, 10, 3, 1, 1};

    while (a < n2 && (int)ops.size() < 100000) {
        // Pre-compute distances before any operation this turn
        int before[K];
        for (int k = 0; k < K; k++)
            before[k] = (a+k < n2 && !gone[a+k]) ? dist(a+k) : 0;

        int best_b = 0, best_d = 1, best_sc = INT_MIN;

        for (int b1 = 0; b1 < MB; b1++) {
            for (int d1 : {-1, 1}) {
                shift(b1, d1);
                bool at1 = (!gone[a] && g[0][HALF] == a);

                // Baseline: score after just this one op (2-step inner = at most this)
                auto score_state = [&](bool at_from_step1) -> int {
                    int sc = at_from_step1 ? 2000000 : 0;
                    bool at_now = (!gone[a] && g[0][HALF] == a);
                    if (!at_from_step1 && at_now) sc += 1000000;
                    for (int k = 0; k < K; k++) {
                        int aft = (a+k < n2 && !gone[a+k]) ? dist(a+k) : 0;
                        sc += W[k] * (before[k] - aft);
                    }
                    return sc;
                };

                int inner = score_state(at1); // 1-step baseline (no 2nd op)

                // Try all 22 follow-up ops
                for (int b2 = 0; b2 < MB; b2++) {
                    for (int d2 : {-1, 1}) {
                        shift(b2, d2);
                        int sc = score_state(at1);
                        shift(b2, -d2);
                        if (sc > inner) inner = sc;
                    }
                }

                shift(b1, -d1);
                if (inner > best_sc) {
                    best_sc = inner;
                    best_b  = b1;
                    best_d  = d1;
                }
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
