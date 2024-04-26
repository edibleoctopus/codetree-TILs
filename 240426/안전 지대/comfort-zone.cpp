#include <iostream>
#include <vector> 
#include <cmath> 

using namespace std; 

//집의 높이는 1이상 100이하의 숫자로 구성 
//안전 영역이란 잠기지 않은 집들로 이루어져 있으며, 
//잠기지 않은 집들끼리 서로 인접해 있는 경우 동일한 안전 영역에 있는 것으로 봅니다.
//잠긴 집 : 장애물, 장애물을 기준으로 나뉜 청크가 안전 영역임.

//안전 영역의 수가 최대가 될때의 K와 그 때의 안전 영역의 수
//K <= 100(K를 100까지 할 것인가?)
int n, m; 

vector<vector<int>> mmap; 
vector<vector<bool>> visited;

bool InRange(int x, int y)
{
    return (x>=0 && y>=0 && x<n && y<m);
}

bool Cango(int x, int y)
{
    if(InRange(x, y))//영역안에 있을 때,
    {
        return (mmap[x][y] && !visited[x][y]);//맵이 0이아니고 이동가능하면 true
    }
    return false;
}

int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0}; //동남서북

void DFS(int x, int y)///이동 확인 
{
    for(int i=0;i<4;i++)
    {
        int nx = x+dx[i];
        int ny = y+dy[i];

        if(Cango(nx, ny)) //이동 가능시
        {
            visited[nx][ny] = true;
            DFS(nx, ny);
        }
    }
}


int main() {
    // 여기에 코드를 작성해주세요.
    cin>>n>>m; 
    //맵 정보 입력
    mmap.resize(n,vector<int>(m));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
           cin >> mmap[i][j];
        }
    }
    //안전 영역의 수가 몇 개인지, 최대인지 확인해야 함.
    //K보다 작은 곳을 다 0으로 만들어서 이동 불가로 만들어야함. 
    //이동 가능한지(맵이 0인지, 방문했는지, 영역 내에 있는지)를 확인하고 DFS 진행해서 청크를 확인
    //이걸로 청크 개수 확인하기
    int ans = 0;
    int max_k = 0;

    for(int k=1; k<101; k++)//k값 변화시키기
    {
        //물에 잠기게 하기
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(mmap[i][j] <= k)
                {
                    mmap[i][j] = 0;
                }
            }
        }

        //visited 초기화
        visited.assign(n, vector<bool>(m, false));

        //DFS로 안전 영역 세기
        int ccount =0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(Cango(i, j))
                {
                    visited[i][j] = true;
                    ccount++;
                    DFS(i, j);
                }
            }
        }

        if(ans < ccount)
        {
            max_k = k;
            ans = ccount;
        }
    }   

    cout<<max_k<<' '<<ans;
    return 0;
}