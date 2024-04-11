#include <iostream>
#include <vector> 

using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n, t;
    cin >>n>>t;

    vector<int> convey(3*n,0);

    for(int i=0;i<3*n;i++)
    {
        cin>>convey[i];
    }

    for(int tt=0;tt<t;tt++)
    {
        int temp = convey[3*n-1];

        for(int i=3*n-1;i>0;i--)
        {
            convey[i] = convey[i-1];
        }
        convey[0] = temp;
    }

    for(int i=0;i<3*n;i++)
    {
        cout<<convey[i]<<' ';
        if(i==(n-1) || i==2*n-1)
        {
            cout<<'\n';
        }
    }
    return 0;
}