#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

vector<vector<int>> mmap;
bool visited[9][9];
int n, k, u, d;

bool InRange(int x, int y) {
    return (x >= 0 && y >= 0 && x < n && y < n);
}

bool Cango(int x, int y, int nx, int ny) {
    if (InRange(nx, ny)) {
        int diff = abs(mmap[nx][ny] - mmap[x][y]);
        if (diff >= u && diff <= d && !visited[nx][ny]) {
            return true;
        }
    }
    return false;
}

int BFS(int x, int y) {
    queue<pair<int, int>> q;
    q.push({ x, y });
    visited[x][y] = true;
    int c = 1;

    int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (Cango(x, y, nx, ny)) {
                visited[nx][ny] = true;
                c++;
                q.push({ nx, ny });
            }
        }
    }
    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k >> u >> d;

    mmap.resize(n, vector<int>(n));
    vector<pair<int, int>> cities;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mmap[i][j];
            cities.push_back({ i, j });
        }
    }

    vector<pair<int, pair<int, int>>> city_counts;
    for (int i = 0; i < cities.size(); i++) {
        //visited 초기화
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                visited[j][k] = false;
            }
        }
        //모든 시작점에서 BFS 실시
        int count = BFS(cities[i].first, cities[i].second);
        city_counts.push_back({ count, {cities[i].first, cities[i].second}});
    }
    //내림차순 정렬
    sort(city_counts.rbegin(), city_counts.rend());

    int ans = 0;
    vector<bool> selected(cities.size(), false);
    for (int i = 0; i < k; i++) {
        int count = city_counts[i].first;
        int x = city_counts[i].second.first;
        int y = city_counts[i].second.second;

        if (!selected[x * n + y]) {
            ans += count;
            selected[x * n + y] = true;
        }
    }

    cout << ans;

    return 0;
}