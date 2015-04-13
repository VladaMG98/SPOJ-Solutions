/*
Vladimir "VladaMG98" Milenkovic
Using Heavy-Light decomposition for finding LCA
graf[i].parent[j] is 2^j-th parent of node i
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN=10010;
const int LOGN=20;
const int COMMAND=10;
int n;
char s[COMMAND];
int idx[MAXN];
struct Node
{
    vector<int> adj;
    vector<int> weg;
    int parent[20];
    int dist;
    int depth;
};
Node graf[MAXN];
struct TreeNode
{
    int parent;
    int depth;
    int chainTop;
    int subTreeSize;
};
TreeNode T[MAXN];
int DFS(int root, int parent, int depth)
{
    T[root].parent = parent;
    T[root].depth = depth;
    T[root].subTreeSize = 1;
    for (int i=0; i<graf[root].adj.size(); i++)
    {
        int xt = graf[root].adj[i];
        if (xt == parent) continue;
        T[root].subTreeSize += DFS(xt, root, depth+1);
    }
    return T[root].subTreeSize;
}
void HLD(int root, int parent, int chainTop)
{
    T[root].chainTop = chainTop;

    for (int i=0; i<graf[root].adj.size(); i++)
    {
        int xt = graf[root].adj[i];
        if (xt == parent) continue;
        if (T[xt].subTreeSize*1.0 > T[root].subTreeSize*0.5) HLD(xt, root, chainTop);
        else HLD(xt, root, xt);
    }
}
inline int LCA(int u, int v)
{
    while (T[u].chainTop != T[v].chainTop)
    {
        if (T[T[u].chainTop].depth < T[T[v].chainTop].depth) v = T[T[v].chainTop].parent;
        else u = T[T[u].chainTop].parent;
    }
    if (T[u].depth < T[v].depth) return u;
    else return v;
}
void dfs(int src,int last,int dis,int dep)
{
    graf[src].dist=dis;
    graf[src].depth=dep;
    graf[src].parent[0]=last;
    for(int i=1; i<LOGN; i++)
    {
        graf[src].parent[i]=graf[graf[src].parent[i-1]].parent[i-1];
    }
    for(int i=0; i<graf[src].adj.size(); i++)
    {
        if(graf[src].adj[i]==last) continue;
        dfs(graf[src].adj[i],src,dis+graf[src].weg[i],dep+1);
    }
}
int par(int k,int v)
{
    int ret=v;
    while(k)
    {
        int nxt=k&-k;
        k-=nxt;
        ret=graf[ret].parent[idx[nxt]];
    }
    return ret;
}
int precalc()
{
    int to=1;
    for(int i=0; to<MAXN; i++)
    {
        idx[to]=i;
        to*=2;
    }
}
int main()
{
    precalc();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0; i<=n; i++)
        {
            graf[i].adj.clear();
            graf[i].weg.clear();
            T[i].parent=T[i].depth=T[i].chainTop=T[i].subTreeSize=0;
            for(int j=0; j<LOGN; j++) graf[i].parent[j]=0;
        }
        for(int i=0; i<n-1; i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            graf[u].adj.push_back(v);
            graf[v].adj.push_back(u);
            graf[u].weg.push_back(w);
            graf[v].weg.push_back(w);
        }
        DFS(1,1,0);
        HLD(1,1,1);
        dfs(1,0,0,0);
        while(true)
        {
            int u,v,k;
            scanf("%s",s);
            if(s[1]=='O') break;
            else if(s[1]=='I')
            {
                scanf("%d%d",&u,&v);
                int lca=LCA(u,v);
                printf("%d\n",graf[u].dist+graf[v].dist-2*graf[lca].dist);
            }
            else
            {
                scanf("%d%d%d",&u,&v,&k);
                --k;
                int lca=LCA(u,v);
                int depa=graf[u].depth;
                int depb=graf[v].depth;
                int depl=graf[lca].depth;
                if(k<=depa-depl) printf("%d\n",par(k,u));
                else printf("%d\n",par((depb-depl)-(k-(depa-depl)),v));
            }
        }
    }
    return 0;
}
