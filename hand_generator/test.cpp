#include <bits/stdc++.h>
using namespace std;

int main(){
	char cmd[1000];
	string predeal = "./a.out <inp.txt";
	strcpy(cmd,predeal.c_str());
	for(int i=0;i<10;i++){
		system(cmd);
	}

}