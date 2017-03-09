#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define F first
#define S second
#define rn (double)rand()/(double)RAND_MAX
#define mp make_pair
#define pb push_back
#define INF INT_MAX
#define f1(x) x*x
#define f2(x) (x-10)*(x-10)
int MU = 20; //crossover operator
int NU = 20; //mutation operator
#define B_(r) r<=0.5?pow((2*r),double(1)/(1+MU)):pow( ((double)1/2*(1-r)),double(1)/(1+MU))
#define D_(r) r<=0.5?pow(2*r,double(1)/(1+NU))-1:1-pow(2*(1-r),double(1)/(NU+1))

int mr;

struct table{
	double x,f1,f2,cd;
	int rank;
};

bool compare(struct table t1, struct table t2){
	return t1.f1 < t2.f1;
}

bool compare1(struct table t1, struct table t2){
	if(t1.rank < t2.rank) return true;
	else if(t1.rank == t2.rank) return t1.cd > t2.cd;
	else return false;
}
bool compare2(struct table t1, struct table t2){
	if(t1.rank < t2.rank) return true;
	else if(t1.rank == t2.rank) return t1.f1 < t2.f1;
	else return false;
}

void set_cd(vector<struct table> &t,int x, int y, double f1_max, double f2_max, double f1_min, double f2_min){
	t[x].cd = INF; t[y].cd = INF;
	for(int i=x+1;i<y;i++) t[i].cd = (t[i+1].f1-t[i-1].f1)/(f1_max-f1_min) + (t[i+1].f2-t[i-1].f2)/(f2_max-f2_min);
}

void evaluate_obj_func( vector<struct table> &t ){
	int n = t.size();
	double f1_max,f1_min,f2_max,f2_min;
	
	for(int i=0;i<n;i++) {t[i].f1 = f1(t[i].x); t[i].f2 = f2(t[i].x); t[i].rank = 0; t[i].cd =0;}
	f1_max = f1_min = t[0].f1; f2_max=f2_min = t[0].f2;
	for(int i=1;i<n;i++){
		if(t[i].f1 > f1_max) f1_max = t[i].f1;
		if(t[i].f2 > f2_max) f2_max = t[i].f2;
		if(t[i].f1 < f1_min) f1_min = t[i].f1;
		if(t[i].f2 < f2_min) f2_min = t[i].f2;
	}
	sort(t.begin(),t.end(),compare);	//sorts according to f1....
	//for(int i=0;i<n;i++) printf("this is %10lf %10lf %10lf %10d %10lf\n",t[i].x,t[i].f1,t[i].f2,t[i].rank,t[i].cd);
	mr = 0;
	for(int i=0;i<n;i++){  				//rank calculation...........
		int max_rank = 0;
		for(int j=i-1;j>=0;j--) if(t[i].f1 > t[j].f1 && t[i].f2 > t[j].f2 && t[j].rank > max_rank) max_rank = t[j].rank;
		t[i].rank = max_rank+1;
		if(t[i].rank > mr) mr = t[i].rank;
	}
	int i=0;

	sort(t.begin(),t.end(),compare2); //sorts rank wise then accoring to f1.....
	for(int i=0;i<n;i++) printf("f1 this is %10lf %10lf %10lf %10d %10lf\n",t[i].x,t[i].f1,t[i].f2,t[i].rank,t[i].cd);
	while(i < n){					//crowding distance calculation......
		int crank = t[i].rank;
		int j=i+1;
		while(crank == t[j].rank && j<n) j++;
		if(j-i > 2) set_cd(t,i,j-1,f1_max,f2_max,f1_min,f2_min);
		else{ t[i].cd = INF; t[j-1].cd = INF;}
		i = j;
	}
	for(int i=0;i<n;i++) printf("%10lf %10lf %10lf %10d %10lf\n",t[i].x,t[i].f1,t[i].f2,t[i].rank,t[i].cd);
	cout<<"mr = "<<mr<<endl;
}

int main(int argc, char* argv[]){
	srand(time(NULL));
	if(argc < 2) printf("usage %s <population_size> [<no_of_iteration>] [<MU>] [<NU>]\n",argv[0]);
	int c=1000,n = atoi(argv[1]);
	if(argc == 5){ MU = atoi(argv[3]); NU=atoi(argv[4]);}
	if(argc >= 3) c = atoi(argv[2]);
	vector<struct table> t(n,{0,0,0,0,0});
	for(int i=0;i<n;i++) t[i].x = rn*30-10;
	cout<<"Init"<<endl;
	evaluate_obj_func(t); 					// calculates rank and crowding distance....
	cout<<"Init"<<endl;
	FILE *fp = fopen("output1","w");
	for(int i=0;i<n;i++){
		fprintf(fp, "%lf	%lf\n",t[i].f1,t[i].f2 );
	}
	fclose(fp);
	//c = 0;
	while(c--){
		n = t.size();
		// tournament selection....
		sort(t.begin(),t.end(),compare1);
		int nn = n*0.9,n_=n;				//crossover of 80% of total.....
		if(nn%2 == 0) nn--; 				//make it even... 
		vector<struct table> tt;
		while(tt.size()!=nn){
			int r1=rn*n_,r2=rn*n_,r3;
			r3 = compare1(t[r1],t[r2])?r1:r2;
			tt.pb(t[r3]);
			//cout<<"r3= "<<r3<<" t.size = "<<t.size()
			auto it = t.begin();
			for(int i=0;i<r3;i++) it++; t.erase(it);
			n_--;
		}
		cout<<"tournament over"<<endl;
		//crossover...
		for(int i=0;i<=nn;i+=2){
			struct table child1,child2;
			child1.x = 0.5*( (1+B_(rn))*t[i].x + (1-B_(rn))*t[i+1].x );
			child2.x = 0.5*( (1-B_(rn))*t[i].x + (1+B_(rn))*t[i+1].x );
			t.pb(child2); t.pb(child1);
		}
		for(int i=0;i<=nn;i++) t.pb(tt[i]);
		tt.clear();
		cout<<"crossover over"<<endl;
		//mutation....
		nn = n*0.1; 						//mutating 20% of total popultaion....
		for(int i=0;i<nn;i++){
			int r = rn;
			t[r].x = t[r].x + D_(rn); 
		}
		evaluate_obj_func(t);
		sort(t.begin(),t.end(),compare1); 	//non dominant sorting based on min rank then max crowding....
		t.resize(n);
		for(int i=0;i<n;i++) printf("this is %10lf %10lf %10lf %10d %10lf\n",t[i].x,t[i].f1,t[i].f2,t[i].rank,t[i].cd);
		//scanf("%d",&nn);
		if(mr == 1 || t[n-1].rank == 1){
			printf("stopped at c = %d",c);
			break;
		} 

	}
	fp = fopen("output","w");
	for(int i=0;i<n;i++) fprintf(fp,"%lf 	%lf\n",t[i].f1,t[i].f2);
	fclose(fp);
	system("./run");
	system("gnome-open 1.png");
	return 0;
}
