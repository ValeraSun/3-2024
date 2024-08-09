
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
ll n, m, s;
pair< vector<bool>, vector<bool>> answer;


ll sum(vector<vector<ll>>& a, vector<bool>& iter_n, vector<bool>& iter_m) {
	ll answer = 0;
	for (int i = 0; i < n; i++) {
		if (!iter_n[i]) { continue; }
		for (int j = 0; j < m; j++) {
			if (iter_m[j]) {
				answer += a[i][j];
			}
		}
	}
	return answer;
}
bool  solve(vector<vector<ll>>& a, vector<bool> iter_n, vector<bool> iter_m) {
	ll sum_a = sum(a, iter_n, iter_m);
	if (sum_a == s) {
		cout << "YES" << endl;
		ll count = 0;
		for (int i = 0; i < n; i++) {
			if (!iter_n[i]) { count++; }
		}
		for (int j = 0; j < m; j++) {
			if (!iter_m[j]) { count++; }
		}
		cout << count << endl;
		for (int i = 0; i < n; i++) {
			if (!iter_n[i]) { cout << 1 << " " << i + 1 << endl; }
		}
		for (int j = 0; j < m; j++) {
			if (!iter_m[j]) { cout << 2 << " " << j + 1 << endl; }
		}
		return 1;
	}
	if (sum_a < s) { return 0; }
	int i = 0, j = 0;
	for (int k = 0; k < n; k++) {
		if (!iter_n[k]) {
			i = k + 1;
			break;
		}
	}
	for (int k = 0; k < m; k++) {
		if (!iter_m[k]) {
			j = k + 1;
			break;
		}
	}
	for (; i < n; i++) {
		if (iter_n[i]) {
			iter_n[i] = 0;
			if (solve(a, iter_n, iter_m)) {
				return 1;
			}
			iter_n[i] = 1;
		}
	}
	for (; j < m; j++) {
		if (iter_m[j]) {
			iter_m[j] = 0;
			if (solve(a, iter_n, iter_m)) {
				return 1;
			}
			iter_m[j] = 1;
		}
	}
	return 0;
}

int main()
{
	cin >> n >> m;
	vector<vector<ll>> a(n, vector<ll>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	cin >> s;
	vector<bool> iter_n(n, 1);
	vector<bool> iter_m(m, 1);
	if (!solve(a, iter_n, iter_m)) {
		cout << "NO";
	}
	//for (int i = 0; i < n; i++) {
	//	cout << answer.first[i] << endl;
	//}
	//for (int j = 0; j < m; j++) {
	//	cout << answer.second[j];
	//}


}
