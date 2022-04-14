#include <cstdio>

int T,n,ans;

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ans = 0;
        for(int i = 1,x;i <= n;i++)
        {
            scanf("%d",&x);
            ans ^= x;
        }
        printf("%s\n",ans ? "Yes" : "No");
    }
    return 0;
}