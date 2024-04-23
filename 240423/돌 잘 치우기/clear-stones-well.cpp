#include <iostream>
#include <queue>

using namespace std; 

/*

숫자 0, 1로만 이루어진 n * n 격자가 주어졌을 때, 
주어진 돌 중 m개의 돌만 적절하게 치워 k개의 시작점으로부터 상하좌우 인접한 곳으로만 이동하여
도달 가능한 칸의 수를 최대로 하는 프로그램을 작성해보세요. 
숫자 0은 해당 칸이 이동할 수 있는 곳임을, 숫자 1은 돌이 있어 해당 칸이 이동할 수 없는 곳임을 
의미합니다.

*/

//n,k,m 순서대로 받음
int n, k, m;
vector<vector<int>> mmap;
vector<pair<int, int>> current;//조합 하나 저장
vector<vector<pair<int, int>>> result;//돌 좌표 조합 저장
vector<pair<int, int>> rock;//돌 위치 정보 저장

void combination(int m, int index)
{
    if(current.size() == m)
    {
        result.push_back(current);
        return;
    }

    for(int i=index;i<rock.size();i++)
    {
        current.push_back(rock[i]);
        combination(m,i+1);
        current.pop_back();
    }
}

bool InRange(int x, int y)
{
    return (x>=0 && y>=0 && x<n && y<n);
}

vector<vector<bool>> visited;

int main() {
    // 여기에 코드를 작성해주세요.
    cin >>n>>k>>m;
    mmap.resize(n, vector<int>(n));

    //맵정보 입력
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>mmap[i][j];
            if(mmap[i][j])//돌이면 좌표 저장
                rock.push_back({i,j});
        }
    }
    //0은 이동할 수 있는곳, 숫자 1은 돌이 있어 이동할 수 없는 곳.
    //치울 돌을 추가해놓고 그중 m개를 골라 0으로 만들기

    combination(m, 0);//조합 구하기

    int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};//동남서북
    //k개 시작점에서 이동해서 이동가능한 칸 구하기(BFS)
    int max_count = 0;

    for(int j=0;j<result.size();j++)
    {
        //돌 좌표(rock 중에) k개만큼 뽑고 맵에서 제거하기(조합)
        vector<vector<int>> temp = mmap;
        visited.assign(n, vector<bool>(n,false));

        for(int ij=0;ij<result[j].size();ij++)//조합 하나 뽑기
        {
            int x = result[j][ij].first;
            int y = result[j][ij].second;

            //cout<<ij<<" 돌 좌표 : "<<x<<' '<<y<<'\n';

            temp[x][y] = 0;//돌 제거하기
        }

        //BFS 진행
        int r, c;
        int num_count = 0;
        for(int i=0;i<k;i++)
        {
            queue<pair<int, int>> q;
            cin >>r>>c;
            q.push({r-1,c-1});
            while(!q.empty())
            {
                int x = q.front().first; 
                int y = q.front().second; 
                if((!visited[x][y])) 
                {
                    //cout<<i<<" 좌표 : "<<x<<' '<<y<<'\n';
                    visited[x][y] = true;
                    num_count++;
                }

                q.pop();

                for(int ij=0;ij<4;ij++)//상하 좌우 이동
                {
                    int nx = x+dx[ij];
                    int ny = y+dy[ij];

                    if(InRange(nx, ny))
                    {
                        if((!temp[nx][ny])&&(!visited[nx][ny]))
                        {
                            q.push({nx,ny});
                        }
                    }
                }
            }
        }
        if(max_count<num_count)
            max_count = num_count;
    }

    cout<<max_count;
    return 0;
}