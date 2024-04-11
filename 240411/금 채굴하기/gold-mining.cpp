#include <iostream>
#include <vector>
#include <cmath>

using namespace std; 

/*
이차원 영역 벗어나도 채굴 가능(하지만 벗어난 곳에 금은 없음.)
채굴은 마름모 모양으로 단 한 번할 수 있음. 
특정 중심점을 기준으로 K번 이내로 상하좌우의 인접한 곳으로 이동하는 걸 반복했을 때 갈 수 있는 모든 영역이 색칠되어 있는 모양
k=0일 때 그 지점 하나만 채굴 

채굴 비용 : K * K + (k+1) * (K+1) 
금 한개의 가격 : m 
최대 얻을 수 있는 금 개수 : (n*n)

손해를 보지 않으면서 채굴할 수 있는 가장 많은 금의 개수를 출력하는 코드

일단 최대 k(max_k)는 K * K + (k+1) * (K+1) > n**2 일 때까지

*/

int n, m;
int total = 0;//얻은 금 개수

bool InRange(int x, int y, int n)
{
    return(x>=0 && y>=0 && x<n && y<n);
}

vector<vector<int>> mmap(n,vector<int>(n,0)); //map 정보

//중앙에서 시작하기

int dx[] = {0,1,0,-1};//동 남 서 북 순서
int dy[] = {1,0,-1,0};

vector<vector<bool>> visited1;//방문 여부
void DFS (int depth, int k, int x, int y)
{
    if(depth == k)
    {
        //얻은 금 가격 비교하기
        return;
    }

    //마름모 색칠해 나가기
    for(int i=0;i<4;i++)
    {
        //상하좌우 이동
        //cout<<"k : "<<k<<"depth : "<<depth<<" 현재 좌표 : "<<x<<' '<<y<<'\n'; 
        int nx = x+dx[i];
        int ny = y+dy[i];

        if(InRange(nx, ny, n))//영역안에 있으면서 안갔다왔으면,
        {
            if(mmap[nx][ny] == 1 && (!visited1[nx][ny]))
            {
                total++;
                visited1[nx][ny] = true;
            }      
            DFS(depth+1, k, nx, ny);
        }
    }
    //갈 수 있는지 여부 확인 & 갔다왔는지 여부 확인      
}

int main() {
    // 여기에 코드를 작성해주세요.
    // n : 격자 크기, m : 금 한개의 가격 
    cin >>n>>m;
    int num;
    vector<vector<int>> v1(n, vector<int>(n,0));
    //맵 정보 저장
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin >> num; 
            v1[i][j] = num;
        }
    }

    mmap = v1;
    vector<vector<bool>> visited(n, vector<bool>(n, false));//방문 여부

    //최대 반복할 k찾기
    int max_k = 0;
    while((max_k * max_k + (max_k+1) * (max_k+1)) < n*n)
    {
        max_k++;

    }
    max_k++; //한번더
    int ganswer = 0;
    int answer = 0;
    for(int x=0;x<n;x++)
    {
        for(int y=0;y<n;y++)
        {
            for (int i=0;i<=max_k;i++)
            {
                visited1 = visited;
                visited1[x][y] = true;
                total = 0;
                if(v1[x][y]==1)
                {
                    total++;
                }
                DFS(0, i,x,y);
                int cost = i * i + (i+1) * (i+1);
                int income = m * total - cost;//수익

                if(income >= 0)
                {
                    ganswer = max(ganswer, total);//최대 금 채굴

                }
            }
        }
    }
    cout<<ganswer;
    return 0;
}