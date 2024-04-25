#include <iostream>
#include <vector>
#include <queue>
#define MAX_N 100

using namespace std; 

int n, k, m; //맵 크기, 시작점 개수, 치울 돌 수
bool visited[MAX_N][MAX_N];//방문 여부
vector<vector<int>> mmap;//맵 정보
vector<pair<int, int>> rock;//돌이 있는 위치
vector<pair<int, int>> select_rock;//치울 돌이 있는 위치
queue<pair<int, int>> q;//BFS 진행용 큐
vector<pair<int, int>> s_pos;//시작 포인트 저장

bool InRange(int x, int y)//영역 안에 있는지 확인
{
    return (x>=0 && y>=0 && x<n && y<n);
}

bool CanGo(int x, int y) //영역 내에 있을 때도 갈 수 있는지 없는지 구분(방문 여부 + 돌인지아닌지)
{
    return ((!visited[x][y]) && (!mmap[x][y])); 
}

void BFS() //BFS 진행(이동 가능한 최대 거리 구하기)
{
    while(!q.empty())
    {
        int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0}; //동남서북 순서
        int x = q.front().first; 
        int y = q.front().second;

        q.pop(); 

        for(int i=0; i<4;i++)//동서 남북 이동
        {
            int nx = x+dx[i];
            int ny = y+dy[i]; 

            if(InRange(nx, ny))//영역 내에 있는지 확인
            {
                if(CanGo(nx, ny))//갈 수 있는지 없는지 확인
                {
                    visited[nx][ny] = true;//방문했다고 남기기
                    q.push({nx, ny}); //큐에 추가하기
                }
            }
        }
    }
}

int calc()//선택한 돌 제거, 얼마나 이동가능한지 BFS 실행, 선택한 돌 다시 돌려놓기
{
    //visited 초기화
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            visited[i][j] = false;
        }
    }

    //선택한 돌 제거
    for(int i=0;i<m;i++)
    {
        int x = select_rock[i].first;
        int y = select_rock[i].second;

        mmap[x][y] = 0; //돌 제거
    }


    for(int i=0;i<k;i++)//큐에 시작점 넣기
    {
        q.push(s_pos[i]);
        visited[s_pos[i].first][s_pos[i].second] = true; 
    }

    //BFS진행 
    BFS(); 

    //선택한 돌 다시 돌려놓기
    for(int i=0;i<m;i++)
    {
        int x = select_rock[i].first;
        int y = select_rock[i].second;

        mmap[x][y] = 1; //돌 넣기
    }

    //방문 여부에서 참인 것 세기 
    int ccount = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(visited[i][j])
                ccount++;
        }
    }
    return ccount;
}

int ans = 0;
void Find_max(int idx, int cnt) //백트래킹으로 제거할 돌 선택
{
    if(idx == rock.size())//모든 돌을 탐색했으면 탈출
    {
        if(cnt == m)//cnt와 치울 수 있는 돌의 개수 m과 같아지면 최대 이동 가능 경우인지 확인하기
            ans = max(ans, calc()); 

        return;
    }

    select_rock.push_back(rock[idx]);//돌 추가
    Find_max(idx+1, cnt+1);//현재 돌 추가했다는 가정하에 탐색
    select_rock.pop_back();//현재 돌 제거
    Find_max(idx+1, cnt);//현재 돌 제외하고 탐색
}

int main()
{
    cin>>n>>k>>m; 
    mmap.resize(n, vector<int>(n));

    //맵 정보 입력
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin >> mmap[i][j];
            if (mmap[i][j])
                rock.push_back({i,j});
        }
    }

    int r, c;

    for(int i=0;i<k;i++)
    {
        cin >> r>>c;
        r--, c--; 
        s_pos.push_back(make_pair(r,c));
    }
    //최대 이동 가능한 경우 찾기(idx : 돌 위치 최대 크기, cnt : 치울 돌 개수)
    Find_max(0,0);

    cout<<ans;
	return 0;
}