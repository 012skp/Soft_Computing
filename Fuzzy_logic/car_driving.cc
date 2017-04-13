#include<bits/stdc++.h>
using namespace std;

#define F first
#define S second
#define pb push_back
typedef pair<int,int> pii;

int main(){
	//Initialise...................
	int features = 3; // temprature and cloudiness....
	vector<vector<pii> > data(features); // data[0] => temprature;  data[1] => cloudiness; data[2] => speed.

	data[0].pb({20,50});	//COLD
	data[0].pb({40,70});	//NORMAL
	data[0].pb({60,90});	//HOT
	data[0].pb({80,100});	//VERY HOT

	data[1].pb({20,40});	//LESS CLOUDY
	data[1].pb({30,70});	//NORMAL CLOUDY
	data[1].pb({60,100});	//HIGH CLOUDY

	data[2].pb({20,40});	//SLOW SPEED
	data[2].pb({30,70});	//NORMAL SPEED
	data[2].pb({60,100});	//HIGH SPEED


	cout<<"test"<<endl;
	//Rules Defined...
	vector<vector<int> > rule(4,vector<int>(3));
	rule[0][0] = 1;
	rule[0][1] = 0;
	rule[0][2] = 0;
	rule[1][0] = 1;
	rule[1][1] = 1;
	rule[1][2] = 0;
	rule[2][0] = 2;
	rule[2][1] = 1;
	rule[2][2] = 1;
	rule[3][0] = 2;
	rule[3][1] = 2;
	rule[3][2] = 1;

	cout<<"test2"<<endl;
	int n = features-1;
	int param[n];
	printf("Enter temp(0-100):"); fflush(stdout);
	cin>>param[0];
	printf("Enter cloudiness(0-100):"); fflush(stdout);
	cin>>param[1];


	vector<vector<pair<int,double> > > output(n);
	//Calculation of output....

	for(int f = 0;f<n;f++){
		for(int i=1;i<data[f].size()-1;i++) //For intermediate triangles
			if(param[f] < data[f][i].S && param[f] > data[f][i].F){
				double mid = (1.0*data[f][i].F+data[f][i].S)/2;
				if(param[f] < mid) output[f].pb({i,(1.0*param[f]-data[f][i].F)/(1.0*mid-data[f][i].F)});
				else output[f].pb({i,(1.0*param[f]-data[f][i].S)/(1.0*mid-data[f][i].S)});
			}
		if(param[f] < data[f][0].S)
			if(param[f] < data[f][0].F) output[f].pb({0,1.0});
			else output[f].pb({0,(1.0*param[f]-data[f][0].S)/(1.0*data[f][0].F-data[f][0].S)});
		int end = data[f].size()-1;
		if(param[f] > data[f][end].F)
			if(param[f] > data[f][end].S) output[f].pb({end,1.0});
			else output[f].pb({end,(1.0*data[f][end].F-param[f])/(1.0*data[f][end].F-data[f][end].S)});
	}


	for(int i=0;i<output.size();i++){
		printf("%d feature: ",i);
		for(int j=0;j<output[i].size();j++) printf("{%d,%lf} ",output[i][j].F,output[i][j].S);
		cout<<endl;
	}
		//Here output size = 2;
	double ans = 0,sum = 0;
	for(int i=0;i<output[0].size();i++)
		for(int j=0;j<output[1].size();j++){
			int x1 = output[0][i].F, x2 = output[1][j].F;
			double y1 = output[0][i].S, y2 = output[1][j].S;
			int partition = rule[x1][x2];
			if(data[2].size()-1 == partition){
				//cout<<"last partition"<<endl;
				ans+= min(y1,y2)*data[2][data[2].size()-1].S;
				sum+= min(y1,y2);
			}
			else if(partition == 0){
				//cout<<"first partition"<<endl;
				ans+= min(y1,y2)*data[2][0].F;
				sum+= min(y1,y2);
			}
			else{
				//cout<<"middle partition"<<endl;
				ans+= min(y1,y2)*(1.0*data[2][partition].F+data[2][partition].S)/2;
				sum+= min(y1,y2);
			}
		}
		cout<<"you should drive at speed = "<<ans/sum<<endl;

}
