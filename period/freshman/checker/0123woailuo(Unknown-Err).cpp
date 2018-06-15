#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

int arr[100020], n;
char s[20];

const int MAXNUM = 10020000 * 4;

struct SegTreeNode
{
    long long val;
} segTree[MAXNUM];
 
void build(int root, int arr[], int istart, int iend)
{
	if(istart == iend)
    	segTree[root].val = arr[istart];
	else
 	{
    	int mid = (istart + iend) / 2;
    	build(root*2+1, arr, istart, mid);
    	build(root*2+2, arr, mid+1, iend);
    	
    	segTree[root].val = max(segTree[root*2+1].val, segTree[root*2+2].val);
	}
}

long long query(int root, int nstart, int nend, int qstart, int qend)
{
 
	if(qstart > nend || qend < nstart)
    	return 0;

	if(qstart <= nstart && qend >= nend)
    	return segTree[root].val;

	int mid = (nstart + nend) / 2;
	return max(query(root*2+1, nstart, mid, qstart, qend),
            query(root*2+2, mid + 1, nend, qstart, qend));

}

void updateOne(int root, int nstart, int nend, int index, int addVal)
{
    if(nstart == nend)
    {
        if(index == nstart)
            segTree[root].val += addVal;
        return;
    }
    
	int mid = (nstart + nend) / 2;
    if (index <= mid)
        updateOne(root*2+1, nstart, mid, index, addVal);
    else updateOne(root*2+2, mid+1, nend, index, addVal);
    
    segTree[root].val = max(segTree[root*2+1].val, segTree[root*2+2].val);
}

int main()  
{  
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif

    int i, t, x, y, ans = 1; 
    
	scanf("%d", &t);
    while(t--)  
    { 
        scanf("%d", &n);
        for(i = 0; i <n; i++)  
        {  
            scanf("%d", &arr[i]); 
        }  
        build(0, arr, 0, n-1);
        
        printf("Case %d:\n", ans++);  
        while(scanf("%s", s) == 1)  
        { 
            if(s[0] == 'E') break;
            
            scanf("%d %d", &x, &y);  
            if(s[0] == 'A') updateOne(0,0,n-1,x-1, y);  
            else if(s[0] == 'S') updateOne(0,0,n-1,x-1, -y);  
            else printf("%lld\n", query(0,0,n-1,x-1,y-1));  
        }  
    }
} 
