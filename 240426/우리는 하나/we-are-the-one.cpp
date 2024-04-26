#include <iostream>
#include <vector> 
#include <queue>
#include <cmath>

using namespace std;

/*
n*n 크기의 격자로 이루어져 있는 나라 정보 
각 칸마다 하나의 도시가 존재
각 도시마다 높이 정보가 주어짐
이때 k개의 도시를 겹치지 않게 적절하게 골라(백트래킹)
골라진 k개의 도시로부터 갈 수 있는 서로 다른 도시의 수를 최대화 하고자 합니다. 
이때 이동은 상하좌우로 인접한 도시간의 이동만 가능하며, 그중에서도 두 도시간의 높이의 차가 u이상 d이하인
경우에만 가능합니다. 

k개의 도시를 적절하게 골라 갈 수 있는 서로 다른 도시의 수를 최대로 하는 프로그램을 작성해보세요. 

*/

vector<vector<int>> mmap; 
bool visited[9][9];

int n, k, u, d;

bool InRange(int x, int y)
{
    return (x>=0 && y>=0 && x<n && y<n);
}

bool Cango(int x, int y, int nx, int ny)
{
    if(InRange(nx,ny))
    {
        if(abs(mmap[nx][ny]-mmap[x][y])>=u && abs(mmap[nx][ny]-mmap[x][y])<=d && !visited[nx][ny])//u이상 d이하 차이, 방문하지 않은 나라
        {
            return true;
        }
    }
    return false;
}

vector<pair<int, int>> selected_country;
queue<pair<int, int>> q;
vector<pair<int, int>> mp; 

int BFS()
{
     int c=0;
    for(int i = 0; i<k;i++)
    {
        int x = selected_country[i].first; 
        int y = selected_country[i].second;
        q.push({x,y});
        visited[x][y] = true;
        c++;
    }

    int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};
    while(!q.empty())
    {
       int x = q.front().first;
       int y = q.front().second;

       q.pop();

       for(int i=0;i<4;i++)
       {
        int nx = x+dx[i];
        int ny = y+dy[i];

        if(Cango(x,y,nx,ny))
        {
            visited[nx][ny] = true;
            c++;
            q.push({nx, ny});
        }
       }
    }
   
    return c;
}

int ans = 0;
void back(int idx, int cnt)
{
    if(idx == mp.size())
    {
        if(cnt == k)
        {
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    visited[i][j] = false;
                }
            }
            int ccount = BFS();
            ans = max(ans, ccount);
        }
        return;
    }
    selected_country.push_back(mp[idx]);
    back(idx+1, cnt+1);
    selected_country.pop_back(); 
    back(idx+1, cnt);
}

int main() {
    // 여기에 코드를 작성해주세요.
     //시간 초과 방지
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>n>>k>>u>>d;
    //맵 정보 입력
    mmap.resize(n, vector<int>(n));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>mmap[i][j];
            mp.push_back({i,j});
        }
    }

    //k개 고르고 갈 수 있는 나라의 수를 구한다.(백트래킹)
    //사실상 시작점 고르는 것과 같음. 
    
    back(0,0); 

    cout<<ans;
    return 0;
}