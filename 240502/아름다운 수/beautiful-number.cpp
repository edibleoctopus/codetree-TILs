#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n;
int cnt = 0;
vector<int> vt;

bool isBeautiful() {
    int prev = -1;
    int count = 0;

    for (int i = 0; i < vt.size(); i++) {
        if (vt[i] != prev)//이전 값과 같지 않으면 초기화
        {
            if (prev != -1 && count != prev)//-1이 아니면서 count가 prev와 같지 않으면 false
                return false;

            prev = vt[i];
            count = 1;
        }

        else//같으면 count
        {
            count++;
        }
    }
    return count == prev;
}

bool isBeauti2()
{
    int prev = -1;
    int count = 0;

    for (int i = 0; i < vt.size(); i++)
    {
        if (vt[i] != prev)
        {
            if (prev != -1 && (count % prev != 0))//맨 처음이 아니면서, prev의 배수만큼 count가 안나왔다면 false
                return false;

            prev = vt[i];
            count = 1;
        }

        else
            count++;
    }

    if (count % prev == 0)//맨 처음이 아니면서, prev의 배수만큼 count가 안나왔다면 false
        return true;

    else
        return false;

    
}

void backtrack(int depth) {
    if (depth == n) {
        if (isBeautiful() || isBeauti2())
            cnt++;
        return;
    }

    for (int i = 1; i <= 4; i++) {//1~4까지 반복
        vt.push_back(i);
        backtrack(depth + 1);
        vt.pop_back();
    }
}

int main() {
    cin >> n;
    backtrack(0);
    cout << cnt;
    return 0;
}