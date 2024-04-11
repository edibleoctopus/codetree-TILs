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

bool InRange(int x, int y, int n)
{
    return(x>=0 && y>=0 && x<n && y<n);
}

vector<vector<bool>> visited1;//방문 여부
vector<vector<int>> mmap(n,vector<int>(n,0)); //map 정보

//중앙에서 시작하기

int dx[] = {0,1,0,-1};//동 남 서 북 순서
int dy[] = {1,0,0,-1};
int answer = 0; //최대 가격
int ganswer = 0;
void DFS (int depth, int k, int total, int x, int y)
{
    if(depth == k*4)
    {
        //얻은 금 가격 비교하기
        int cost = k * k + (k+1) * (k+1);
        int income = m*total - cost;//수익
        int answer2 = answer;
        answer = max(answer, income);//최대 수익
        if(answer != answer2)//유지시
            ganswer = total;
        return;
    }

    //마름모 색칠해 나가기
    for(int i=0;i<4;i++)
    {
        //상하좌우 이동
        int nx = x+dx[i];
        int ny = y+dy[i];

        if(InRange(nx, ny, n) && (!visited1[nx][ny]))//영역안에 있으면서 안갔다왔으면,
        {
            visited1[nx][ny] = true;
            if(mmap[nx][ny] == 1)
            {
                total++;
            }      
            x = nx, y = ny;
            DFS(depth+1, k, total,x,y);
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
    visited1 = visited;

    //최대 반복할 k찾기
    int max_k = 0;
    while((max_k * max_k + (max_k+1) * (max_k+1)) < n*n)
    {
        max_k++;
    }
    max_k++; //한번더

    //중앙에서 시작
    int x = n/2;
    int y = n/2;

    int total = 0;//얻은 금 개수
    if(v1[x][y]==1)
    {
        total++;
    }

    for (int i=0;i<=max_k;i++)
    {
        DFS(0, i, total,x,y);
    }
    
    cout<<ganswer;

    return 0;
}