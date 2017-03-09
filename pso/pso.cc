#include <bits/stdc++.h>
using namespace std;
#include <unistd.h>
#include <stdlib.h>
#include<iomanip>
typedef pair<double,double>  vec2;
#define F first
#define S second
#define mp make_pair
#define pb push_back


#define POINT_MAX 500
#define VELOCITY_MAX 100
#define rn (double)rand()/(double)RAND_MAX

double dist(vec2 point){
	return sqrt( point.F*point.F + point.S*point.S);
}

vec2 min(vec2 &gbest, vec2 &point){
	if(dist(gbest) < dist(point)) return gbest;
	else return point;
}

int main(int argc, char* argv[]){
	vector<vec2> points,velocity,pbest;
	int n = atoi(argv[1]);
	for(int i=0;i<n;i++){
		points.pb(mp(rn*POINT_MAX,rn*POINT_MAX));
		pbest.pb(points[i]);
		velocity.pb(mp(rn*VELOCITY_MAX,rn*VELOCITY_MAX));
	}

	double W = strtod(argv[2], NULL);
	double C1,C2;
	C1 = C2 = 2.0;
	//W=0.4;
	vec2 gbest = points[0];
	for(int i=0;i<n;i++) gbest = min(gbest,pbest[i]);
	while(1){
		//update velocity...
		for(int i=0;i<n;i++){
			velocity[i].F =  W*velocity[i].F + C1*rn*(pbest[i].F-points[i].F) +  C2*rn*(gbest.F - points[i].F);
			velocity[i].S =  W*velocity[i].S + C1*rn*(pbest[i].S-points[i].S) +  C2*rn*(gbest.S - points[i].S);
		}
		//update position...
		for(int i=0;i<n;i++){ points[i].F += velocity[i].F; points[i].S += velocity[i].S; }
		//update pbest...
		for(int i=0;i<n;i++) pbest[i] = min(pbest[i],points[i]);
		//update gbest...
		for(int i=0;i<n;i++) gbest = min(gbest,pbest[i]);

		for(int i=0;i<n;i++) printf("%0.20lf ",dist(points[i]));
		cout<<endl;
		usleep(100000);
		//W = W - 0.01;
	//	if(dist(gbest) < 0.00001) break;
	}

	return 0;
}
