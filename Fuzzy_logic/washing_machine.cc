#include<bits/stdc++.h>
using namespace std;

#define WT 100

int main(){
double  dirty,greasy;
cin>>dirty>>greasy;
double washing_time = WT*(dirty+greasy)/100;
cout<<"washing time "<<washing_time<<endl;
return 0;
}
