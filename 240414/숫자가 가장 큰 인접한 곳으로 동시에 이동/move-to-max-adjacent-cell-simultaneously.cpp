#include <iostream>
#include <vector>

using namespace std;

int n; // 격자의 크기
vector<vector<int>> next_count(n, vector<int>(n,0)); // 다음 상태의 구슬 수를 저장할 배열
vector<vector<int>> Count(n, vector<int>(n,0)); // 현재 상태의 구슬 수를 저장할 배열
vector<vector<int>> real_mmap(n, vector<int>(n,0)); // 실제 구슬이 있는지 여부를 나타내는 배열

int dx[] = {-1, 1, 0, 0}; // 상하좌우 이동을 위한 배열
int dy[] = {0, 0, -1, 1};

bool InRange(int x, int y) {
    return (x >= 0 && y >= 0 && x < n && y < n);
}

pair<int, int> GetNextPos(int x, int y) {
    int max_val = -1;
    pair<int, int> next_pos = {x, y};
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (InRange(nx, ny) && real_mmap[nx][ny] > max_val)//영역안에 있고,  
        {
            max_val = real_mmap[nx][ny];
            next_pos = {nx, ny};
        }
    }
    return next_pos;
}

void MoveAll() {
    next_count.assign(n, vector<int>(n, 0)); // 다음 구슬 위치 상태 배열을 0으로 초기화

    // 각 위치에서의 구슬 개수를 계산하여 next_count에 저장
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (Count[i][j] == 1) {
                pair<int, int> next_pos = GetNextPos(i, j);
                next_count[next_pos.first][next_pos.second]++;
            }
        }
    }

    // 다음 상태의 구슬 수를 현재 상태로 복사
    Count = next_count;
}

void RemoveDuplicateMarbles() {
    // 충돌이 일어난 구슬은 현재 상태에서 제거
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (Count[i][j] >= 2) {
                Count[i][j] = 0;
            }
        }
    }
}

void Simulate(int t) {
    // t번 반복하여 구슬 이동 및 충돌 제거
    while (t--) {
        MoveAll();
        RemoveDuplicateMarbles();
    }
}

int main() {
    int m, t; // 구슬 개수와 반복 횟수
    cin >> n >> m >> t; // 격자 크기, 구슬 개수, 반복 횟수 입력

    // 벡터 크기 초기화
    next_count.assign(n, vector<int>(n, 0));
    Count.assign(n, vector<int>(n, 0));
    real_mmap.assign(n, vector<int>(n, 0));

    // 격자 정보 입력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> real_mmap[i][j];
        }
    }

    // 구슬 위치 입력 및 count 배열 초기화
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        Count[x-1][y-1] = 1;
    }

    // 구슬 이동 및 충돌 시뮬레이션
    Simulate(t);

    // 남아있는 구슬의 개수 계산
    int remaining_marbles = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (Count[i][j] == 1) {
                remaining_marbles++;
            }
        }
    }

    // 결과 출력
    cout << remaining_marbles << endl;

    return 0;
}