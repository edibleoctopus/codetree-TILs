#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

int n, k, u, d;
vector<vector<int>> mmap;

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

int bfs(int startX, int startY, vector<vector<bool>>& visited) {
    int cnt = 1;
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny) && !visited[nx][ny]) {
                int diff = abs(mmap[x][y] - mmap[nx][ny]);
                if (diff >= u && diff <= d) {
                    q.push({nx, ny});
                    visited[nx][ny] = true;
                    cnt++;
                }
            }
        }
    }

    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k >> u >> d;
    mmap.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mmap[i][j];
        }
    }

    vector<pair<int, pair<int, int>>> cities;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<vector<bool>> visited(n, vector<bool>(n, false));
            int cnt = bfs(i, j, visited);
            cities.push_back({cnt, {i, j}});
        }
    }

    sort(cities.rbegin(), cities.rend());

    vector<vector<bool>> selected(n, vector<bool>(n, false));
    int ans = 0;

    for (int i = 0; i < cities.size() && k > 0; i++) {
        int x = cities[i].second.first;
        int y = cities[i].second.second;

        if (!selected[x][y]) {
            ans += cities[i].first;
            selected[x][y] = true;
            k--;
        }
    }

    cout << ans << endl;

    return 0;
}