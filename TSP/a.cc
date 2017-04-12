#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define F first
#define S second
#define pb push_back
#define mp make_pair


typedef vector<vector<double> > matrix;

int main(int argc, char* argv[]){
	int n;
	cin>>n;
	matrix graph(n,vector<double>(n));
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>graph[i][j];
	matrix fi(n,vector<double>(n,0.2));			//Initialise Feromen Intensity....
	matrix di(n,vector<double>(n));				//Initialise dist. inverse matrix...
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) {if(i==j) di[i][j] = INT_MAX; di[i][j] =1.0/graph[i][j];}
	double best_cost = INT_MAX;
	vector<int> best_path;
	while(1){
		//Start n ants from each of n nodes...
		for(int i=0;i<n;i++){ for(int j=0;j<n;j++) cout<<fi[i][j]<<' '; cout<<endl;}
		matrix del_fi(n,vector<double>(n,0.0));
		
		for(int i=0;i<n;i++){
			vector<int> path; path.pb(i);
			vector<int> done(n,0); done[i] = 1;
			int node = i;
			while(1){
				double t = 0.0; 
				int next_node = -1;
				for(int j=0;j<n;j++){
					if(done[j]) continue;
					else if(fi[node][j]*di[node][j]*di[node][j] > t){ t = fi[node][j]*di[node][j]*di[node][j]; next_node = j;}
				}
				if(next_node == -1) break;
				else{
					//printf("for %d node %d is best...\n",node,next_node);
					path.pb(next_node);
					done[next_node] = 1;
					node = next_node;
				}
			}
			double cost = 0.0;
			for(int j=1;j<path.size();j++) cost+=graph[path[j-1]][path[j]]; cost+= graph[path[path.size()-1]][path[0]];
			for(int j=1;j<path.size();j++) del_fi[path[j-1]][path[j]] += 1.0/cost; del_fi[path[path.size()-1]][path[0]] += 1.0/cost;
			if(cost < best_cost) {best_cost = cost; best_path = path;}
			cout<<"current best = "<<cost<<" global best = "<<best_cost<<"     ";
			for(int j=0;j<n;j++) cout<<path[j]<<' '; cout<<endl;
			//for(int k=0;k<n;k++){ for(int l=0;l<n;l++) cout<<del_fi[k][l]<<' '; cout<<endl;}
		}
		//Update feroment intensity fi = (fi+del_fi)/2;
		for(int j=1;j<best_path.size();j++) del_fi[best_path[j-1]][best_path[j]] += n*1.0/best_cost; del_fi[best_path[best_path.size()-1]][best_path[0]] += n*1.0/best_cost;
		for(int i=0;i<n;i++) for(int j=0;j<n;j++) fi[i][j] = (fi[i][j]+del_fi[i][j]);
		//printf("best cost = %lf\n",best_cost);
		//for(int i=0;i<best_path.size();i++) cout<<best_path[i]<<' '; cout<<endl;
		if(argc >= 2) sleep(1);
	}


	return 0;
}
