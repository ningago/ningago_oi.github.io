#include <cstdio>

#define N 100010
#define lson(x) (tr[x].s[0])
#define rson(x) (tr[x].s[1])
struct FHQ_TREAP
{
	int s[2];
	int val,key;
	int size;
}tr[N];
int root,idx;

unsigned int sd = 233;
inline int rnd()
{
	sd ^= sd << 13;
	sd ^= sd >> 7;
	sd ^= sd << 11;
	return (int)sd;
}

inline int newnode(int val)
{
	tr[++idx].val = val;
	tr[idx].key = rnd();
	tr[idx].size = 1;
	return idx;
}

inline void pushup(int k)
{
	tr[k].size = tr[lson(k)].size + tr[rson(k)].size + 1;
}

void split(int k,int val,int &x,int &y)
{
	if(!k)
		x = y = 0;
	else
	{
		if(tr[k].val <= val)
		{
			x = k;
			split(rson(k),val,rson(k),y);
		}
		else
		{
			y = k;
			split(lson(k),val,x,lson(k));
		}
		pushup(k);
	}
}

int merge(int x,int y)
{
	if(!x || !y)
		return x + y;
	if(tr[x].key > tr[y].key) // > >= < <=
	{
		rson(x) = merge(rson(x),y);
		pushup(x);
		return x;
	}
	else
	{
		lson(y) = merge(x,lson(y));
		pushup(y);
		return y;
	}
}
int x,y,z;
inline void ins(int val)
{
	split(root,val,x,y);
	root = merge(merge(x,newnode(val)),y);
}

inline void del(int val)
{
	split(root,val,x,z);
	split(x,val - 1,x,y);
	y = merge(lson(y),rson(y));
	root = merge(merge(x,y),z);
}

inline int get_rank(int val)
{
	split(root,val - 1,x,y);
	int res = tr[x].size + 1;
	root = merge(x,y);
	return res;
}

inline int get_num(int rank)
{
	int u = root;
	while(u)
	{
		if(tr[lson(u)].size + 1 == rank)
			break;
		else if(tr[lson(u)].size >= rank)
			u = lson(u);
		else
		{
			rank -= tr[lson(u)].size + 1;
			u = rson(u);
		}
	}
	return tr[u].val;
}

inline int get_pre(int val)
{
	split(root,val - 1,x,y);
	int u = x;
	while(rson(u))
		u = rson(u);
	int res = tr[u].val;
	root = merge(x,y);
	return res;
}

inline int get_suc(int val)
{
	split(root,val,x,y);
	int u = y;
	while(lson(u))
		u = lson(u);
	int res = tr[u].val;
	root = merge(x,y);
	return res;
}
int n,op,t;
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d",&op,&t);
		if(op == 1)
			ins(t);
		else if(op == 2)
			del(t);
		else if(op == 3)
			printf("%d\n",get_rank(t));
		else if(op == 4)
			printf("%d\n",get_num(t));
		else if(op == 5)
			printf("%d\n",get_pre(t));
		else if(op == 6)
			printf("%d\n",get_suc(t));
	}
	return 0;
}