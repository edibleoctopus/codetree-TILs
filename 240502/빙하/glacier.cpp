#include <iostream>
#include <vector>
#include <queue>

#define DIR_NUM 4
#define MAX_N 200
#define MAX_M 200

using namespace std; 

//1로 가로막혀있으면(못녹이는 물)visited를 못한다.
//가로막혀있지 않은 물을 찾는 방식으로 풀기
int n, m;
int t = 0;
int dx[] = { 0,1,0,-1 }, dy[] = { 1,0,-1,0 };//동남서북

int mmap[MAX_N][MAX_M];//맵 정보 저장
bool visited[MAX_N][MAX_M];
queue<pair<int, int>> q;
int last_count_g;

bool InRange(int x, int y)//영역 내에 있는지 확인
{
    return (x>=0 && y>=0 && x<n && y<m);
}

bool Cango(int x, int y)
{
    return (InRange(x, y) && !mmap[x][y] && !visited[x][y]);//영역안에 있고, 방문하지 않았으며, 1이아니면(빙하)
}

void Init()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            visited[i][j] = 0;
        }
    }
}

void BFS()
{
    Init();

    q.push({0,0});//0,0에서 시작
    visited[0][0] = true;

    while(!q.empty())
    {
        pair<int, int> cc = q.front();
        int x = cc.first, y = cc.second;
        q.pop();

        for(int i=0;i< DIR_NUM;i++)
        {
            int nx = x+dx[i];
            int ny = y+dy[i];

            if(Cango(nx,ny))
            {
                q.push({nx,ny});
                visited[nx][ny] = true;
            }
        }
    }
}

bool meltornot(int x, int y)
{
    for(int k=0;k< DIR_NUM;k++)
    {
        int nx = x+dx[k], ny = y + dy[k];

        if(InRange(nx, ny) && visited[nx][ny])
        {        
            return true;//녹이기     
        }
    }
    return false;//없으면 냅두기
}


void melt()
{

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            //만약, 빙하라면 주변에(사방) visited 물이 있는지 확인하기
            if(mmap[i][j] == 1 && meltornot(i, j))
            {
                mmap[i][j] = 0;//물로 녹이기
                last_count_g++;
            }
        }
    }
}

bool exist_g()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(mmap[i][j])//얼음이 있으면 계속
            {
                return true;
            }
        }
    }
    return false;//없으면 그만
}

void Simulate() {
    t++;
    last_count_g = 0;

    //녹이는 물 확인하기(0,0에서 시작 )->BFS로 visited 채우기
    BFS();
    //녹이기(visited 물 근처에 빙하가 있으면 녹이기)
    melt();

}
int main()
{
    cin>>n>>m;

    //맵 정보 입력
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>mmap[i][j];
        }
    }
    
    do{
        Simulate();
    }while(exist_g());  //빙하가 다 녹았는지 확인하기

    //다 녹이는데 몇 초 걸렸고, 마지막에 몇 개 녹였는지 출력하기
    cout<<t<<' '<<last_count_g;
    return 0;
}