#include <bits/stdc++.h>
using namespace std;

int main(){
	vector<vector<string> > ll(4,vector<string>(4,""));
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(ll[i][j]==""){
				cout<<ll[i][j].size()<<" ";
			}
		}
		cout<<endl;
	}
}