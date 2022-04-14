#include <cstdio>

#define N 3000010

int n,a[N],s[N],f[N],top;

int main()
{
    scanf("%d",&n);
    for(int i = 1;i <= n;i++)
        scanf("%d",&a[i]);
    for(int i = n;i >= 1;i--)
    {
        while(top && a[s[top]] <= a[i])
            top--;
        f[i] = s[top];
        s[++top] = i;
    }
    for(int i = 1;i <= n;i++)
        printf("%d ",f[i]);
    return 0;
}