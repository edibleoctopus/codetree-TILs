#include <iostream>
#include <vector> 

//왼쪽, 아래로만 이동 가능, 뱀이 있는 위치로는 이동 불가
//두 방향 모두 이동 가능 시 아래쪽부터 우선 탐색
//그래프에서 두 정점의 연결관계를 표현하기 위해 -> 인접 행렬 or 인접 리스트 
//DFS 탐색에서는 재귀함수가 필요하며, 인자로 현재 위치를 나타내는 vertex 값이 필요 
//격자에서의 DFS 탐색에서는 (x,y) 좌표 필요 
//visied 배열에 방문 표시를 하는 위치를 재귀 함수 호출 전에 하지 않고, 다음과
//DFS 탐색 시에도 재귀함수 호출 직전에 Visitied 표기하는 패턴으로 연습하기
using namespace std;
int n, m; 

vector<vector<bool>> visited(n, vector<bool> (m,false));
vector<vector<int>> mmap(n, vector<int> (m,0));

bool InRange(int x, int y)
{
    return (x>=0 && x<n && y>=0 && y<m); 
}

bool cango(int x, int y)//갈 수 있는지 여부 확인
{
    if(!InRange(x, y))//아래 vector나 array에 할당되지 않은 값이 들어가지 않게 먼저
        return false; 

    if((visited[x][y]) || !mmap[x][y]) //값이 0(뱀)이거나 방문했을 때 false
        return false;

    else 
        return true;
}
bool poss = false;
void DFS(int x, int y)
{
    if(!cango(x, y))
        return;

    if(x==(n-1) && y==(m-1))
    {
        poss = true;
        return; 
    }

    int dx[] = {0,1};//우, 하
    int dy[] = {1,0};

    for(int i=0;i<2;i++)
    {
        int nx = x+dx[i];
        int ny = y+dy[i];

        if(cango(nx, ny))//갈 수 있으면,
        {
            visited[x][y] = true;
            DFS(nx, ny);
        }
    }
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin>>n>>m;
    visited.resize(n, vector<bool> (m, false));
    mmap.resize(n, vector<int> (m,0));

    //맵 정보 입력
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin >> mmap[i][j];
        }
    }

    DFS(0,0);

    if(poss)
        cout<<1;
    else
        cout<<0;

    return 0;
}