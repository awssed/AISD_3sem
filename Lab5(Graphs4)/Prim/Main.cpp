#include<iostream>
#include<vector>;
using namespace std;
#define INF 9999999
void Prim(int G[8][8], int V)
{
    int min = INT_MAX, amount_edge = 0, row = 0, col = 0;
    int* selected=new int [V];

    for (int i = 0; i < V; i++)
        selected[i] = false;

    selected[0] = true;

    while (amount_edge < V - 1) {
        min = INT_MAX;
        for (int i = 0; i < V; i++)
            if (selected[i])
                for (int j = 0; j < V; j++)
                    if (!selected[j] && G[i][j])
                        if (min > G[i][j]) {
                            min = G[i][j];
                            row = i;
                            col = j;
                        }
        cout << (row + 1) << " - " << col + 1 << " :  " << G[row][col] << endl;
        selected[col] = true;
        amount_edge++;
    }
}
void main()
{
    int Matrix[8][8] =
    {
        {0, 2, 0, 8, 2, 0, 0, 0 },
        {2, 0, 3, 10, 5, 0, 0, 0},
        {0, 3, 0, 0, 12, 0, 0, 7},
        {8, 10, 0, 0, 14, 3, 1, 0},
        {2, 5, 12, 14, 0, 11, 4, 8},
        {0, 0, 0, 3, 11, 0, 6, 0},
        {0, 0, 0, 1, 4, 6, 0, 9},
        {0, 0, 7, 0, 8, 0, 9, 0}
    };
    Prim(Matrix, 8);
}
