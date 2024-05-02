#include <iostream>
#include <vector> 

using namespace std;

//xor 결과 최대 만들기(m 개 숫자를 뽑아 모두 XOR한 결과의 최댓값)
int n, m;
int answer=0;

vector<int> vt;
vector<int> select_i;
void Bactraking(int idx, int depth)
{
    if(idx > vt.size() || depth>m)//idx가 size를 넘거나, m개 이상 고르면 return
        return;

    if(depth == m)
    {
        //xor 수행
        int total = select_i[0];
        for(int i=1;i<select_i.size();i++)
        {
            total = total ^ select_i[i];
        }

        answer = max(answer, total);

        return;
    }

    select_i.push_back(vt[idx]);
    Bactraking(idx+1, depth+1);//넣고
    select_i.pop_back();
    Bactraking(idx+1, depth);//빼고

}

int main() {
    // 여기에 코드를 작성해주세요.
    cin>>n>>m;
    vt.resize(n);

    for(int i=0;i<n;i++)
    {
        cin>>vt[i];
    }

    Bactraking(0,0);
    cout<<answer;
    return 0;
}