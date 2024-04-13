#include <iostream>
#include <vector>
#include <queue>

/*
2차원 격자 위에서 단일 객체를 이동하는 유형에 대해 배워보도록 하겠습니다.

2차원 격자 정보가 주어졌을 때, 인접한 4개의 칸 중 
'가장 큰 숫자로 이동하는 것을 t번 반복' 하려고 합니다. 
최종 위치를 출력하는 프로그램을 작성해보세요. 
단, 인접한 4개의 칸 중 가장 큰 숫자가 여러 개라면, 
상하좌우 순서대로 '우선순위를 매겨 가능한 곳 중 우선순위가 더 높은곳으로 이동'합니다.
현재 위치에 있는 숫자보다 더 큰 위치로 끊임없이 이동
만약 그러한 위치가 여러개 있는 경우, 상하좌우 방향 순서대로 우선순위를 매겨 가능한 곳 중 우선순위가 
더 높은 곳으로 이동
격자를 벗어나서는 안되며, 더 이상 움직일 수 없을 때까지 반복

*/
using namespace std; 
bool InRange(int x, int y, int n)
{
    return (x>=0 && y>=0 &&x<n&&y<n);
}

int main() {
    // 여기에 코드를 작성해주세요.
    int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1}; //상, 하, 좌, 우 방향 순서대로

    int n;
    int r,c;

    cin>>n>>r>>c; //격자 크기, 시작 좌표
    r = r-1;
    c = c-1;

    vector<vector<int>> v1(n, vector<int>(n,0));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>v1[i][j];
        }
    }
    queue<pair<int, int>> q; 
    q.push({r,c});

    int mmax = v1[r][c];
    cout<<mmax<<' ';
    while(!q.empty())
    {
        int x = q.front().first; 
        int y = q.front().second; 
        q.pop();
        int ck_mmax = mmax;
        for(int i=0;i<4;i++)
        {   
            int nx = x+dx[i];
            int ny = y+dy[i];

            if(InRange(nx, ny, n))//영역 안에 있고
            {
                if(v1[nx][ny] > mmax)
                {
                    mmax = v1[nx][ny] ;
                    q.push({nx,ny});
                    break;
                }
            }
        }
        if(mmax == ck_mmax)
            break;
        cout<<mmax<<' ';
    }

    return 0;
}