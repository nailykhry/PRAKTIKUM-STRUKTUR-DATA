#include <bits/stdc++.h>
using namespace std;

int jembatan, pulau, j_ada, node1, node2;


void DFS(int mulai, vector<int> v[], vector<int> &visited);

int main() 
{
    scanf("%d %d", &pulau, &j_ada);
    //simpan node dan node yg dituju
    vector<int> v[pulau+1];
    //yang dikunjungin, memset 0
    vector<int> visited(pulau+1,0);
    //masukkan data
    for(int i=0; i<j_ada; i++) 
    {
        //undirected makannya di bolak balik
        scanf("%d%d", &node1, &node2);
        v[node1].push_back(node2);
        v[node2].push_back(node1);
    }     
    //inisialisasi jembatan tambahan 0
    jembatan = 0;
    
    //ke-dfs
    for(int i=1; i<=pulau; i++) 
    {
        //blm dikunjungi
        if(visited[i] == 0 ) 
        {
            jembatan++;
            DFS(i,v,visited);
        }            
    }
    //output
    if(jembatan-1>0) printf("%d\n", jembatan-1); 
    else printf("HAIL ASEP!\n");  
    return 0;
}

void DFS(int mulai, vector<int> v[],vector<int> &visited) {
   //yg dipanggil ditandai dulu
    visited[mulai] = 1;
    
    //ukuran dari vector dari posisi itu
    int len = v[mulai].size();
    
    //cek
    for(int i= 0; i<len ; i++) 
    {  
        //kalau belum dikunjungi dikunjungi dengan dfs      
        if(visited[v[mulai][i]] == 0)
            DFS(v[mulai][i], v, visited);        
    }    
}
