#include <cstdio>
#include <cstring>

unsigned int sd = 233;

#define N 100010

inline int rnd()
{
	sd ^= sd << 13;
	sd ^= sd >> 7;
	sd ^= sd << 11;
	return (int)sd;
}

struct node
{
	int lson,rson,val,key,sz;
};

struct Tree
{
	int idx,root;
	node fhq[N];
	#define lson(k) fhq[k].lson
	#define rson(k) fhq[k].rson
	inline int newnode(int val)
	{
		fhq[++idx].val = val;
		fhq[idx].key = rnd();
		fhq[idx].sz = 1;
		return idx;
	}
	inline void pushup(int k)
	{
		fhq[k].sz = fhq[lson(k)].sz + fhq[rson(k)].sz + 1;
	}
	void split(int k,int sz,int &x,int &y)
	{
		if(!k)
			x = y = 0;
		else
		{
			if(fhq[lson(k)].sz < sz)
			{
				x = k;
				split(rson(k),sz - fhq[lson(k)].sz - 1,rson(k),y);
			}
			else
			{
				y = k;
				split(lson(k),sz,x,lson(k));
			}
			pushup(k);
		}
	}
	int merge(int x,int y)
	{
		if(!x || !y)
			return x + y;
		if(fhq[x].key > fhq[y].key)
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
	void ins(int sz,int val)
	{
		split(root,sz,x,y);
		root = merge(merge(x,newnode(val)),y);
	}
	void del(int sz)
	{
		split(root,sz,x,z);
		split(x,sz - 1,x,y);
		root = merge(x,z);
	}
	int get_k(int rank)
	{
		int u = root;
		while(u)
		{
			if(fhq[lson(u)].sz + 1 == rank)
				break;
			else if(fhq[lson(u)].sz >= rank)
				u = lson(u);
			else
			{
				rank -= fhq[lson(u)].sz + 1;
				u = rson(u);
			}
		}
		return fhq[u].val;
	}
	void out(int k)
	{
		if(!k)
			return;
		out(lson(k));
		printf("%d ",fhq[k].val);
		out(rson(k));
	}
}

int main()
{
	while(1)
	{
		int op,a,b,c;
		scanf("%d",&op);
		if(op == 1)
		{
			scanf("%d%d",&a,&b);
			ins(a,b);
		}
		if(op == 2)
		{
			scanf("%d",&a);
			del(a);
		}
		if(op == 3)
		{
			scanf("%d",&a);
			printf("%d\n",get_k(a));
		}
		out(root);
		printf("\n");
	}
	return 0;
}