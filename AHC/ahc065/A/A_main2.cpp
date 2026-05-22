#include <bits/stdc++.h>
using namespace std;

// Belt layout  (total 20 belts)
//   0      : central vertical  cols 10-11  (0,10)→...→(19,10)→(19,11)→...→(0,11)
//   1-10   : horizontal        row pairs   (2k,0)→...→(2k,19)→(2k+1,19)→...→(2k+1,0)
//   11-15  : vertical          col pairs   0-1, 2-3, 4-5, 6-7, 8-9
//   16-19  : vertical          col pairs   12-13, 14-15, 16-17, 18-19

const int N   = 20;
const int M   = 20;
const int EXR = 0;
const int EXC = N / 2;   // exit = (0, 10)
const int SEN = N * N;   // sentinel: empty cell

int g[N][N];
pair<int,int> pos[SEN];
vector<pair<int,int>> belt[M];

void build_belts() {
    // Belt 0: central vertical (cols 10, 11)
    for (int i = 0; i < N; i++)     belt[0].push_back({i, 10});
    for (int i = N-1; i >= 0; i--) belt[0].push_back({i, 11});

    // Belts 1-10: horizontal row pairs
    for (int k = 0; k < N/2; k++) {
        for (int j = 0; j < N; j++)     belt[1+k].push_back({2*k,   j});
        for (int j = N-1; j >= 0; j--) belt[1+k].push_back({2*k+1, j});
    }

    // Belts 11-15: col pairs (0-1)..(8-9)
    for (int c = 0; c < 5; c++) {
        for (int i = 0; i < N; i++)     belt[11+c].push_back({i, 2*c});
        for (int i = N-1; i >= 0; i--) belt[11+c].push_back({i, 2*c+1});
    }

    // Belts 16-19: col pairs (12-13)..(18-19)  [c=6..9]
    for (int c = 6; c < 10; c++) {
        for (int i = 0; i < N; i++)     belt[10+c].push_back({i, 2*c});
        for (int i = N-1; i >= 0; i--) belt[10+c].push_back({i, 2*c+1});
    }
}

// Vertical belt for column c
// pair<5 → 11+pair, pair==5 → 0 (central), pair>5 → 10+pair
int vert_belt(int c) {
    int p = c / 2;
    if (p < 5)  return 11 + p;
    if (p == 5) return 0;
    return 10 + p;   // p=6→16, 7→17, 8→18, 9→19
}

// Horizontal belt for row r: row pair k → belt 1+k
int horiz_belt(int r) { return 1 + r / 2; }

void do_shift(int b, int d) {
    int l = (int)belt[b].size();
    int tmp[40];
    for (int x = 0; x < l; x++) tmp[x] = g[belt[b][x].first][belt[b][x].second];
    for (int x = 0; x < l; x++) {
        int nx = ((x + d) % l + l) % l;
        auto [r, c] = belt[b][nx];
        g[r][c] = tmp[x];
        if (tmp[x] < SEN) pos[tmp[x]] = {r, c};
    }
}

int dist_to_exit(int box) {
    auto [r, c] = pos[box];
    return r + abs(c - EXC);
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
    cout << M << '\n';
    for (int b = 0; b < M; b++) {
        cout << (int)belt[b].size();
        for (auto [r, c] : belt[b]) cout << ' ' << r << ' ' << c;
        cout << '\n';
    }

    // --- Simulation ---
    vector<pair<int,int>> ops;
    int a = 0;  // next box to remove

    auto try_remove = [&]() {
        while (a < SEN && g[EXR][EXC] == a) {
            g[EXR][EXC] = SEN;
            pos[a] = {-1, -1};
            a++;
        }
    };

    try_remove();

    // K-box lookahead greedy.
    // W[0] >> sum(W[1..K-1]) guarantees box a always makes progress
    // (at least +1 distance reduction per turn).
    const int K = 5;
    const long long W[K] = {1000000LL, 1000LL, 10LL, 1LL, 0LL};

    while (a < SEN && (int)ops.size() < 100000) {
        // Candidates: vert + horiz belts of next K target boxes
        vector<pair<int,int>> cands;
        for (int k = 0; k < K && a + k < SEN; k++) {
            auto [r, c] = pos[a + k];
            if (r < 0) break;
            cands.push_back({vert_belt(c),  -1});
            cands.push_back({vert_belt(c),  +1});
            cands.push_back({horiz_belt(r), -1});
            cands.push_back({horiz_belt(r), +1});
        }
        sort(cands.begin(), cands.end());
        cands.erase(unique(cands.begin(), cands.end()), cands.end());

        // Snapshot distances before any trial shift
        long long before[K] = {};
        for (int k = 0; k < K && a + k < SEN; k++)
            if (pos[a + k].first >= 0) before[k] = dist_to_exit(a + k);

        int best_b = -1, best_d = 0;
        long long best_sc = LLONG_MIN;

        for (auto [b, d] : cands) {
            do_shift(b, d);

            // Huge bonus if box a reaches exit
            long long sc = (g[EXR][EXC] == a) ? (long long)2e12 : 0LL;
            for (int k = 0; k < K && a + k < SEN; k++)
                if (pos[a + k].first >= 0)
                    sc += W[k] * (before[k] - dist_to_exit(a + k));

            do_shift(b, -d);  // undo trial

            if (sc > best_sc) { best_sc = sc; best_b = b; best_d = d; }
        }

        if (best_b < 0) break;
        do_shift(best_b, best_d);
        ops.push_back({best_b, best_d});
        try_remove();
    }

    // --- Output operations ---
    cout << (int)ops.size() << '\n';
    for (auto [b, d] : ops) cout << b << ' ' << d << '\n';

    return 0;
}
