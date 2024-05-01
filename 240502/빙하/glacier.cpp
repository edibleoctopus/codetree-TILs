#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
int t = 0;
int dx[] = {0,1,0,-1}, dy[]={1,0,-1,0};
vector<vector<int>> mmap;
vector<vector<bool>> visited;

// 범위 내에 있는지 확인
bool InRange(int x, int y) {
    return (x >= 0 && y >= 0 && x < n && y < m);
}

// 방문 가능한지 확인
bool CanGo(int x, int y) {
    return (InRange(x, y) && !mmap[x][y] && !visited[x][y]);
}

void BFS() {
    queue<pair<int, int>> q;
    q.push({0, 0});
    visited[0][0] = true;
    
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (CanGo(nx, ny)) {
                q.push({nx, ny});
                visited[nx][ny] = true;
            }
        }
    }
}
int last_count_g;
// 주변에 물이 있는지 확인하고 녹이기
void Melt() {
    last_count_g = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mmap[i][j] == 1) {
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    
                    if (InRange(nx, ny) && visited[nx][ny]) {
                        mmap[i][j] = 0;
                        last_count_g++;
                        break;
                    }
                }
            }
        }
    }
    
    t++;
}

bool GlacierExist() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mmap[i][j] == 1) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    mmap.resize(n, vector<int>(m));
    visited.resize(n, vector<bool>(m, false));
    
    // 맵 정보 입력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mmap[i][j];
        }
    }
    
    do {
        BFS(); // 빙하가 녹을 수 있는 물 주변을 탐색
        Melt(); // 빙하 녹이기
    } while (GlacierExist()); // 빙하가 존재하는 한 반복
    
    // 결과 출력
    cout << t << ' ' << last_count_g;
    
    return 0;
}