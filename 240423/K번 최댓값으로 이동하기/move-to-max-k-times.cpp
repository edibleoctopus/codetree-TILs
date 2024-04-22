#include <iostream>
#include <vector> 
using namespace std;
/*
n*n 크기의 격자에 1이상 100이하의 숫자가 각 칸에 하나씩 주어져 있습니다.
이때 특정 위치에서 시작하여 아래 조건을 만족하는 숫자의 위치를 찾아 상하좌우로만 이동합니다.
이렇게 이동하는 것을 k번 반복한 이후의 위치를 구하는 프로그램을 작성해보세요.
만약 아직 k번을 반복하지 못했지만, 더 이상 새로 이동할 위치가 없다면 움직이는 것을 종료합니다.

이동 조건 :
시작 위치에 적혀있는 숫자를 x라고 했을 때, 시작 위치에서 출발하여 인접한 칸들 중 적혀있는 숫자가
x보다 작은 곳으로는 전부 이동이 가능합니다.
갈 수 있는 칸 중 최대 숫자 선택
만약 여러 개라면 행 번호가 가장 작은 곳으로 이동
또 여러개라면 열 번호가 가장 작은 곳으로 이동

이동 불가 조건 : 자기 자신보다 큰 숫자로 둘러쌓여있을 때, 격자 밖으로 나갈 때

1) 시작 위치 값보다는 작지만 그 중 가장 큰 값을 고른다.
*/
int n;//격자 크기 
int k;//이동 횟수 

vector<vector<int>>mmap;
vector<pair<int, int>> max_val; //값이 max인 좌표 추가
int mmax;//최대 값 저장

bool InRange(int x, int y)
{
    return (x >= 0 && y >= 0 && x < n && y < n);
}

int dx[] = { 0,1,0,-1 }, dy[] = { 1,0,-1,0 };//동남서북 순서

//갈 수 있는 곳 중에서 가장 큰 곳으로 이동
vector<vector<bool>> visited;
bool poss = false;

void DFS(pair<int, int> p, int val)
{
    int x = p.first;
    int y = p.second;

    if(!InRange(x, y))
        return;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (InRange(nx, ny))//영역안에 있고,
        {
            if(!visited[nx][ny])
            {
                visited[nx][ny] = true;

            if (mmap[nx][ny] < val)//시작 위치 값보다는 작은데
            {
                poss = true;
                if (mmap[nx][ny] > mmax)//다른 값보다 크다면,
                {
                    mmax = mmap[nx][ny];//mmax 값 업데이트
                    max_val.clear();//이전 값 좌표 다 지우기
                    max_val.push_back({ nx,ny });//좌표 저장
                }

                else if (mmap[nx][ny] == mmax)//가장 큰 값과 같다면,
                {
                    max_val.push_back({ nx,ny });
                }
                DFS({ nx, ny }, val);
            }
            }
        }
    }
    
    if (!poss)//상하좌우 다 못나가면.
        return;
}

pair<int, int> checker(vector<pair<int, int>> a)
{
    //a.first 중에서 값이 가장 작은 것 모으기
    //b.first 중에서 값이 가장 작은 것 모으기
    if (a.empty())
    {
        return make_pair(-1, -1);
    }

    vector<pair<int, int>> b;
    pair<int, int> min_pair = a[0];
    for (const auto& p : a)
    {
        if (p.first < min_pair.first)
        {
            b.clear();
            min_pair = p;
            b.push_back(p);
        }
        else if (p.first == min_pair.first)
        {
            b.push_back(p);
        }
    }

    min_pair = b[0];
    for (const auto& p : b)
    {
        if (p.second < min_pair.second)
        {
            min_pair = p;
        }
    }
    return min_pair;
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> n >> k;
    mmap.resize(n, vector<int>(n));
    visited.resize(n, vector<bool>(n, false));
    //맵정보 입력
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> mmap[i][j];
        }
    }

    int r, c;
    cin >> r >> c;//시작 좌표 입력
    r = r - 1, c = c - 1;
    pair<int, int> p;
    //자기값보다는 작은데 그중에서 가장 큰 값의 좌표 찾기
    for (int i = 0; i < k; i++)
    {
        p = { r,c };
        mmax = 0;
        DFS(p, mmap[r][c]);
        int rp = r, cp = c;
        r = checker(max_val).first;
        c = checker(max_val).second;
        if(r==-1 && c==-1)
        {
            cout<<rp+1<<' '<<cp+1;
            return 0;
        }
        poss = false;
        visited.assign(n, vector<bool>(n, false));
    }

    cout << r+1 << ' ' << c+1;
    return 0;
}