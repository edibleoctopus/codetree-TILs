#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
/*
마름모 중앙 (a,b) 임의의 위치 (c,b)
|c-a| + |d-b| <= k면 마름모에 포함됨.

k의 범위 
좌측 상단과 우측 하단이 커버할 수 있게 해야함. 
2*(N-1까지 커져야함.)

*/
bool InRange(int x,int y, int n)
{
    return (x>=0 && y>=0 && x<n && y<n);
}

int main() {
    // 여기에 코드를 작성해주세요.
    int n, m;
    cin>>n>>m; 
    vector<vector<int>> v1(n,vector<int>(n,0));
    //맵 저장
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
           cin>> v1[i][j];
        }
    }
    int max_gold=0; 
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
       
          for(int k=0;k<=2*n-1;k++)
          {
            int num_gold = 0;
            for(int x=0;x<n;x++)
            {
                for(int y =0; y<n;y++)
                {
                    if((abs(x-i) + abs(y-j) <=k) && InRange(x, y, n))
                    {
                        num_gold += v1[x][y];
                    }
                }
            }
            if(num_gold * m >= (k * k + (k+1) * (k+1)))
            {
                max_gold = max(max_gold, num_gold);
            }
          }
        }
    }
    cout<<max_gold;
    return 0;
}