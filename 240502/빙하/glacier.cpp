#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//1로 가로막혀있으면(못녹이는 물)visited를 못한다.
//가로막혀있지 않은 물을 찾는 방식으로 풀기
int n, m;
//bool visited[200][200];//방문 여부 저장(녹이는 물을 저장할 것.)
int last_count_g;
int t = 0;
int dx[] = { 0,1,0,-1 }, dy[] = { 1,0,-1,0 };//동남서북
vector<vector<int>> mmap;//맵 정보 저장
vector <vector<bool>> visited;

bool InRange(int x, int y)//영역 내에 있는지 확인
{
    return (x >= 0 && y >= 0 && x < n && y < m);
}

bool Cango(int x, int y)
{
    return (InRange(x, y) && !mmap[x][y] && !visited[x][y]);//영역안에 있고, 방문하지 않았으며, 1이아니면(빙하)
}



void BFS()
{
    visited.assign(n, vector<bool>(m, false));//visited 초기화
   /* for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            visited[i][j] = false; 
        }
    }*/

    queue<pair<int, int>> q;
    q.push({ 0,0 });
    visited[0][0] = true;

    while (!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (Cango(nx, ny))
            {
                q.push({ nx,ny });
                visited[nx][ny] = true;

            }
        }
    }
}

bool meltornot(int i, int j)
{
    for (int k = 0; k < 4; k++)
    {
        int nx = i + dx[k];
        int ny = j + dy[k];

        if (InRange(nx, ny))
        {
            if (visited[nx][ny])//방문한 물이 있으면,
            {
                return true;//녹이기
            }
        }
    }
    return false;//없으면 냅두기
}

void melt()
{
    last_count_g = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            //만약, 빙하라면 주변에(사방) visited 물이 있는지 확인하기
            if (mmap[i][j] == 1 && meltornot(i, j))
            {
                mmap[i][j] = 0;//물로 녹이기
                last_count_g++;
            }
        }
    }
}

bool exist_g()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mmap[i][j])//얼음이 있으면 계속
            {
                return true;
            }
        }
    }
    return false;//없으면 그만
}

int main()
{
    cin >> n >> m;
    mmap.resize(n, vector<int>(m));
    //맵 정보 입력
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> mmap[i][j];
        }
    }

    do {

        //녹이는 물 확인하기(0,0에서 시작 )->BFS로 visited 채우기
        BFS();
        //녹이기(visited 물 근처에 빙하가 있으면 녹이기)
        melt();
        t++;

    } while (exist_g());  //빙하가 다 녹았는지 확인하기

    //다 녹이는데 몇 초 걸렸고, 마지막에 몇 개 녹였는지 출력하기
    cout << t << ' ' << last_count_g;
    return 0;
}