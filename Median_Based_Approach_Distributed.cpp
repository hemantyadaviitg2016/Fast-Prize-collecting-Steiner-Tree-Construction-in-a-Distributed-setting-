//input, output as well as the data structures for storing the graph
// are same as in the GW algo code so as to maintain a common interface


// Basic idea is to assume that there a n machines in the system (graph has n nodes). Since we are using the prize of
// of the vertices only and not the edges, we can assume a simple topology, something like 0-0-0-0-0 where 0 represents
// nodes and - represents an edge

#include <iostream>
#include <thread>
#include <bits/stdc++.h>

using namespace std;

// this struct is particularly not useful in this code.
// However for the sake of having similar interface so as to incorporate this into a larger code,
// i have used this struct here as well
struct vertex
{
    int e,mark=0;
};


// helper function to create the simple topology as above
void copy_to_machine(vector<vector<vertex>> &v, int i, int prize[])
{
	prize[i]=v[0][i+1].e;
}

//helper function to sort by comparing adjacent elements
void sort_distributed_helper(int prize[], int i)
{
	if(prize[i]>prize[i+1])
		swap(prize[i], prize[i+1]);
}

//random function to select randomly n/4 vertices
void generate(int random_ar[], int i, int n)
{
	random_ar[i]=(rand()%(n/2))+n/2;
}

int main()
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

	int prize[n];
	thread work[n];                  // there will n threads corresponding to n machines

	// create the simple topology
	for(int i=0;i<n;i++)
		work[i]=thread(copy_to_machine,v,i,prize);

	// wait for all the threads to finish
	for(int i=0;i<n;i++)
		work[i].join();

	//distributed sort
	// it takes n steps and one step will be all the threads working in parallel thus O(n) time
	// in even steps, it compares every even index element with the next odd index element
	// in odd steps, it compares every odd index element with the next even index element
	// this helps in avoiding race condition for the working threads
	for(int j=0;j<n;j++)
	{
		if(j%2==0)
		{
			for(int i=0;i<n-1;i+=2)
				work[i]= thread(sort_distributed_helper, prize, i);
		}
		else
		{
			for(int i=1;i<n-1;i+=2)
				work[i]= thread(sort_distributed_helper, prize, i);
		}

		//wait for threads to finish
		for(int i=0;i<n;i++)
			work[i].join();
	}
	int med;           // median value
	if(n%2!=0)
    	med = arr[n/2];
    else
    	med = (arr[n/2]+arr[(n/2)-1])/2;
    int random_ar[n/4];          // array used to choose randomly

    // generate n/4 random numbers in parallel
    for(int i=0;i<n/4;i++)
    {
    	work[i]=thread(generate,random_ar,i, n);
    }
    cout<<"Prize vertices chosen are\n";
    for(int i=0;i<n/4;i++)
    	cout<<prize[random_ar[i]]<<" ";
   	cout<<endl;

	return 0;
}

