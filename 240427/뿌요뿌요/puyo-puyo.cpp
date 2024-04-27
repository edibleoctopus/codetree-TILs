#include <iostream>
#include <vector>
using namespace std;
/*
n*n 크기의 격자에 1이상 100이하의 숫자 주어짐
상하좌우로 인접한 칸끼리 숫자로 이루어져있는 경우 하나의 블럭으로 생각
4개 이상이면, 해당 블럭은 터지게 됨
터지게 되는 블럭 수, 최대 블럭의 크기를 구하는 프로그램
*/

int n; 
vector<vector<int>> mmap;
vector<vector<bool>> visited; 

bool InRange(int x, int y)
{
	return (x >= 0 && y >= 0 && x < n && y < n);
}
//상하좌우 검색, 만약 자기 숫자와 같으면 num++ 만약 num++가 4가 넘으면 터지기

bool cango(int x, int y, int nx, int ny)
{
	return (InRange(nx, ny) && mmap[x][y] == mmap[nx][ny] && !visited[nx][ny]); //같은 숫자여야 하고, 영역 내에 있어야 한다.
}
int num;
void DFS(int x, int y)
{
	//지금에서 만약 4개가 넘으면 터지는 블럭 수, 가장 많이 터진 블럭 수 
	//현재는 최다로 터진 블럭수를 출력하고 있음 위에 것으로 수정해야함.
	visited[x][y] = true;//방문 도장 쾅
	
	int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};//동 남 서 북 
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (cango(x, y, nx, ny))
		{
			num++;
			DFS(nx, ny);
		}
	}
}
int ans = 1;
int max_n=0;
int main()
{
	cin >> n; 
	mmap.resize(n, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> mmap[i][j];
		}
	}
	visited.assign(n, vector<bool>(n, false));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			num = 1;
			
			DFS(i, j);

			if (num==1)
				continue;
		
			ans = max(ans, num);
			if (num > 3)
			{
				max_n++;
			}
		}
	}
		
	cout << max_n<< ' ' << ans;

	return 0;
}