#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
int getroot(int ar[],int i){
    int index=i-1;
    int root=ar[index];
    while(root!=-1){
        index=root-1;
        root=ar[index];
    }
    return index;
}

int getrootrec(int ar[],int i){
    if(ar[i]==-1){
        return i;
    }
    return getrootrec(ar,ar[i]);
}
bool find(int ar[],int a,int b){
    int root1=getroot(ar,a)+1;
    int root2=getroot(ar,b)+1;
    cout<<root1<<endl;
    cout<<root2<<endl;
    if(root1==root2){
        return 1;
    }
    return 0;
}
int main(){
    int ar[]={-1,1,1,2,-1};
    cout << find(ar,5,2);
    return 0;
}

/* #include<bits/stdc++.h>
using namespace std;

vector<int> dsuf;
//FIND operation
int find(int v)
{
	if(dsuf[v]==-1)
		return v;
	return find(dsuf[v]);
}

void union_op(int fromP,int toP)
{
	fromP = find(fromP);
	toP = find(toP);
	dsuf[fromP] = toP;
}

bool isCyclic(vector<pair<int,int>>& edge_List)
{
	for(auto p: edge_List)
	{
		int fromP = find(p.first);	//FIND absolute parent of subset
		int toP = find(p.second);

		if(fromP == toP)
			return true;

		//UNION operation
		union_op(fromP,toP);	//UNION of 2 sets
	}
	return false;
}

int main()
{
	int E;	//No of edges
	int V;	//No of vertices (0 to V-1)
	cin>>E>>V;

	dsuf.resize(V,-1);	//Mark all vertices as separate subsets with only 1 element
	vector<pair<int,int>> edge_List;	//Adjacency list
	for(int i=0;i<E;++i)
	{
		int from,to;
		cin>>from>>to;
		edge_List.push_back({from,to});
	}

	if(isCyclic(edge_List))
		cout<<"TRUE\n";
	else
		cout<<"FALSE\n";
	
	return 0;
} */
