#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

#define MU 0.01
#define F first
#define S second
#define pb push_back
#define rn (1.0*rand())/RAND_MAX
#define NU 20
#define D_(r) r<=0.5?pow(2*r,double(1)/(1+NU))-1:1-pow(2*(1-r),double(1)/(NU+1))
typedef pair<double,pair<double,double> > cat;

double param[3];
double x_value[3];

double f(){
  return 0.26*x_value[0]+(0.93*x_value[1])+(0.26*x_value[2]);
}

double f1(){
  return param[0]*x_value[0]+(param[1]*x_value[1])+(param[2]*x_value[2]);
}

int main(){
  int n = 50;
  vector<double> v(n);
  vector<double> e(n);
  for(int i=0;i<n;i++) v[i] = rn-0.5;
  x_value[0] = x_value[1] = x_value[2] = 0;
  FILE *fp = fopen("output","w");
  double itr = 1;
  while(1){
    for(int i=0;i<n;i++){
      x_value[0] = v[i];
      x_value[1] = x_value[0];
      x_value[2] = x_value[1];
      double err = (f()-f1());
      param[i] += 2*MU*v[i]*err;
      e[i] = err;
    }
    sort(e.begin(),e.end());
    cout<<"error is: "<<e[n-1]<<endl;
    //cout<<"System Paramter is: "<<param[0]<<" "<<param[1]<<" "<<param[2]<<endl;
    usleep(1000);
    if(e[n-1] < 0.0002) break;
    fprintf(fp,"%lf %lf\n",e[n-1]*e[n-1],itr);
    itr+= 1;
  }
  cout<<"Training Phase Completed..."<<endl;
  cout<<"System Paramter is: "<<param[0]<<" "<<param[1]<<" "<<param[2]<<endl;
  fclose(fp);
  cout<<"Testing phase"<<endl;
  x_value[0] = x_value[1] = x_value[2] = 0;
  vector<double> vv(100);
  for(int i=0;i<100;i++) vv[i] = rn-0.5;
  FILE *fp1 = fopen("output1","w");
  FILE *fp2 = fopen("output2","w");
  for(int i=0;i<100;i++){
    x_value[0] = vv[i];
    x_value[1] = x_value[0];
    x_value[2] = x_value[1];
    fprintf(fp1,"%lf %d\n",f(),i);
    fprintf(fp2,"%lf  %d\n",f1(),i);
  }
  fclose(fp1);
  fclose(fp2);
  return 0;
}
