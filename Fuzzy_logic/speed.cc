#include<bits/stdc++.h>
using namespace std;

#define F first
#define S second
#define pb push_back
typedef pair<int,int> pii;
int features = 3; // temprature and cloudiness....
vector<vector<pii> > data(features); // data[0] => temprature;  data[1] => cloudiness;

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


int ans_partition = 3;
//Rules Defined...
vector<vector<int> > rules(data[0].size(),vector<double>(data[1].size()));
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

int main(){
	int cloudiness,temp;
	cin>>temp>>cloudiness;
	vector<pair<int,double> > cloudiness_value,temp_value;


	//Handling Temprature...
	for(int i=1;i<data[0].size()-1;i++) //For intermediate triangles
		if(temp < data[0][i].S && temp > data[0][i].F){
			double mid = (1.0*data[0][i].F+data[0][i].S)/2;
			if(temp < mid) temp_value.pb({i,(1.0*temp-data[0][i].F)/(1.0*mid-data[0][i].F)});
			else temp_value.pb({i,(1.0*temp-data[0][i].S)/(1.0*mid-data[0][i].S)});
		} 
	if(temp < data[0][0].S)
		if(temp < data[0][0].F) temp_value.pb({0,1.0});
		else temp_value.pb({i,(1.0*temp-data[0][0].S)/(1.0*data[0][0].F-data[0][0].S)});
	int end = data[0].size()-1;
	if(temp > data[0][end].F)
		if(temp > data[0][end].S) temp_value.pb({i,1.0});
		else temp_value.pb({i,(1.0*data[0][end].F-temp)/(1.0*data[0][end].F-data[0][end].S)});
	
	//Handling Cloudiness....
	for(int i=1;i<data[1].size()-1;i++) //For intermediate triangles
		if(cloudiness < data[1][i].S && temp > data[1][i].F){
			double mid = (1.0*data[0][i].F+data[0][i].S)/2;
			if(temp < mid) temp_value.pb({i,(1.0*temp-data[0][i].F)/(1.0*mid-data[0][i].F)});
			else temp_value.pb({i,(1.0*temp-data[0][i].S)/(1.0*mid-data[0][i].S)});
		} 
	if(temp < data[0][0].S)
		if(temp < data[0][0].F) cloudiness_value.pb({0,1.0});
		else cloudiness_value.pb({i,(1.0*temp-data[0][0].S)/(1.0*data[0][0].F-data[0][0].S)});
	int end = data[0].size()-1;
	if(temp > data[0][end].F)
		if(temp > data[0][end].S) temp_value.pb({i,1.0});
		else temp_value.pb({i,(1.0*data[0][end].F-temp)/(1.0*data[0][end].F-data[0][end].S)});
	


}






