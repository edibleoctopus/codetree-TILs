#include <iostream>
#include <vector>
#include <algorithm>

using namespace std; 

//특정 위치 선택시 그 위치를 중심으로 십자 모양으로 폭탄이 터지게 됨. 
//십자 모양의 크기는 선택된 위치에 적혀있는 숫자로 정해짐, 터진 이후에는 중력에 의해 숫자들이 
//아래로 떨어지게 된다. 
//지정 위치 상하좌우 + n-1만큼 터진다.

int main() {
    // 여기에 코드를 작성해주세요.
    int n;
    cin>>n; 
    vector<vector<int>> v1(n, vector<int>(n,0));
    //맵정보 저장
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>v1[i][j];
        }  
    }

    //폭발 구현
    pair<int, int> bomb;//폭탄 좌표
    int x, y;
    cin>>bomb.first>>bomb.second;
    x = bomb.first-1;
    y = bomb.second-1;

    int k = v1[x][y];//폭탄에 써있는 번호

    int dx[] = {-1,0,1,0}, dy[] = {0,1,0,-1};//북, 동, 남, 서 순서

    int min_vic_x = max(x-(k-1), 0);//삭제할 좌표 저장(북) 자기 자신~ +k-1 까지
    int max_vic_x = min(x+(k-1), n-1);//삭제할 좌표 저장(남) 자기 자신~ +k-1 까지

    int min_vic_y = max(y-(k-1), 0);//삭제할 좌표 저장(서) 자기 자신~ +k-1 까지
    int max_vic_y = min(y+(k-1), n-1);//삭제할 좌표 저장(동) 자기 자신~ +k-1 까지

    //폭발
    for(int j=min_vic_y;j<=max_vic_y;j++)//y
    {
        v1[x][j] = 0;
    }

    for(int j=min_vic_x;j<=max_vic_x;j++)//x
    {
        v1[j][y] = 0;
    } 

    //중력 구현 
   
    for(int i=0;i<n;i++)//열 고르기
    {
        int temp[n] ={0,};
        int end_of_temp = 0;

        for(int j=0;j<n;j++)//열의 원소 고르기
        {
            if(v1[n-1-j][i] == 0)//삭제된 부분
                continue;
            temp[end_of_temp] = v1[n-1-j][i];
            end_of_temp++;
        }
        
        for(int j=n-1;j>=0;j--)//대체하기
        {
           v1[n-1-j][i] = temp[j];
        } 
        
        
    } 

    //출력 
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<v1[i][j]<<' ';
        }  
        cout<<'\n';
    }
    return 0;
}