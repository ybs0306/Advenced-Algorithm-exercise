#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
 
const int N = 501;
const int INF = 10000000;
 
struct node
{
    int to, cost;
};
 
vector<node> edge[N];
int dis_s[N], dis_e[N];
int parent_s[N], parent_e[N];
 
void Dijkstra(int n, int s, int dis[], int parent[])
{
    bool vis[N];
 
    for(int i = 1; i <= n; i ++)
    {
        dis[i] = INF;
        vis[i] = false;
    }
    dis[s] = 0;
    parent[s] = s;
 
    int u, min;
    for(int t = 1; t <= n; t ++)
    {
        u = 0, min = INF;
 
        for(int i = 1; i <= n; i ++)
        {
            if(!vis[i] && dis[i] < min)
            {
                min = dis[i];
                u = i;
            }
        }
 
        vis[u] = true;
 
        for(int i = 0; i < edge[u].size(); i ++)
        {
            int v = edge[u][i].to, w = edge[u][i].cost; 
 
            if(!vis[v] && dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                parent[v] = u;
            }
        }
 
    }
}
 
int main()
{
    int N, S, E, m, k;
    int x, y, cost;
    bool flag = false;
 
    while(cin >> N >> S >> E)
    {
        for(int i = 1; i <= N; i ++)
            edge[i].clear();
 
        cin >> m;
        while(m --)
        {
            cin >> x >> y >> cost;
            edge[x].push_back((node){y, cost});
            edge[y].push_back((node){x, cost});
        }
 
        Dijkstra(N, S, dis_s, parent_s);
        Dijkstra(N, E, dis_e, parent_e);
 
        cin >> k;
 
        int distance = dis_s[E];
        int ts = 0, te = 0;
 
        while(k --)
        {
            cin >> x >> y >> cost;
            if(dis_s[x] + cost + dis_e[y] < distance)
            {
                distance = dis_s[x] + cost + dis_e[y];
                ts = x, te = y;
            }
            if(dis_s[y] + cost + dis_e[x] < distance)
            {
                distance = dis_s[y] + cost + dis_e[x];
                ts = y, te = x;
            }
        }
 
        int station = ts;
 
        if(flag) cout << "\n";
        flag = true;
 
        if(ts == 0 && te == 0)
        {
            while(S != E)
            {
                cout << S << " ";
                S = parent_e[S];
            }
            cout << E << "\n";
        }
        else
        {
            int buffer[N];
            int index = 0;
 
            while(ts != S)
            {
                buffer[index ++] = ts;
                ts = parent_s[ts];
            }
            buffer[index ++] = S;
 
            for(int i = index - 1; i >= 0; i --)
                cout << buffer[i] << " ";
 
            while(te != E)
            {
                cout << te << " ";
                te = parent_e[te];
            }
            cout << E << "\n";
        }
 
        if(station == 0)
            cout << "Ticket Not Used\n";
        else
            cout << station << "\n";
 
        cout << distance << "\n";
    }
 
    return 0;
}
