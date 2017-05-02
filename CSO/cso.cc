#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

#define F first
#define S second
#define pb push_back
#define rn (1.0*rand())/RAND_MAX
int NU = 10; //mutation operator

#define D_(r) r<=0.5?pow(2*r,double(1)/(1+NU))-1:1-pow(2*(1-r),double(1)/(NU+1))

struct position{
  double x,y,z;
};

struct velocity{
  double x,y,z;
};

typedef pair<double,pair<velocity,position> > pop;

void swap(pop &p1, pop &p2){
  pop p3 = p1;
  p1 = p2;
  p2 = p3;
}

double f(pop c){
  int x = c.S.S.x;
  int y = c.S.S.y;
  int z =c.S.S.z;
  return sqrt(x*x+y*y+z*z);
}

#define test(n) {cout<<"test"<<n<<endl; int ttt; cin>>ttt;}
bool compare(pop p1, pop p2){
  return p1.F < p2.F;
}



int main(){
	srand(time(NULL));
  int n = 50;
  double x_l,y_l,z_l;
  x_l = y_l = z_l = 5.12;
  vector<pop> population(n);
  //Initialise random population....
  for(int i=0;i<n;i++) population[i].S.S = {rn*x_l,rn*y_l,rn*z_l};
  for(int i=0;i<n;i++) population[i].S.F = {rn-0.5,rn-0.5,rn-0.5};
  for(int i=0;i<n;i++) population[i].F = f(population[i]); //sets f(x,y,z)...
  pop gbest;
  while(1){
    sort(population.begin(),population.end(),compare);
    if(population[n-1].F == 0) break;
    gbest = population[0];
    for(int i=0;i<n;i++) swap(population[i],population[rn*50]);  //Randomization..

    int n_8 = n*0.8;    //Put 80% in seeking mode....
    for(int i=0;i<n_8;i++){
      vector<pop> clone(6,population[i]);
      for(int j=0;j<5;j++){
        double r = rn;
        //printf("prev x =%lf   ",clone[j].S.S.x);
        clone[j].S.S.x+=D_(rn);
        clone[j].S.S.y+=D_(rn);
        clone[j].S.S.z+=D_(rn);
        //printf("now x =%lf   \n",clone[j].S.S.x);
        clone[j].F = f(clone[j]);
      }
      f(clone[5]);
      sort(clone.begin(),clone.end(),compare);
      //printf("prev = %lf now  = %lf\n",population[i].F,clone[0].F);
      population[i] = clone[0]; // replace cat with best cloned cats...
    }

    for(int i=n_8;i<n;i++){ // 20% in tracing mode.. Mutate them....
      velocity v = population[i].S.F;
      position p = population[i].S.S;
      v.x += rn*2*(gbest.S.F.x-v.x);
      v.y += rn*2*(gbest.S.F.y-v.y);
      v.z += rn*2*(gbest.S.F.z-v.z);

      p.x += v.x;
      p.y += v.y;
      p.z += v.z;

      population[i].S.F = v;
      population[i].S.S = p;

      population[i].F = f(population[i]);
    }
    sort(population.begin(),population.end(),compare);
    for(int i=0;i<n;i++) cout<<(population[i].F)<<' '; cout<<endl;
  }

  return 0;
}
