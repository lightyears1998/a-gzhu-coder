// Author���Ұ���
#include <iostream>  
#include <cstring>   
#include <cstdio>   
#include <algorithm>  
#include <cmath>     
#include <string.h>  
using namespace std;
int arr[100050],n;char a[20];
struct node
{
    int val;  //����������ĳ�������ֵ
    int l,r;  //���Ҷ��ӱ�ţ����䷶Χ�� 
}tree[3000001];

void build(int root,int l,int r)  //���� 
{
    int mid;
   
    tree[root].l=l;tree[root].r=r;
    if (l==r) tree[root].val=arr[l];
    else
    {
        mid=(l+r)/2;
        build(root*2,l,mid);     //�ݹ鹹��������
        build(root*2+1,mid+1,r); //�ݹ鹹��������
        tree[root].val=max(tree[root*2].val,tree[root*2+1].val);//�洢�������������ֵ 
    }
}

void update(int root,int ind,int addval)  //������� 
{
    int mid;
    if (tree[root].l==tree[root].r)
    {
        tree[root].val+=addval;
        return;
    }
    else
    {
        mid=(tree[root].l+tree[root].r)/2;
        if (ind<=mid) update(root*2,ind,addval);
        else update(root*2+1,ind,addval);
        tree[root].val=max(tree[root*2].val,tree[root*2+1].val);
    }
}

int ask(int root,int l,int r)
{
    int mid;
    if (tree[root].l==l&&tree[root].r==r)
        return tree[root].val;
    else 
    {
        mid=(tree[root].l+tree[root].r)/2;
        if (mid>=r)
            return ask(root*2,l,r);
        else if (mid<l)
            return ask(root*2+1,l,r); 
        else return max(ask(root*2,l,mid),ask(root*2+1,mid+1,r));

    }
}

int main()
{
	int t,ans=1;
   scanf("%d",&t);
   while(t--)
   {
   	scanf("%d",&n);
   	 for(int i=1;i<=n;i++)
   	 scanf("%d",&arr[i]);
   	 build(1,1,n);
   	 printf("Case %d:\n",ans++);
   	 int ind,val;
   	 while(scanf("%s",&a))
   	 {
   	 	if(a[0]=='E')break;
   	 	scanf("%d%d",&ind,&val);
   	 	if(a[0]=='Q') printf("%d\n",ask(1,ind,val));
   	 	else if(a[0]=='A')update(1,ind,val);
   	 	else if(a[0]=='S')update(1,ind,-val);
		}
   }
}
