#include <bits/stdc++.h>
using namespace std;

int main()
{
    int q;
    scanf("%d", &q);
    
    //memset vector 0
    vector <int> v(q+1, 0);
    
    int a,b;
    while(cin>>a>>b)
    {
        v[a]++;
        v[b]++;
    }
    string s;
    cin>>s;
    int maks_nilai = -1;
    int maks_angka = -1;
    int mins_nilai = 10e6;
    int mins_angka = 10e6;
    for(int i=1; i<=q; i++)
    {
        if(v[i] > maks_nilai)
        {
            maks_nilai = v[i];
            maks_angka = i;
        }
        if(v[i] <= mins_nilai)
        {
            mins_nilai = v[i];
            mins_angka = i;
        }
    }
    printf("%d itu si Node Putih\n", maks_angka);
    printf("%d itu si Node Merah\n", mins_angka);
}

