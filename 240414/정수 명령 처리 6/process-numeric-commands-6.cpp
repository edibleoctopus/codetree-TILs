#include <iostream>
#include <queue> 
#include <string>

using namespace std; 

int main() {
    // 여기에 코드를 작성해주세요.
    priority_queue<int> pq; 

    int n; //명령어의 가짓수N 
    cin>>n;
    string str;
    int x;
    for(int i=0;i<n;i++)
    {
        cin >>str;
        if(str=="push")
        {
            cin>>x;
            pq.push(x);
        }

        else if(str=="size")
            cout<<pq.size()<<'\n';

        else if(str=="empty")
        {
            if(pq.empty()) cout<<1<<'\n';
            else cout<<0<<'\n';
        }

        else if(str=="top")
            cout<<pq.top()<<'\n';

        else if (str=="pop")
        {
            x = pq.top();
            pq.pop();
            cout<<x<<'\n';
        }
    }

    return 0;
}