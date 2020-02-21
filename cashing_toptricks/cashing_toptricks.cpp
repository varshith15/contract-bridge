#include <bits/stdc++.h>
using namespace std;

bool compare(const pair<int,int> &a,const pair<int,int> &b){
	return a.first>b.first;
}

typedef struct node{
	bool p;
	int t;
	int r;
	string play;
	vector<pair<int,int> > north[4];
	vector<pair<int,int> > south[4];
}nd;

class cashing{
	public:
	vector<pair<int,int> > north[4];
	vector<pair<int,int> > south[4];
	void input();
	void rank();	
	void search();
};

void cashing::input(){
	for(int i=0;i<4;i++){
		string s;
		getline(cin,s);
		istringstream ss(s);
		string x;
		while(ss>>x){
			if(x=="-"){
				continue;
			}
			north[i].push_back({stoi(x),-1});
		}
	}	
	for(int i=0;i<4;i++){
		string s;
		getline(cin,s);
		istringstream ss(s);
		string x;
		while(ss>>x){
			if(x=="-"){
				continue;
			}
			south[i].push_back({stoi(x),-1});
		}
	}
	// for(int i=0;i<4;i++){
	// 	for(int j=0;j<north[i].size();j++){
	// 		cout<<north[i][j].first<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// for(int i=0;i<4;i++){
	// 	for(int j=0;j<south[i].size();j++){
	// 		cout<<south[i][j].first<<" ";
	// 	}
	// 	cout<<endl;
	// }
}

void cashing::rank(){
	vector<pair<int,int> > temp[4];
	for(int i=0;i<4;i++){
		for(int j=0;j<north[i].size();j++){
			temp[i].push_back(north[i][j]);
		}
		for(int j=0;j<south[i].size();j++){
			temp[i].push_back(south[i][j]);
		}
		sort(temp[i].begin(),temp[i].end(),compare);
	}
	// for(int i=0;i<4;i++){
	// 	for(int j=0;j<temp[i].size();j++){
	// 		cout<<temp[i][j].first<<" ";
	// 	}
	// 	cout<<endl;
	// }

	for(int i=0;i<4;i++){
		int check=14;
		int rank=1;
		for(int j=0;j<temp[i].size();j++){
			if(check==temp[i][j].first){
				temp[i][j].second=rank;
				check--;
			}
			else{
				check=temp[i][j].first;
				check--;
				rank++;
				temp[i][j].second=rank;
			}
		}
	}
	for(int i=0;i<4;i++){
		int a=0,b=0;
		for(int j=0;j<temp[i].size();j++){
			if(north[i].size()!=0 && temp[i][j].first==north[i][a].first){
				north[i][a++].second=temp[i][j].second;
			}
			else{
				south[i][b++].second=temp[i][j].second;	
			}
		}
	}

	// for(int i=0;i<4;i++){
	// 	for(int j=0;j<north[i].size();j++){
	// 		cout<<north[i][j].first<<" "<<north[i][j].second<<"  ";
	// 	}
	// 	cout<<endl;
	// }
	// for(int i=0;i<4;i++){
	// 	for(int j=0;j<south[i].size();j++){
	// 		cout<<south[i][j].first<<" "<<south[i][j].second<<"  ";
	// 	}
	// 	cout<<endl;
	// }
}

void cashing::search(){
	//assuming south starts
	int ma=INT_MIN;
	queue<nd> q;
	nd temp;
	temp.p=1;
	temp.t=0;
	temp.r=0;
	temp.play="";
	for(int i=0;i<4;i++){
		temp.north[i]=north[i];
		temp.south[i]=south[i];
		for(int j=0;j<north[i].size();j++){
			if(north[i][j].second==1){
				temp.r++;
			}
		}
		for(int j=0;j<south[i].size();j++){
			if(south[i][j].second==1){
				temp.r++;
			}	
		}
	}
	q.push(temp);
	string line_of_play="";
	while(!q.empty()){
		// cout<<"ll"<<endl;
		temp=q.front();
		q.pop();
		// ma=max(ma,temp.t);
		if(ma<=temp.t){
			ma=temp.t;
			line_of_play=temp.play;
		}
		if(temp.r==0){
			cout<<temp.t<<endl;
			continue;
		}
		if(temp.p==1){
			for(int i=0;i<4;i++){
				for(int j=0;j<temp.south[i].size();j++){
					if(temp.south[i][j].second!=1){
						if(temp.north[i].size()!=0){
							for(int k=0;k<temp.north[i].size();k++){
								if(temp.north[i][k].second==1){
									nd temp1=temp;
									temp1.p=0;
									temp1.t=temp.t+1;
									temp1.r=temp.r-(south[i][j].second==1)-(north[i][k].second==1);
									temp1.play=temp.play+"South plays "+to_string(south[i][j].first)+" "+to_string(i+1)+"\n North plays "+to_string(north[i][k].first)+" "+to_string(i+1)+"\n";
									temp1.north[i].erase(temp1.north[i].begin()+k);
									temp1.south[i].erase(temp1.south[i].begin()+j);
									q.push(temp1);
								}
							}
						}
					}
					else{
						if(temp.north[i].size()!=0){
							for(int k=0;k<temp.north[i].size();k++){
								nd temp1=temp;
								temp1.p=temp.south[i][j].first>north[i][k].first;
								temp1.t=temp.t+1;
								temp1.r=temp.r-(south[i][j].second==1)-(north[i][k].second==1);
								temp1.play=temp.play+"South plays "+to_string(south[i][j].first)+" "+to_string(i+1)+"\n North plays "+to_string(north[i][k].first)+" "+to_string(i+1)+"\n";
								temp1.north[i].erase(temp1.north[i].begin()+k);
								temp1.south[i].erase(temp1.south[i].begin()+j);
								q.push(temp1);
							}
						}
						else{
							for(int a=0;a<4;a++){
								for(int b=0;b<north[a].size();b++){
									nd temp1=temp;
									temp1.p=1;
									temp1.t=temp.t+1;
									temp1.r=temp.r-(south[i][j].second==1)-(north[a][b].second==1);
									temp1.play=temp.play+"South plays "+to_string(south[i][j].first)+" "+to_string(i+1)+"\n North plays "+to_string(north[a][b].first)+" "+to_string(a+1)+"\n";
									temp1.north[a].erase(temp1.north[a].begin()+b);
									temp1.south[i].erase(temp1.south[i].begin()+j);
									q.push(temp1);
								}
							}
						}
					}
				}
			}
		}
		else{
			for(int i=0;i<4;i++){
				for(int j=0;j<temp.north[i].size();j++){
					if(temp.north[i][j].second!=1){
						if(temp.south[i].size()!=0){
							for(int k=0;k<temp.south[i].size();k++){
								if(temp.south[i][k].second==1){
									nd temp1=temp;
									temp1.p=1;
									temp1.t=temp.t+1;
									temp1.r=temp.r-(north[i][j].second==1)-(south[i][k].second==1);
									temp1.play=temp.play+"North plays "+to_string(north[i][j].first)+" "+to_string(i+1)+"\n South plays "+to_string(south[i][k].first)+" "+to_string(i+1)+"\n";
									temp1.south[i].erase(temp1.south[i].begin()+k);
									temp1.north[i].erase(temp1.north[i].begin()+j);
									q.push(temp1);
								}
							}
						}
					}
					else{
						if(temp.south[i].size()!=0){
							for(int k=0;k<temp.south[i].size();k++){
								nd temp1=temp;
								temp1.p=temp.north[i][j].first>south[i][k].first;
								temp1.t=temp.t+1;
								temp1.r=temp.r-(north[i][j].second==1)-(south[i][k].second==1);
								temp1.play=temp.play+"North plays "+to_string(north[i][j].first)+" "+to_string(i+1)+"\n South plays "+to_string(south[i][k].first)+" "+to_string(i+1)+"\n";
								temp1.south[i].erase(temp1.south[i].begin()+k);
								temp1.north[i].erase(temp1.north[i].begin()+j);
								q.push(temp1);
							}
						}
						else{
							for(int a=0;a<4;a++){
								for(int b=0;b<south[a].size();b++){
									nd temp1=temp;
									temp1.p=0;
									temp1.t=temp.t+1;
									temp1.r=temp.r-(north[i][j].second==1)-(south[a][b].second==1);
									temp1.play=temp.play+"North plays "+to_string(north[i][j].first)+" "+to_string(i+1)+"\n South plays "+to_string(south[a][b].first)+" "+to_string(a+1)+"\n";
									temp1.south[a].erase(temp1.south[a].begin()+b);
									temp1.north[i].erase(temp1.north[i].begin()+j);
									q.push(temp1);
								}
							}
						}
					}
				}
			}
		}
	}
	cout<<"max top tricks: "<<ma<<endl;
	cout<<line_of_play;
}

int main(){
	cashing c;
	c.input();
	c.rank();
	c.search();
	return 0;
}