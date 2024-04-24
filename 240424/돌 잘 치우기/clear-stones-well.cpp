#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, k, m;
vector<vector<int>> mmap;
vector<pair<int, int>> rocks;
int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };

bool InRange(int x, int y) {
    return (x >= 0 && y >= 0 && x < n && y < n);
}

//bfs
int getBFS(vector<vector<int>>& temp_map, vector<bool>& removed_rocks) {
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    int num_count = 0;
    for (int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        queue<pair<int, int>> q;
        q.push({ r - 1, c - 1 });
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
                    q.push({ nx, ny });
                }
            }
        }
    }
    return num_count;
}

//back tracking
void generateCombinations(int idx, int count, vector<bool>& removed_rocks, int& max_count) {
    if (count == m) {
        vector<vector<int>> temp_map = mmap;
        for (int i = 0; i < rocks.size(); i++) {
            if (removed_rocks[i]) {
                temp_map[rocks[i].first][rocks[i].second] = 0;
            }
        }
        int num_count = getBFS(temp_map, removed_rocks);
        max_count = max(max_count, num_count);
        return;
    }

    for (int i = idx; i < rocks.size(); i++) {
        removed_rocks[i] = true;
        generateCombinations(i + 1, count + 1, removed_rocks, max_count);
        removed_rocks[i] = false;
    }
}

int main() {
    cin >> n >> k >> m;
    mmap.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mmap[i][j];
            if (mmap[i][j]) {
                rocks.push_back({ i, j });
            }
        }
    }

    int max_count = 0;
    vector<bool> removed_rocks(rocks.size(), false);
    generateCombinations(0, 0, removed_rocks, max_count);

    cout << max_count << '\n';
    return 0;
}