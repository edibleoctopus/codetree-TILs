#include <iostream>
#include <vector>

/*
n * m크기의 이차원 영역의 각 위치에 정수 값이 하나씩 적혀있습니다.
이 영역 안에서 서로 겹치지 않는 두 직사각형을 적절하게 잡아, 두 직사각형 안에 적힌 숫자들의
총 합을 최대로 하는 프로그램을 작성해보세요. 이때, 각 직사각형의 변들은 격자 판에 평행해야 하고
꼭 2개의 직사각형을 골라야만 하며, 두 직사각형의 경계는 서로 닿아도 됩니다.
예를 들어 다음 그림의 경우에는, 두 직사각형을 적절히 잡아 합을 62 만큼 만들 수 있습니다.
*/
using namespace std;
bool InRange(int x, int y, int n, int m)
{
    return (x >= 0 && y >= 0 && x < n && y < m);
}

int main() {
    // 여기에 코드를 작성해주세요.
    int n, m;

    cin >> n >> m;
    vector<vector<int>>map(n, vector<int>(m, 0));
    vector<pair<int, int>> orr;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            orr.push_back({ i,j });
        }
    }

    //겹치지 않는 직사각형 2개 설정하기
    //먼저 하나 설정하고 차지 하는 부분 visited로 놓기
    //최대 변 길이 k가 필요
    int answer = -1000 * n * m;
    for (int i = 0; i < orr.size(); i++)//사각형 1 왼쪽 끝 x 좌표
    {
        for (int j = 0; j < orr.size(); j++)//사각형 1 왼쪽 끝 y좌표
        {
            int x1 = orr[i].first;
            int y1 = orr[i].second;
            int x2 = orr[j].first;
            int y2 = orr[j].second;
            vector<vector<bool>>visited(n, vector<bool>(m, false));//겹치지 않기 위한 도구
            if (x1 > x2)
                swap(x1, x2);
            if (y1 > y2)
                swap(y1, y2);
            int total = 0;

            //x2~x1, y2~y1은 사각형 1이 점령 중 
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    total += map[x][y];
                    visited[x][y] = true;
                }
            }
            //사각형 2가 점령 중
            for (int i2 = 0; i2 < orr.size(); i2++)//사각형 2 왼쪽 끝 x 좌표
            {
                for (int j2 = 0; j2 < orr.size(); j2++)//사각형 2 왼쪽 끝 y좌표
                {
                    int x3 = orr[i2].first;
                    int y3 = orr[i2].second;
                    int x4 = orr[j2].first;
                    int y4 = orr[j2].second;
                    if (x3 > x4)
                        swap(x3, x4);
                    if (y3 > y4)
                        swap(y3, y4);
                    //cout << "좌표 : [" << x1 << ' ' << y1 << "] [" << x2 << ' ' << y2 << "] [" << x3 << ' ' << y3 << "] [" << x4 << ' ' << y4 << "] \n";

                    int total2 =0;
                    bool poss = true;

                    for (int x5 = x3; x5 <= x4; x5++)
                    {
                        for (int y5 = y3; y5 <= y4; y5++)
                        {
                            if (visited[x5][y5])
                            {
                                poss = false;
                                break;
                            }
                            total2 += map[x5][y5];
                        }
                        if (!poss)
                            break;
                    }

                    if (poss)
                    {
                        int guess = total + total2;
                        //cout << "좌표 : [" << x1 << ' ' << y1 << "] [" << x2 << ' ' << y2 << "] [" << x3 << ' ' << y3 << "] [" << x4 << ' ' << y4 << "] \n";
                        //cout << total << ' ' << total2 << ' ' << guess << '\n';
                        answer = max(answer, guess);
                    }

                }
            }
            ///////
        }
    }

    cout << answer;
    return 0;
}