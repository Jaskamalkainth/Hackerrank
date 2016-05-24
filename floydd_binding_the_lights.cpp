#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


const int maxN = 407;
int dist[maxN][maxN];
int main() {
    int n , m; cin >> n >> m;
    
    for(int i= 0; i < n; i++)
            for(int j = 0; j < n; j++)
        {
        if(i==j)
            dist[i][j] = 0;
        else
                dist[i][j] = 99999;
    }
    
    for(int i = 0 ; i < m; i++)
        {
        int u , v , wt; cin >> u >> v >> wt;
        u--;v--;
        dist[u][v] = wt;
    }
        
    for(int k = 0; k < n; k++)
        for(int i= 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k]+dist[k][j];
                
        
    int q; cin >> q;
    while(q--)
        {
        int u , v; cin >>u >> v;
        u--;v--;
        if(dist[u][v] == 99999)
            cout<<-1<<"\n";
        else
        cout<<dist[u][v]<<"\n";
    }
    return 0;
}

