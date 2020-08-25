#include <bits/stdc++.h>
using namespace std; 

class DisjointSet
{
    unordered_map<int, int> parent;

    unordered_map<int, int> rank;

public:
    void makeSet(vector<int> const &universe)
    {
        for (int i : universe)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int Find(int k)
    {
        // if k is not root
        if (parent[k] != k)
            // path compression
            parent[k] = Find(parent[k]);

        return parent[k];
    }

    // Perform Union of two subsets
    void Union(int a, int b)
    {
        // find root of the sets in which elements
        // x and y belongs
        int x = Find(a);
        int y = Find(b);

        // if x and y are present in same set
        if (x == y)
            return;

        // Always attach smaller depth tree under the
        // root of the deeper tree.
        if (rank[x] > rank[y])
            parent[y] = x;
        else if (rank[x] < rank[y])
            parent[x] = y;
        else
        {
            parent[x] = y;
            rank[y]++;
        }
    }
};

void printSets(vector<int> const &universe, DisjointSet &ds)
{
    for (int i : universe)
        cout << ds.Find(i) << ' ';

    cout << '\n';
}



struct vertex
{
    int e,mark=0;
};

bool connected(int l[], int n)
{   
    for(int i=1;i<n;i++)
        if(l[i] == 1)
            return true;
    return false;
}


vector<float> edge_cost(vector<vector<vertex> > A,float d[],int l[], DisjointSet C,int n)
{
    float ans = 99999, temp;
    int v1=1,v2=1;
    for(int i=1;i<n+1;i++)
    {
        for(int j=i+1;j<n+1;j++)
        {
            if(A[i][j].e!=-1 && (C.Find(i) != C.Find(j)) && l[i]+l[j]!=0)
            {   
                temp = (A[i][j].e - d[i] - d[j])/(l[i]+l[j]);
                if(temp<ans)
                {
                    ans = temp;
                    v1 = i;
                    v2 = j;
                    
                }
            }
        }
    }
    vector<float> v;
    v.push_back(ans);
    v.push_back(static_cast<float>(v1));
    v.push_back(static_cast<float>(v2));
    return v;
}


vector<float> penalty(vector<vector<vertex> > A, float w[], unordered_map<int, set<int>> mp,int l[], int n)
{
    float temp=0, ans;
    int in, comp;
    ans=99999;
    vector<float> v;

    for(auto it:mp)
    {
        if(l[it.first] == 1)
        {
            temp = 0;
            for(auto it1=it.second.begin();it1!=it.second.end();++it1)
            {
                in = *it1;
                temp+=(A[in][0].e);
            }
            if(temp-w[it.first]<ans)
            {
                ans = temp-w[it.first];
                comp = it.first;
            }
        }
    }
    v.push_back(ans);
    v.push_back(static_cast<float>(comp));
    return v;
}


int main() 
{ 
    cout<<"Provide input in the following format \n";
    cout<<"n e r where n is the #nodes, e is the #edges, r is the root node.\n";
    cout<<"Followed by n lines of the following format each\n";
    cout<<"v p where v is the vertex number and p is its prize\n";
    cout<<"Followed by e lines of following format each\n";
    cout<<"v1 v2 w where w is the weight of the edge between vertex v1 and v2.\n";
    int n,ne,r;
    cin>>n>>ne>>r;
    int v1,v2,p1;
    float d[n+1];
    float w[n+1];
    int l[n+1];
    // struct vertex A[n+1][n+1];
    vector<vector<vertex> > A( n+1 , vector<vertex> (n+1));

    memset(d,0,n+1);
    memset(w,0,n+1);
    memset(l,0,n+1);
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


    // for(int i=0;i<n+1;i++)
    // {
    //     for(int j=0;j<n+1;j++)
    //         cout<<A[i][j].e<<" ";
    //     cout<<endl;
    // }

    unordered_map<int, set<int>> mp;
    for(int i=1;i<n+1;i++)
        mp[i].insert(i);

    DisjointSet C;
    vector<int> universe;
    for(int i=1;i<n+1;i++)
        universe.push_back(i);
    C.makeSet(universe);


    set<pair<int, int>> F;
    for(int i=1;i<n+1;i++)
    {
        d[i] = 0;
        w[i] = 0;
        if(i==r)
            l[i] = 0;
        else
            l[i] = 1;
    }

    while(connected(l,n+1))
    {
        vector<float> ans1 = edge_cost(A,d,l,C,n);
        vector<float> ans2 = penalty(A,w,mp,l,n);
        vector<float> ans;
       
        if(ans1[0]<=ans2[0])
            ans=ans1;
        else
            ans=ans2;

        for(int i=1;i<n+1;i++)
        {
            w[i]+=((ans[0])*l[i]);
            d[i]+=((ans[0])*l[i]);
        }
        if(ans==ans1)
        {
            // cout<<" add to F "<<ans[1]<<" "<<ans[2]<<" "<<endl;
            F.insert(make_pair(static_cast<int>(ans[1]),static_cast<int>(ans[2])));
            C.Union(static_cast<int>(ans[1]),static_cast<int>(ans[2]));
            int var1,var2;
            var1 = min(static_cast<int>(ans[1]),static_cast<int>(ans[2]));
            var2 = max(static_cast<int>(ans[1]), static_cast<int>(ans[2]));
            for(auto it=mp[var2].begin();it!=mp[var2].end();++it)
                mp[var1].insert((*it));
            for(auto it=mp[var1].begin();it!=mp[var1].end();++it)
                mp[var2].insert((*it));
            int vari=w[static_cast<int>(ans[1])]+w[static_cast<int>(ans[2])];
            for(auto it=mp[var1].begin();it!=mp[var1].end();++it)
                w[(*it)]=vari;
            if(C.Find(r)==C.Find(static_cast<int>(ans[1])))
            {
                for(auto it = mp[static_cast<int>(ans[1])].begin();it!=mp[static_cast<int>(ans[1])].end();++it)
                    l[(*it)] = 0;
            }
            
        }
        else
        {
            vector<int> vtemp;
            // cout<<" not add to F "<<ans[1]<<endl;
            for(auto it=mp[static_cast<int>(ans[1])].begin();it!=mp[static_cast<int>(ans[1])].end();++it)
            {
                l[(*it)]=0;
                A[0][(*it)].mark = 1;
                A[(*it)][0].mark = 1;
            }

            
        }
        // for(int i=1;i<n+1;i++)
        //     cout<<l[i]<<" ";
        // cout<<endl;
        // for(int i=1;i<n+1;i++)
        //     cout<<w[i]<<" ";
        // cout<<endl<<endl<<endl;
    }
    cout<<"\n Prize part is \n";
    for(auto it:F)
        cout<<it.first<<" "<<it.second<<endl;
    // cout<<"\nPrize part contains following vertices \n";
    // cout<<"vertx no. 5 with prize 4\n";
    // cout<<"\nPCST value is \n 13 \n";
    return 0; 
} 