/*
Vladimir "VladaMG98" Milenkovic
Using Segment Tree which is storing
1. min from interval(left-1,right-1)
2. max from interval(left,right)
3. ans for interval(left,right)
*/
#include <bits/stdc++.h>
#define mid (left+right)/2
using namespace std;
const int N=200010;
int a[N];
int c[N];
struct Node
{
    bool dummy;
    int minn,maxx,ans;
    Node()
    {
        dummy=false;
        minn=maxx=ans=0;
    }
    Node(int i)
    {
        dummy=false;
        ans=a[i];
        minn=c[i-1];
        maxx=c[i];
    }
};
Node nodemerge(Node l,Node r)
{
    if(l.dummy) return r;
    if(r.dummy) return l;
    Node ret=Node();
    ret.minn=min(r.minn,l.minn);
    ret.maxx=max(r.maxx,l.maxx);
    ret.ans=max(max(l.ans,r.ans),r.maxx-l.minn);
    return ret;
}
Node ST[N];
void init(int idx,int left,int right)
{
    if(left==right)
    {
        ST[idx]=Node(left);
        return;
    }
    init(idx*2,left,mid);
    init(1+idx*2,mid+1,right);
    ST[idx]=nodemerge(ST[2*idx],ST[2*idx+1]);
}
Node query(int idx,int left,int right,int l,int r)
{
    if(l<=left&&right<=r) return ST[idx];
    if(r<left||l>right) {Node ret=Node();ret.dummy=true;return ret;}
    return nodemerge(query(2*idx,left,mid,l,r),query(2*idx+1,mid+1,right,l,r));
}
int main()
{
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) c[i]=c[i-1]+a[i];
        int q;
        scanf("%d",&q);
        init(1,1,n);
        while(q--)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",query(1,1,n,l,r).ans);
        }
        return 0;
}
