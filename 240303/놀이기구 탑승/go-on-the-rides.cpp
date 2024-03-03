#include <iostream>
#include <math.h>

using namespace std;
int main() {
    // 여기에 코드를 작성해주세요.
    int n;
    cin >> n;

    int seq[n * n * 5] = { 0, };
    for (int i = 0; i < n * n * 5; i++)
        cin >> seq[i];

    // fill student to ride
    int ride[n * n] = { 0, };
    for (int i = 0; i < n * n; i++) // iterate students
    {
        int map[n * n] = { 0, }; // affinity map
        for (int y = 0; y < n; y++) // iterate row
        {
            for (int x = 0; x < n; x++)  // iterate col
            {
                if (ride[y * n + x] != 0)  // occupied
                    continue;

                // condition 3, 4
                map[y * n + x] += n * n - (y * n + x);
                if (y > 0)
                    if (ride[(y-1) * n + x] == 0) // condition 2
                        map[y * n + x] += 1000;
                    else
                        for (int j = 1; j < 5; j++)
                            if (ride[(y-1) * n + x] == seq[i * 5 + j]) // condition 1
                                map[y * n + x] += 10000;

                if (y < n-1)
                    if (ride[(y+1) * n + x] == 0)
                        map[y * n + x] += 1000;
                    else
                        for (int j = 1; j < 5; j++)
                            if (ride[(y+1) * n + x] == seq[i * 5 + j]) // condition 1
                                map[y * n + x] += 10000;

                if (x > 0)
                    if (ride[y * n + (x-1)] == 0)
                        map[y * n + x] += 1000;
                    else
                        for (int j = 1; j < 5; j++)
                            if (ride[y * n + (x-1)] == seq[i * 5 + j]) // condition 1
                                map[y * n + x] += 10000;

                if (x < n-1)
                    if (ride[y * n + (x+1)] == 0)
                        map[y * n + x] += 1000;
                    else
                        for (int j = 1; j < 5; j++)
                            if (ride[y * n + (x+1)] == seq[i * 5 + j]) // condition 1
                                map[y * n + x] += 10000;

            }
        }

        // for (int y = 0; y < n; y++)
        // {
        //     for (int x = 0; x< n; x++){
        //         cout << map[y * n + x] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;

        // max(map)
        int max_idx = -1;
        int max_num = -1;
        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < n; x++)
            {
                if (map[y * n + x] > max_num)
                {
                    max_num = map[y * n + x];
                    max_idx = y * n + x;
                }
            }
        }

        ride[max_idx] = seq[i * 5];
    }

    // for (int y = 0; y < n; y++)
    // {
    //     for (int x = 0; x< n; x++){
    //         cout << ride[y * n + x] << " ";
    //     }
    //     cout << endl;
    // }

    // sum score
    int score = 0;
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            // find idx of student
            int idx = 0;
            for (idx = 0; idx < n * n; idx++)
                if (ride[y * n + x] == seq[idx * 5])
                    break;

            int num = 0;
            if (y > 0)
                for (int j = 1; j < 5; j++)
                    if (ride[(y-1) * n + x] == seq[idx * 5 + j])
                        num += 1;
            if (y < n-1)
                for (int j = 1; j < 5; j++)
                    if (ride[(y+1) * n + x] == seq[idx * 5 + j])
                        num += 1;
            if (x > 0)
                for (int j = 1; j < 5; j++)
                    if (ride[y * n + (x-1)] == seq[idx * 5 + j])
                        num += 1;
            if (x < n-1)
                for (int j = 1; j < 5; j++)
                    if (ride[y * n + (x+1)] == seq[idx * 5 + j])
                        num += 1;

            if (num > 0)
                score += pow(10, num-1);
        }
    }

    cout << score;

    return 0;
}