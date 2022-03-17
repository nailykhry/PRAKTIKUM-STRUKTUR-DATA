//jumlah pulau
#include <bits/stdc++.h>
using namespace std;

int arr[10][10];
void fill(int x, int y);
int sum;

int main()
{
    
    for(int i=1; i<=5; i++)
    {
        for(int j=1; j<=5; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    
    for(int i=1; i<=5; i++)
    {
        for(int j=1; j<=5; j++)
        {
            if(arr[i][j]==1)
            {
                fill(i,j);
                sum++;
            }
        }
    }
    printf("Jumlah pulau Andromeda: %d\n", sum);
}

void fill(int x,  int y)
{
    arr[x][y]=0;
    
    if(x-1 > 0)
    {
        if(y-1 > 0)
        {
            if(arr[x-1][y-1]==1) fill(x-1, y-1);
        }
        if(y+1 < 6)
        {
            if(arr[x-1][y+1]==1) fill(x-1, y+1);
        }
        if(arr[x-1][y]==1) fill(x-1, y);
    }
    if(x+1 < 6)
    {
        if(y-1 > 0)
        {
            if(arr[x+1][y-1]==1) fill(x+1, y-1);
        }
        if(y+1 < 6)
        {
            if(arr[x+1][y+1]==1) fill(x+1, y+1);
        }
        if(arr[x+1][y]==1) fill(x+1, y);
    }
    if(y-1 > 0)
    {
        if(arr[x][y-1]==1) fill(x, y-1);
    }
    if(y+1 < 6)
    {
        if(arr[x][y+1]==1) fill(x, y+1);
    }
}
