#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;


#define F first
#define S second
#define pb push_back
#define rn (1.0*rand())/RAND_MAX
#define NU 20
#define D_(r) r<=0.5?pow(2*r,double(1)/(1+NU))-1:1-pow(2*(1-r),double(1)/(NU+1))
typedef pair<double,pair<double,double> > cat;

double f(double x){
  return 0.26+(0.93/x)+(0.26)/(x*x);
}a

double param[3];

define f1(double x){
  return param[0]+(param[1]/x)+(param[2]/x);
}


void swap(cat &c1, cat &c2){
  cat c3 = c1;
  c1 = c2;
  c2 = c1;
}

int main(){
  int n = 50;
  vector<cat> cat_list(n);
  for(int i=0;i<n;i++){
    cat_list[i].S.F = rn-0.5; //position
    cat_list[i].S.S = rn/10;  //velocity
    cat_list[i].F = f(cat_list[i].S.F);
  }
  cat gbest;
  while(1){
    sort(cat_list.begin(),cat_list.end());
    for(int i=0;i<n;i++) cout<<cat_list[i].F<<' '; cout<<endl;
    if(cat_list[n-1].F == 0) break;
    gbest = cat_list[0];

    //Randomization......
    //for(int i=0;i<n;i++) cout<<cat_list[i].F<<endl;
    for(int i=0;i<n;i++) swap(cat_list[i],cat_list[rn*50]);
    cout<<"after..."<<endl;
    //for(int i=0;i<n;i++) cout<<cat_list[i].F<<endl;

    //Seeking Mode for 80% of cats.....
    int t_8 = 0.8*n;
    for(int i=0;i<t_8;i++){
      vector<cat> clone(6,cat_list[i]);
      for(int j=0;j<5;j++){
        clone[j].S.F += D_(rn);
        clone[j].F = f(clone[j].S.F);
      }
      sort(clone.begin(),clone.end());
      cat_list[i] = clone[0];
    }


    //Tracing Mode for 20% of cats...
    for(int i=t_8;i<n;i++){
      cat_list[i].S.S += rn*2*(gbest.S.F-cat_list[i].S.F); //Velocity update...
      cat_list[i].S.F += cat_list[i].S.S; //Position update...
      cat_list[i].F = f(cat_list[i].S.F);
    }

    sleep(1);

  }



  return 0;
}
