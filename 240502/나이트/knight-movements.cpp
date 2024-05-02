#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
최소 이동 횟수를 구하는 프로그램

*/

int n;//격자 크기 
int r1, c1, r2, c2; //시작점, 끝점
queue<pair<int, int>> q;
vector<vector<bool>>visited;
vector<vector<int>> vt;

int dx[] = {-2,-2,-1,1,2,2,1,-1}, dy[] = {-1,1,2,2,1,-1,-2,-2};

bool InRange(int x, int y)
{
    return (x>=0 && y>=0 && x<n && y<n);
}

//최단거리 이동
void BFS(int x1, int y1)
{
    q.push({x1,y1});
    visited[x1][y1] = true;

    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for(int i=0;i<8;i++)
        {
            int nx = x+dx[i];
            int ny = y+dy[i];

            if(InRange(nx, ny) && !visited[nx][ny])
            {
                vt[nx][ny] = vt[x][y]+1;//이전 값에 +1 해주기
                q.push({nx,ny});
                visited[nx][ny] = true;
            }
        }

    }
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin>>n;
    visited.resize(n, vector<bool>(n, false));
    vt.resize(n,vector<int>(n, 0));
    cin>>r1>>c1>>r2>>c2;
    BFS(r1-1, c1-1);

    if(!vt[r2-1][c2-1])
        cout<<-1;

    else
        cout<< vt[r2-1][c2-1];

    return 0;
}