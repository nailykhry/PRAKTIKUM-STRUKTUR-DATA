#include <bits/stdc++.h>
using namespace std;

void DFS(int mulai, vector<int> v[], vector<int> &visited);
int panjang_node;

int main() 
{
    //mappin dulu
    map <string,int> mp;
    mp["A1"] = 1;
    mp["A2"] = 2;
    mp["A3"] = 3;
    mp["B1"] = 4;
    mp["B2"] = 5;
    mp["B3"] = 6;
    mp["C1"] = 7;
    mp["C2"] = 8;
    mp["C3"] = 9;
    
    //banyak hubungan
    int hub;
    scanf("%d",&hub);
    
    //simpan node dan node yg dituju
    vector<int> v[10];
    
    //yang dikunjungin, memset 0
    vector<int> visited(9,0);
    
    //masukkan data
    string s1, s2, s3;
    for(int i=0; i<hub; i++) 
    {
        //undirected makannya di bolak balik
        cin>>s1>>s2>>s3;
        
        v[mp[s1]].push_back(mp[s3]);
        v[mp[s3]].push_back(mp[s1]);
        
    }     
    
    //simpan banyak node yg ada
    vector<int>nodes;
    
    for(int i=1; i<=9; i++) 
    {
        if(visited[i] == 0 ) 
        {
            //inisialisasi
            panjang_node = 0;
            
            //panggil buat cek
            DFS(i,v,visited);
            //printf("%d\n", panjang_node);
            //hasil masuk ke vector
            nodes.push_back(panjang_node);
        }            
    }
    
    //output
    //banyak kemungkinan perkalian semua panjang connected component
    
    int ans = 0;
    int len = nodes.size();
    for(int i=0; i<len-1; i++)
    {
        for(int j=i+1 ; j<len; j++)
        {
            ans += (nodes[i]*nodes[j]);
        }
    }
    printf("%d\n", ans);
    return 0;
    
}

void DFS(int mulai, vector<int> v[],vector<int> &visited) 
{
    //tandai kunjungi
    visited[mulai] = 1;
    
    //tambah panjang
    panjang_node++;
    
    //cek yg belum dikunjungi
    int len = v[mulai].size();
    for(int i= 0; i<len ; i++) 
    {        
        if(visited[v[mulai][i]] == 0)
            DFS(v[mulai][i], v, visited);        
    }    
}
