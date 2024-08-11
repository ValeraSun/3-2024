#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 15;
int a[maxn][maxn];
long long smaskSum[1 << maxn];
long long dp[1 << maxn][1 << ((maxn + 1) / 2)];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    long long s;
    cin >> s;
    int half = (m + 1) / 2;
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < (1 << half); ++j) {
            dp[i][j] = 0;
        }
    }   



    for (int mask = 0; mask < (1 << half); ++mask) {

        fill(smaskSum, smaskSum + (1 << n), 0);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < half; ++j) {
                if ((1 << j) & mask) {
                    smaskSum[1 << i] += a[i][j];
                }
            }
        }

        for (int bit = 0; bit < n; ++bit) {
            for (int mask = 0; mask < (1 << n); ++mask) {
                if ((1 << bit) & mask) {
                    smaskSum[mask] += smaskSum[mask ^ (1 << bit)];
                }
            }
        }

        for (int smask = 0; smask < (1 << n); ++smask) {
            dp[smask][mask] = smaskSum[smask] * (1 << half) + mask;
        }
    }



    for (int mask = 0; mask < (1 << n); ++mask) {
        sort(dp[mask], dp[mask] + (1 << half));
    }


    for (int mask = 0; mask < (1 << (m - half)); ++mask) {
        fill(smaskSum, smaskSum + (1 << n), 0);
        for (int i = 0; i < n; ++i) {
            for (int j = half; j < m; ++j) {
                if ((1 << (j - half)) & mask) {
                    smaskSum[1 << i] += a[i][j];
                }
            }
        }
        for (int bit = 0; bit < n; ++bit) {
            for (int mask = 0; mask < (1 << n); ++mask) {
                if ((1 << bit) & mask) {
                    smaskSum[mask] += smaskSum[mask ^ (1 << bit)];
                }
            }
        }
        for (int smask = 0; smask < (1 << n); ++smask) {
            long long need = s - smaskSum[smask];
            if (need < 0) continue;
            auto pt = lower_bound(dp[smask], dp[smask] + (1 << half), need * (1 << half));
            if (pt != dp[smask] + (1 << half) && (*pt) / (1 << half) == need) {
                cout << "YES\n";
                int msk = (1 << half) * mask + (*pt % (1ll << half));
                vector<pair<int, int>> res;
                for (int i = 0; i < n; ++i) {
                    if (!((1 << i) & smask)) {
                        res.push_back({ 1, i + 1 });
                    }
                }
                for (int i = 0; i < m; ++i) {
                    if (!((1 << i) & msk)) {
                        res.push_back({ 2, i + 1 });
                    }
                }
                cout << res.size() << '\n';
                for (auto i : res) {
                    cout << i.first << ' ' << i.second << '\n';
                }
                return;
            }
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    t = 1;
    while (t--) {
        solve();
    }
}
