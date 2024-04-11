#include <iostream>
#include <vector> 

using namespace std; 

/*
대각선으로 움직이며 반시계 순회를 했을 때 지나왔던 지점들의 집합
반드시 아래에서 시작해서 (오위, 왼위, 왼아래, 오아래)방향 순으로 순회해야하며, 각 방향으로 최소 1번은 움직여야 함. 
이동 중 격자 밖으로 넘어가면 안됨. 

가능한 기울어진 직사각형들 중 해당 직사각형을 이루는 지점에 적힌 숫자들의 합이 
최대가 되도록 하는 프로그램을 작성해보세요.

위의 예에서는 다음과 같이 기울어진 직사각형을 잡게 되었을 때 합이 21이 되어 최대가 됩니다.


*/

bool InRange(int x, int y, int n)
{
    return (x>=0 && x<n && y>=0 && y<n);
}

int main() {
    // 여기에 코드를 작성해주세요.
    int n; 
    cin>>n;
    vector<vector<int>> v1(n, vector<int>(n,0));
    for(int i=0;i<n;i++)//map 정보 입력 
    {
        for(int j=0;j<n;j++)
        {
            cin>>v1[i][j];
        }
    }

    //1, 3 의 길이, 2, 4의 길이는 같아야함.
    //특정 지점에서 시작(1의 시작 위치)
    //만약 진행중 격자 밖을 벗어나면 무효
    //k(변의 길이)의 최대 값은 n

    int max_k = n;
    int dx[ ]={-1,-1,1,1},dy[] = {1,-1,-1,1}; 
    int answer = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {        
            for(int k1=1;k1<max_k;k1++)//
            {
                for(int k2=1;k2<max_k;k2++)//
                {
                    bool possible = true;
                    int total = 0;
                    int x = i,  y = j;
                    for(int d=0;d<4;d++)//1, 2, 3, 4 과정
                    {
                        int k;
                        if(d%2==0)//1,3 과정
                            k = k1;
                        else 
                            k = k2;//2, 4 과정

                    for(int z = 0;z<k;z++)//해당 과정만큼 반복
                    {
                        int nx = x+dx[d], ny = y+dy[d]; 
                        if(InRange(nx, ny,n))
                        {
                            total+=v1[nx][ny];
                            x = nx, y=ny;
                        }
                        else
                            possible=false;

                        if(!possible)
                                break;
                    }    
                        if(!possible)
                                break;
                    }
                    if(possible)    
                        answer = max(total, answer);    
                }
            }        
        }
    }
    cout<<answer;
    //i, j -> 1(i-1 j+1)...(i-(k1-1) j+(k1-1)),->2(i-(k1-1) j+(k1-1)...i-(k1-1)-(k2-1), j+(k1-1)-(k2-1)) 

    return 0;
}