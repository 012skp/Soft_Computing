#include<bits/stdc++.h>

int main(){
  for(int i=0;i<100;i++) for(int j=0;j<100;j++) {
    char cmd[100];
    sprintf(cmd,"./cd %d %d >> output",i,j);
    system(cmd);
  }
}
