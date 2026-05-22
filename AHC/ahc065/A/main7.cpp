#include <bits/stdc++.h>
using namespace std;

const int N = 20;
const int V = N * N;
const int M = 20;
const int EXIT = 10;
const int EMPTY = V;

vector<int> belt[M];
vector<pair<int,int>> occ[V];
int dist_cell[V];
int g[V];
int pos[V];

int id(int r, int c) { return r * N + c; }
pair<int,int> rc(int x) { return {x / N, x % N}; }

void build_belts() {
    for (int i = 0; i < N; i++) belt[0].push_back(id(i, 10));
    for (int i = N - 1; i >= 0; i--) belt[0].push_back(id(i, 11));

    for (int k = 0; k < N / 2; k++) {
        for (int j = 0; j < N; j++) belt[1 + k].push_back(id(2 * k, j));
        for (int j = N - 1; j >= 0; j--) belt[1 + k].push_back(id(2 * k + 1, j));
    }

    for (int c = 0; c < 5; c++) {
        for (int i = 0; i < N; i++) belt[11 + c].push_back(id(i, 2 * c));
        for (int i = N - 1; i >= 0; i--) belt[11 + c].push_back(id(i, 2 * c + 1));
    }

    for (int c = 6; c < 10; c++) {
        for (int i = 0; i < N; i++) belt[10 + c].push_back(id(i, 2 * c));
        for (int i = N - 1; i >= 0; i--) belt[10 + c].push_back(id(i, 2 * c + 1));
    }

    for (int b = 0; b < M; b++) {
        for (int i = 0; i < (int)belt[b].size(); i++) {
            occ[belt[b][i]].push_back({b, i});
        }
    }
}

void build_dist() {
    vector<vector<int>> rev(V);
    for (int b = 0; b < M; b++) {
        int l = (int)belt[b].size();
        for (int i = 0; i < l; i++) {
            int u = belt[b][i];
            int v1 = belt[b][(i + 1) % l];
            int v2 = belt[b][(i - 1 + l) % l];
            rev[v1].push_back(u);
            rev[v2].push_back(u);
        }
    }

    fill(dist_cell, dist_cell + V, 1 << 20);
    queue<int> q;
    dist_cell[EXIT] = 0;
    q.push(EXIT);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : rev[v]) {
            if (dist_cell[u] > dist_cell[v] + 1) {
                dist_cell[u] = dist_cell[v] + 1;
                q.push(u);
            }
        }
    }
}

void do_shift_global(int b, int d) {
    int l = (int)belt[b].size();
    int tmp[40];
    for (int i = 0; i < l; i++) tmp[i] = g[belt[b][i]];
    for (int i = 0; i < l; i++) {
        int ni = (i + d + l) % l;
        int cell = belt[b][ni];
        g[cell] = tmp[i];
        if (tmp[i] < EMPTY) pos[tmp[i]] = cell;
    }
}

const int LOOK = 14;
const int BEAM = 70;
const int PHASE_DEPTH = 7;
const long long W[LOOK] = {
    0, 1200000LL, 450000LL, 160000LL, 60000LL, 22000LL,
    8000LL, 3000LL, 1100LL, 400LL, 150LL, 60LL,
    20LL, 8LL
};

struct State {
    array<short, V> board;
    array<short, LOOK> p;
    vector<pair<short, short>> ops;
    long long score;
    short removed;
};

void shift_state(State& s, int b, int d, int base) {
    int l = (int)belt[b].size();
    int tmp[40];
    for (int i = 0; i < l; i++) tmp[i] = s.board[belt[b][i]];
    for (int i = 0; i < l; i++) {
        int ni = (i + d + l) % l;
        int cell = belt[b][ni];
        int val = tmp[i];
        s.board[cell] = (short)val;
        if (base <= val && val < base + LOOK) s.p[val - base] = (short)cell;
    }
}

long long eval_state(const State& s) {
    long long sc = (long long)s.removed * 1000000000000LL - (long long)s.ops.size() * 100000000LL;
    for (int k = s.removed; k < LOOK; k++) {
        if (s.p[k] >= 0) sc -= W[k] * dist_cell[s.p[k]];
    }
    for (int k = s.removed; k + 1 < LOOK; k++) {
        if (s.p[k] >= 0 && s.p[k + 1] >= 0) {
            sc -= 200LL * abs(dist_cell[s.p[k]] - dist_cell[s.p[k + 1]]);
        }
    }
    return sc;
}

void remove_state(State& s) {
    while (s.removed < LOOK && s.board[EXIT] == s.removed) {
        s.board[EXIT] = EMPTY;
        s.p[s.removed] = -1;
        s.removed++;
    }
}

vector<pair<int,int>> reducing_ops(int cell) {
    vector<pair<int,int>> res;
    for (auto [b, idx] : occ[cell]) {
        int l = (int)belt[b].size();
        for (int d : {-1, 1}) {
            int to = belt[b][(idx + d + l) % l];
            if (dist_cell[to] == dist_cell[cell] - 1) res.push_back({b, d});
        }
    }
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

vector<pair<int,int>> plan_beam(int a) {
    State init;
    for (int i = 0; i < V; i++) init.board[i] = (short)g[i];
    init.p.fill(-1);
    for (int k = 0; k < LOOK && a + k < V; k++) {
        if (pos[a + k] >= 0) init.p[k] = (short)pos[a + k];
    }
    init.ops.clear();
    init.removed = 0;
    remove_state(init);
    init.score = eval_state(init);

    vector<State> beam = {init};
    vector<State> goal;
    int need = dist_cell[pos[a]];

    for (int depth = 0; depth < need; depth++) {
        vector<State> nxt;
        for (const State& cur : beam) {
            int cell = cur.p[0];
            for (auto [b, d] : reducing_ops(cell)) {
                State ns = cur;
                shift_state(ns, b, d, a);
                ns.ops.push_back({(short)b, (short)d});
                ns.score = eval_state(ns);
                if (ns.p[0] == EXIT) goal.push_back(ns);
                else nxt.push_back(std::move(ns));
            }
        }
        if (!goal.empty()) break;
        if (nxt.empty()) break;
        sort(nxt.begin(), nxt.end(), [](const State& x, const State& y) {
            if (x.score != y.score) return x.score > y.score;
            return x.ops.size() < y.ops.size();
        });
        if ((int)nxt.size() > BEAM) nxt.resize(BEAM);
        beam.swap(nxt);
    }

    if (goal.empty()) return {};
    sort(goal.begin(), goal.end(), [](const State& x, const State& y) {
        if (x.ops.size() != y.ops.size()) return x.ops.size() < y.ops.size();
        return x.score > y.score;
    });

    vector<pair<int,int>> ret;
    for (auto [b, d] : goal[0].ops) ret.push_back({b, d});
    return ret;
}

vector<pair<int,int>> plan_phase(int a) {
    State init;
    for (int i = 0; i < V; i++) {
        int val = g[i];
        init.board[i] = (val >= a && val < a + LOOK) ? (short)(val - a) : (short)val;
    }
    init.p.fill(-1);
    for (int k = 0; k < LOOK && a + k < V; k++) {
        if (pos[a + k] >= 0) init.p[k] = (short)pos[a + k];
    }
    init.ops.clear();
    init.removed = 0;
    remove_state(init);
    init.score = eval_state(init);

    vector<State> beam = {init};
    State best = init;
    for (int depth = 0; depth < PHASE_DEPTH; depth++) {
        vector<State> nxt;
        for (const State& cur : beam) {
            for (int b = 0; b < M; b++) {
                for (int d : {-1, 1}) {
                    State ns = cur;
                    shift_state(ns, b, d, 0);
                    ns.ops.push_back({(short)b, (short)d});
                    remove_state(ns);
                    ns.score = eval_state(ns);
                    nxt.push_back(std::move(ns));
                }
            }
        }
        sort(nxt.begin(), nxt.end(), [](const State& x, const State& y) {
            if (x.score != y.score) return x.score > y.score;
            return x.ops.size() < y.ops.size();
        });
        if (!nxt.empty() && nxt[0].score > best.score) best = nxt[0];
        if ((int)nxt.size() > BEAM) nxt.resize(BEAM);
        beam.swap(nxt);
    }

    if (best.removed == 0) return {};
    vector<pair<int,int>> ret;
    for (auto [b, d] : best.ops) ret.push_back({b, d});
    return ret;
}

pair<int,int> fallback_op(int a) {
    int best_b = -1, best_d = 0;
    long long best = LLONG_MIN;
    int before[LOOK];
    for (int k = 0; k < LOOK; k++) {
        before[k] = (a + k < V && pos[a + k] >= 0) ? dist_cell[pos[a + k]] : 0;
    }

    for (int b = 0; b < M; b++) {
        for (int d : {-1, 1}) {
            do_shift_global(b, d);
            long long sc = (g[EXIT] == a ? (long long)4e15 : 0);
            for (int k = 0; k < LOOK; k++) {
                if (a + k < V && pos[a + k] >= 0) {
                    sc += (LOOK - k) * 1000LL * (before[k] - dist_cell[pos[a + k]]);
                }
            }
            do_shift_global(b, -d);
            if (sc > best) {
                best = sc;
                best_b = b;
                best_d = d;
            }
        }
    }
    return {best_b, best_d};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nn;
    cin >> nn;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            int x;
            cin >> x;
            g[id(r, c)] = x;
            pos[x] = id(r, c);
        }
    }

    build_belts();
    build_dist();

    cout << M << '\n';
    for (int b = 0; b < M; b++) {
        cout << belt[b].size();
        for (int cell : belt[b]) {
            auto [r, c] = rc(cell);
            cout << ' ' << r << ' ' << c;
        }
        cout << '\n';
    }

    vector<pair<int,int>> ops;
    int a = 0;

    auto try_remove = [&]() {
        while (a < V && g[EXIT] == a) {
            g[EXIT] = EMPTY;
            pos[a] = -1;
            a++;
        }
    };
    try_remove();

    while (a < V && (int)ops.size() < 100000) {
        vector<pair<int,int>> plan = plan_phase(a);
        if (plan.empty()) plan = plan_beam(a);
        if (plan.empty()) plan.push_back(fallback_op(a));

        for (auto [b, d] : plan) {
            if ((int)ops.size() >= 100000 || a >= V) break;
            if (b < 0) break;
            do_shift_global(b, d);
            ops.push_back({b, d});
            try_remove();
        }
    }

    cout << ops.size() << '\n';
    for (auto [b, d] : ops) cout << b << ' ' << d << '\n';
    return 0;
}
