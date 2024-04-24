#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, k, m;
vector<vector<int>> mmap;
vector<pair<int, int>> rocks;
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

bool InRange(int x, int y) {
    return (x >= 0 && y >= 0 && x < n && y < n);
}

int bfs(vector<vector<int>>& temp_map, vector<vector<bool>>& visited) {
    int num_count = 0;
    for (int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        queue<pair<int, int>> q;
        q.push({r - 1, c - 1});
        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            if (!visited[x][y]) {
                visited[x][y] = true;
                num_count++;
            }
            q.pop();
            for (int ij = 0; ij < 4; ij++) {
                int nx = x + dx[ij];
                int ny = y + dy[ij];
                if (InRange(nx, ny) && !temp_map[nx][ny] && !visited[nx][ny]) {
                    q.push({nx, ny});
                }
            }
        }
    }
    return num_count;
}

int main() {
    cin >> n >> k >> m;
    mmap.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mmap[i][j];
            if (mmap[i][j]) {
                rocks.push_back({i, j});
            }
        }
    }

    int max_count = 0;
    vector<bool> removed(rocks.size(), false);
    for (int mask = 0; mask < (1 << rocks.size()); mask++) {
        if (__builtin_popcount(mask) != m) continue;
        vector<vector<int>> temp_map = mmap;
        for (int i = 0; i < rocks.size(); i++) {
            if (mask & (1 << i)) {
                temp_map[rocks[i].first][rocks[i].second] = 0;
            }
        }
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        int num_count = bfs(temp_map, visited);
        max_count = max(max_count, num_count);
    }

    cout << max_count << endl;
    return 0;
}