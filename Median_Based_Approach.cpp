#include <bits/stdc++.h>
using namespace std; 

struct vertex
{
    int e,mark=0;
};

int main ()
{
    cout<<"Provide input in the following format \n";
    cout<<"n e r where n is the #nodes, e is the #edges, r is the root node.\n";
    cout<<"Followed by n lines of the following format each\n";
    cout<<"v p where v is the vertex number and p is its prize\n";
    cout<<"Followed by e lines of following format each\n";
    cout<<"v1 v2 w where w is the weight of the edge between vertex v1 and v2.\n";
    int n,ne,r,rn1,rn2;
    srand((unsigned)time(0));
    cin>>n>>ne>>r;
    int v1,v2,p1;
    float d[n+1];
    float w[n+1];
    int l[n+1];
    // struct vertex A[n+1][n+1];
    vector<vector<vertex> > A( n+1 , vector<vertex> (n+1));

    for(int i=0;i<n+1;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            A[i][j].e = -1;
            A[i][j].mark = 0;
        }
    }
    
    for(int i=0;i<n;i++)
    {
        cin>>v1>>p1;
        A[0][v1].e = p1;
        A[v1][0].e = p1;
    }
    
    for(int i=0;i<ne;i++)
    {
        cin>>v1>>v2>>p1;
        A[v1][v2].e = p1;
        A[v2][v1].e = p1;
    }

    for(int i=0;i<n+1;i++)
    {
        for(int j=0;j<n+1;j++)
            cout<<A[i][j].e<<" ";
        cout<<endl;
    }
    int arr[n];
    for (int i=1;i<n+1;i++)
    {
    	arr[i-1] = A[0][i].e;
    }

    int med=0;
    sort(arr,arr+n);

    int aux[n];
    for(int i=0;i<n;i++)
    {
        aux[i]=i+1;
    }
    for(int i=0;i<5*n;i++)
    {
        rn1=rand()%n;
        rn2=rand()%n;
        swap(aux[rn1], aux[rn2]);
    }
    if(n%2!=0)
    	med = arr[n/2];
    else
    	med = (arr[n/2]+arr[(n/2)-1])/2;

    int cnt=0;
    int med_arr[n/4];
    for(int i=0;i<n;i++)
    {
    	if(A[0][aux[i]].e>=med)
    	{
    		med_arr[cnt] = A[0][aux[i]].e;
    		cnt++;
    	}
    	if(cnt>=(n/4)-1)
    		break;
    }

    for(int i=0;i<cnt;i++)
    	cout<<med_arr[i]<<" ";
    cout<<endl;

}