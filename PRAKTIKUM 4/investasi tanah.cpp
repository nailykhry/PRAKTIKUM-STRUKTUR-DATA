//hist
#include <bits/stdc++.h>
using namespace std;

int x, y, xA, xB, yA, yB, t, n;
int rec[205][205];

int maxHist(int baris);
int luas_akhir();


int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d%d", &x, &y, &n);
        for(int i=1; i<=x; i++)
        {
            for(int j=1; j<=y; j++)
            {
                rec[i][j] = 1;
            }
        }
        
        //yang bisa 1 yg gabisa 0
        while(n--)
        {
            scanf("%d %d %d %d", &xA, &yA, &xB, &yB);
            for(int i=xA; i<=xB; i++)
            {
                for(int j=yA; j<=yB; j++)
                {
                    rec[i][j] = 0;
                }
            }
        }
        /*for(int i=1; i<=x; i++)
        {
            for(int j=1; j<=y; j++)
            {
                printf("%d ", rec[i][j]);
            }
            printf("\n");
        }*/
        printf("%d\n", luas_akhir());
    }
    return 0;
}


int luas_akhir()
{
    //luas awal
    int luas = maxHist(1);

    // beri nilai tinggi pada setiap array. (hist)
    for (int i = 2; i <= x; i++) 
    {
        for (int j = 1; j <= y; j++)
        {
            //kalau 1
            if (rec[i][j]) rec[i][j] += rec[i - 1][j];
        }
        //update luas
        luas = max(luas, maxHist(i));
    }

    return luas;
}

int maxHist(int baris)
{
    //simpan index 
    stack<int> idx;

    //top stack isi panjang vertical
    int atas;

    //untuk simpan maksimal luas
    int max_luas = 0; 

    //luas sementara
    int luas = 0;

    int i = 0;
    
    while (i <= y) 
    {
        //kalo lebih besar sama dengan bakal dimasukin stack
        if (idx.empty() || rec[baris][idx.top()] <= rec[baris][i])
            idx.push(i++);

        else 
        {
            // kalau dia lebih kecil artinya kena 0 lebih banyak
            // i nya posisi paling kanan
            atas = rec[baris][idx.top()];
            idx.pop();
            luas = atas * i;
            
            //kalau masi ada cek sebelumnya
            if (!idx.empty())
                luas = atas * (i - idx.top() - 1);
                
            max_luas = max(luas, max_luas);
        }
    }
    
    // pop sisa yg ada di stack
    while (!idx.empty()) 
    {
        atas = rec[baris][idx.top()];
        idx.pop();
        luas = atas * i;
        if (!idx.empty())
            luas = atas * (i - idx.top() - 1);
            
        max_luas = max(luas, max_luas);
    }
    return max_luas;
}

