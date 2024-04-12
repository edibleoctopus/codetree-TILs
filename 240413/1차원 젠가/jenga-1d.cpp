#include <iostream>
#include <vector>
/*
n개의 층으로 이루어진 1차원 젠가의 상태가 주어집니다. 
각 층마다 1개의 블럭이 놓여져 있고, 
각 블럭에는 1이상 100 이하의 숫자가 하나씩 적혀있습니다.
이 때 2번에 걸쳐 특정 구간의 블럭들을 빼는 작업을 진행하려 합니다.

처음에 위에서부터 2번째 블럭에서 4번째 블럭까지 블럭을 빼게 된다면, 
남은 블럭은 중력에 의해 떨어지게 되어 다음과 같이 블럭이 남게 됩니다.

특정 구간의 블럭을 두 번 빼는 과정을 거친 이후의 결과를 출력하는 프로그램을 작성해보세요.


*/

using namespace std; 

int main() {
    // 여기에 코드를 작성해주세요.
    int n;//총 젠가 수
    cin>>n; 

    vector<int> arr(n);//arr : 기존 배열 
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];//6 1 2 3... 5
    }
    int s1, s2, e1, e2;//뺄 젠가 입력 받기 
    cin>>s1>>e1>>s2>>e2;

    vector<int> temp(n);//temp 배열 선언
    int end_of_array = n; 
    int end_of_temp_array = 0; 

    for(int i=0;i<end_of_array;i++)
    {
        if((i>=s1-1 && i<e1))//빠지는 젠가들
        {
            continue;
        }
        temp[end_of_temp_array] = arr[i];
        end_of_temp_array++;  
    }

    for(int i=0;i<end_of_temp_array;i++)
    {
        arr[i] = temp[i];
    }

    end_of_array = end_of_temp_array;
    end_of_temp_array = 0; 

    for(int i=0;i<end_of_array;i++)
    {
        if((i>=s2-1 && i<e2))//빠지는 젠가들
        {
            continue;
        }
        temp[end_of_temp_array] = arr[i];
        end_of_temp_array++;  
    }
    cout<<end_of_temp_array<<'\n';
    for(int i=0;i<end_of_temp_array;i++)
    {
        arr[i] = temp[i];
        cout<<arr[i]<<'\n';
    }

    return 0;
}