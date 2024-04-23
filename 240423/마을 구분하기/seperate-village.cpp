#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
n * n크기의 이차원 영역에 사람 혹은 벽이 놓여져있습니다. 
이 때 상하좌우의 인접한 영역에 있는 사람들은 같은 마을에 있는 것으로 간주한다고 합니다. 
예를 들어 <그림 1> 같이 사람과 벽이 배치되어 있는 경우, 그림 안의 점선과 같이 
마을을 나눌 수 있습니다. 

이 때 총 마을의 개수와 같은 마을에 있는 사람의 수를 오름차순으로 
정렬하여 출력하는 코드를 작성해보세요.
*/

int n; //마을의 크기
vector<vector<int>> mmap;//마을 정보
vector<vector<bool>> visited;//방문 여부 확인
vector<int> people_num;//마을 내 사람 수

int ccount=0; //마을 수 
int num=0;

//마을의 개수, 마을 내 사람의 수 정렬해서 출력
//각 지점에서 DFS해서(더 이상 못 움직일 때까지, visited 사용)
//DFS를 할 때마다 count(마을 개수)
//DFS 내에서 또 1을 만나면 count(사람 수), vector에 저장

int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0}; //동, 남, 서, 북

bool InRange(int x, int y)
{
    return (x>=0 && y>=0 && x<n && y<n);
} 

void DFS(int x, int y)
{
    if(!InRange(x,y))
        return;

    if((!visited[x][y]) && mmap[x][y])//방문하지 않았다면 + 값이 0이 아니라면
    {
        visited[x][y] = true;
        //cout<<"좌표 : "<<x<<' '<<y<<'\n';
        num++;//인구수 추가
    }

    else//방문 했다면, 값이 0이라면,
        return;

    for(int i=0;i<4;i++)//동서 남북 탐색
    {
        int nx = x+dx[i];
        int ny = y+dy[i];
        DFS(nx,ny);
    }        
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >>n;

    mmap.resize(n, vector<int> (n));
    visited.resize(n, vector<bool> (n,false));

    //맵정보 기입
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
           cin>>mmap[i][j];
        }
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
           DFS(i, j);
           if(num) {
            ccount++;//마을 수 추가
            people_num.push_back(num);//num이 0이 아니면, 인구수 추가
           }
           num = 0;//인구 수 초기화
        }
    }
    sort(people_num.begin(), people_num.end());
    cout<<ccount<<'\n';
    for(int i=0;i<people_num.size();i++)
    {
        cout<<people_num[i]<<'\n';
    }

    return 0;
}