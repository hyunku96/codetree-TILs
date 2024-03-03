#include <iostream>

using namespace std;
int main() {
    // 여기에 코드를 작성해주세요.
    int n, L, R;
    cin >> n >> L >> R;

    int eggs[n * n] = { 0, };
    for (int i = 0; i < n * n; i++)
        cin >> eggs[i];

    int dx[4] = {0, 1, 0, -1}; // up, right, down, left
    int dy[4] = {-1, 0, 1, 0}; // up, right, down, left
    int max_len = n * n;

    int cnt = 0;
    while (true)
    {
        int q[max_len] = { 0, };
        int inp_idx = 0;
        int out_idx = 0;
        int visited[n * n] = { 0, }; // 1: visited, 0: non-visited        
        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < n; x++)
            {
                if (visited[y * n + x] == 1)
                    continue;
                else
                {
                    int neighbors[n * n] = { 0, };
                    int cnt_neighbor = 0;
                    int cur_x = x;
                    int cur_y = y;

                    while(true)
                    {
                        visited[cur_y * n + cur_x] = 1;

                        // input queue
                        for (int d = 0; d < 4; d++)
                        {
                            if (cur_y + dy[d] > -1 && cur_y + dy[d] < n 
                            && cur_x + dx[d] > -1 && cur_x + dx[d] < n) // check boundary
                            {
                                if (visited[(cur_y + dy[d]) * n + (cur_x + dx[d])] != 1)
                                {
                                    int diff = abs(eggs[cur_y * n + cur_x] - eggs[(cur_y+dy[d]) * n + (cur_x+dx[d])]);
                                    if (diff >= L && diff <= R && diff != 0)
                                    {
                                        q[inp_idx] = (cur_y + dy[d]) * n + (cur_x + dx[d]);
                                        inp_idx = (inp_idx + 1) % max_len;
                                    }                                
                                }                                                   
                            }
                        }

                        // store current idx
                        neighbors[cnt_neighbor] = cur_y * n + cur_x;
                        cnt_neighbor++;

                        if (out_idx == inp_idx)  // queue is empty
                            break;

                        // output queue
                        cur_y = q[out_idx] / n;
                        cur_x = q[out_idx] % n;
                        out_idx = (out_idx + 1) % max_len;
                    }                    

                    int sum = 0;
                    for (int j = 0; j < cnt_neighbor; j++)
                        sum += eggs[neighbors[j]];
                    for (int j = 0; j < cnt_neighbor; j++)
                        eggs[neighbors[j]] = sum / cnt_neighbor;
                }
            }
        }

        // if no transition, then break
        if (inp_idx == 0 && out_idx == 0)
            break;
        
        cnt++;
    }

    cout << cnt;

    return 0;
}