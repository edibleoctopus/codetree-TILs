#include <iostream>
#include <vector>
#include <cmath>

using namespace std; 

bool InRange(int x, int y, int n, int m)
{
    return (x>=0 && y>=0&& x<n && y<m);
}

int main() {
    // 여기에 코드를 작성해주세요.
    int n,m;

    cin >>n>>m;
    vector<vector<int>> mmap(n, vector<int>(m,0));
    vector<pair<int, int>> positive;//양수 좌표 저장

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>> mmap[i][j]; 

            if(mmap[i][j] > 0)//양수면 좌표 저장
                positive.push_back({i,j});
        }
    }
    if(positive.size()==0)
    {
        cout<<-1;
        return 0;
    }
        
    int answer = 1;
    //저장된 양수 좌표 중 두개 고르기 
    for(int i=0;i<positive.size();i++)//x번
    {
        for(int j=i+1;j<=positive.size();j++)//y번
        {
            int x1 = positive[i].first;
            int y1 = positive[i].second;

            int x2 = positive[j].first;
            int y2 = positive[j].second;
            
            if(x1>x2)
                swap(x1, x2);

            if(y1>y2)
                swap(y1, y2);

            bool sq = true; 

            for(int x=x1;x<=x2;x++)//그 사이가 양수인지 음수인지 판별
            {
                for(int y=y1;y<=y2;y++)
                {   
                    if(InRange(x,y,n,m))
                    {
                        if(mmap[x][y] < 0) //음수 일때,
                        {
                            sq = false;
                            break;
                        }       
                    }

                    else
                    {
                        sq = false;
                        break;
                    }
                if(!sq)
                    break;       
                }
                if(!sq)
                    break;
            }
           
            if(sq)
            {
                int answer2 = answer;
                answer = max(answer, abs(x1-(x2+1))*abs(y1-(y2+1)));           
            }
            }
    }
    cout<<answer;

    return 0;
}