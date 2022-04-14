#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

#define N 10010
#define M 100100

using std::min;

int n,m,a[N];
int h[N],e[M << 1],ne[M << 1],idx;
int scch[N],scce[M << 1],sccne[M << 1],sccidx;
int sccru[N];
void add(int x,int y)
{
    ne[++idx] = h[x];
    h[x] = idx;
    e[idx] = y;
}

void sccadd(int x,int y)
{
    sccne[++sccidx] = scch[x];
    scch[x] = sccidx;
    scce[sccidx] = y;
    sccru[y]++;
}

int dfn[N],dfncnt,low[N],scc[N],scca[N],sc,sz[N];
int st[N],top,in_stack[N];
void tarjan(int k)
{
    dfn[k] = low[k] = ++dfncnt;
    st[++top] = k;
    in_stack[k] = 1;
    for(int i = h[k];~i;i = ne[i])
    {
        int nx = e[i];
        if(!dfn[nx])
        {
            tarjan(nx);
            low[k] = min(low[k],low[nx]);
        }
        else if(in_stack[nx])
            low[k] = min(low[k],dfn[nx]);
    }
    if(low[k] == dfn[k])
    {
        sc++;
        while(1)
        {
            int v = st[top];
            top--;
            scc[v] = sc;
            sz[sc]++;
            scca[sc] += a[v];
            in_stack[v] = 0;
            if(v == k)
                break;
        }
    }
}

int ans,dp[N];
std::queue <int> q;
void toposort()
{
    for(int i = 1;i <= sc;i++)
        if(!sccru[i])
        {
            q.push(i);
            dp[i] = scca[i];
        }
    while(!q.empty())
    {
        int t = q.front();
        q.pop();
        for(int i = scch[t];~i;i = sccne[i])
        {
            int nx = scce[i];
            dp[nx] = std::max(dp[nx],dp[t] + scca[nx]);
            sccru[nx]--;
            if(!sccru[nx])
                q.push(nx);
        }
    }
    for(int i = 1;i <= sc;i++)
        ans = std::max(ans,dp[i]);
}

int main()
{
    memset(h,-1,sizeof(h));
    memset(scch,-1,sizeof(scch));
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++)
        scanf("%d",&a[i]);
    for(int i = 1,x,y;i <= m;i++)
    {
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    for(int i = 1;i <= n;i++)
        if(!dfn[i])
            tarjan(i);
    for(int i = 1;i <= n;i++)
    {
        for(int j = h[i];~j;j = ne[j])
        {
            int nx = e[j];
            if(scc[i] != scc[nx])
                sccadd(scc[i],scc[nx]);
        }
    }
    toposort();
    printf("%d\n",ans);
    return 0;
}