#include <iostream>
#include <queue>
#include <vector> 

using namespace std;

bool InRange(int x, int y, int n)
{
    return (x>=0 && y>=0 && x<n && y<n);
}

int main() {
    // 여기에 코드를 작성해주세요.
    int n, k;//n : 격자 크기, k : 시작점 개수 
    cin>>n>>k;
    vector<vector<int>> mmap(n,vector<int>(n,0));
    vector<vector<bool>> visited(n, vector<bool>(n,false));

    //맵 정보 기입
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>mmap[i][j];
        }
    }

    queue<pair<int, int>> spqueue;
    int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};//동남서북
    //시작점 추가
    int ccount = 0;
    for(int i=0;i<k;i++)
    {
        int sx, sy;
        cin>>sx>>sy;
        sx--;
        sy--;
        spqueue.push({sx, sy});
        if(!visited[sx][sy])
        {
            ccount++;
            visited[sx][sy] = true; 
        }
        
        while(!spqueue.empty())
        {
            int x = spqueue.front().first;
            int y = spqueue.front().second;
            spqueue.pop();

            for(int j=0;j<4;j++)
            {
                int nx = x+dx[j];
                int ny = y+dy[j];

                if(InRange(nx, ny, n))//맵 밖이 아님
                {
                    if(mmap[nx][ny]==0 && !visited[nx][ny])//벽이 아님, 다녀온 곳이 아님
                    {
                        visited[nx][ny] = true;

                        spqueue.push({nx,ny});
                        ccount++;
                    }
                }
            }
        }
    }

    cout<<ccount;
    
    return 0;
}