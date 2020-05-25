#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
using namespace std;

map<char,int> se;
map<char,int> ce;
map<int,char> ce1;
map<int,string> sye;

void encoding(){

sye[0]="\xE2\x99\xA0";
sye[3]="\xE2\x99\xA3";
sye[1]="\xE2\x99\xA5";
sye[2]="\xE2\x99\xA6";

ce1[2]='2';
ce1[3]='3';
ce1[4]='4';
ce1[5]='5';
ce1[6]='6';
ce1[7]='7';
ce1[8]='8';
ce1[9]='9';
ce1[10]='T';
ce1[11]='J';
ce1[12]='Q';
ce1[13]='K';
ce1[14]='A';

se['S']=0;
se['H']=1;
se['D']=2;
se['C']=3;

ce['2']=2;
ce['3']=3;
ce['4']=4;
ce['5']=5;
ce['6']=6;
ce['7']=7;
ce['8']=8;
ce['9']=9;
ce['T']=10;
ce['J']=11;
ce['Q']=12;
ce['K']=13;
ce['A']=14;
}

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
	int ul; //upperlimit
	void input();
	void rank();	
	void search();
	void optsearch();
};

void cashing::input(){
	string deal;
	getline(cin,deal);
	vector<string> su;
	boost::split(su,deal,boost::is_any_of(" "));
	vector<string> ll;
	boost::split(ll,su[0],boost::is_any_of("."));
	for(int i=0;i<4;i++){
		for(int j=0;j<ll[i].size();j++){
			north[i].push_back({ce[ll[i][j]],-1});
		}
	}
	boost::split(ll,su[1],boost::is_any_of("."));
	for(int i=0;i<4;i++){
		for(int j=0;j<ll[i].size();j++){
			south[i].push_back({ce[ll[i][j]],-1});
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
	int u=0;
	for(int i=0;i<4;i++){
		int o=0,no=0,o1=0,no1=0;
		for(int j=0;j<north[i].size();j++){
			if(north[i][j].second==1){
				o++;
			}
			else{
				no++;
			}
		}
		for(int j=0;j<south[i].size();j++){
			if(south[i][j].second==1){
				o1++;
			}
			else{
				no1++;
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
			// cout<<temp.t<<endl;
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
									temp1.r=temp.r-(temp.south[i][j].second==1)-(temp.north[i][k].second==1);
									temp1.play=temp.play+"South plays "+sye[i]+" "+ce1[temp.south[i][j].first]+"\nNorth plays "+sye[i]+" "+ce1[temp.north[i][k].first]+"\n";
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
								temp1.p=temp.south[i][j].first>temp.north[i][k].first;
								temp1.t=temp.t+1;
								temp1.r=temp.r-(temp.south[i][j].second==1)-(temp.north[i][k].second==1);
								temp1.play=temp.play+"South plays "+sye[i]+" "+ce1[temp.south[i][j].first]+"\nNorth plays "+sye[i]+" "+ce1[temp.north[i][k].first]+"\n";
								temp1.north[i].erase(temp1.north[i].begin()+k);
								temp1.south[i].erase(temp1.south[i].begin()+j);
								q.push(temp1);
							}
						}
						else{
							for(int a=0;a<4;a++){
								for(int b=0;b<temp.north[a].size();b++){
									nd temp1=temp;
									temp1.p=1;
									temp1.t=temp.t+1;
									temp1.r=temp.r-(temp.south[i][j].second==1)-(temp.north[a][b].second==1);
									temp1.play=temp.play+"South plays "+sye[i]+" "+ce1[temp.south[i][j].first]+"\nNorth plays "+sye[a]+" "+ce1[temp.north[a][b].first]+"\n";
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
									temp1.r=temp.r-(temp.north[i][j].second==1)-(temp.south[i][k].second==1);
									temp1.play=temp.play+"North plays "+sye[i]+" "+ce1[temp.north[i][j].first]+"\nSouth plays "+sye[i]+" "+ce1[temp.south[i][k].first]+"\n";
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
								temp1.r=temp.r-(temp.north[i][j].second==1)-(temp.south[i][k].second==1);
								temp1.play=temp.play+"North plays "+sye[i]+" "+ce1[temp.north[i][j].first]+"\nSouth plays "+sye[i]+" "+ce1[temp.south[i][k].first]+"\n";
								temp1.south[i].erase(temp1.south[i].begin()+k);
								temp1.north[i].erase(temp1.north[i].begin()+j);
								q.push(temp1);
							}
						}
						else{
							for(int a=0;a<4;a++){
								for(int b=0;b<temp.south[a].size();b++){
									nd temp1=temp;
									temp1.p=0;
									temp1.t=temp.t+1;
									temp1.r=temp.r-(temp.north[i][j].second==1)-(temp.south[a][b].second==1);
									temp1.play=temp.play+"North plays "+sye[i]+" "+ce1[temp.north[i][j].first]+"\nSouth plays "+sye[a]+" "+ce1[temp.south[a][b].first]+"\n";
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

void cashing::optsearch(){
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
		nd temp = q.front();
		q.pop();
		if(ma<=temp.t){
			ma=temp.t;
			line_of_play=temp.play;
			cout<<temp.play<<endl;
		}
		if(temp.r==0){
			cout<<temp.t<<endl;
			continue;
		}
		if(temp.p==1){
			for(int i=0;i<4;i++){
				if(temp.south[i].size()==0){
					continue;
				}
				if(temp.north[i].size()==0){
					for(int j=0;j<4;j++){
						if(temp.north[j].size()==0){
							continue;
						}
						if(temp.south[i][0].second==1){
							nd temp1 = temp;
							temp1.p=1;
							temp1.t=temp.t+1;
							temp1.r=temp.r-(temp.south[i][0].second==1)-(temp.north[j][0].second==1);
							temp1.play = temp.play+"South plays "+to_string(temp.south[i][0].first)+" "+to_string(i+1)+"\nNorth plays "+to_string(temp.north[j][0].first)+" "+to_string(j+1)+"\n";
							temp1.south[i].erase(temp1.south[i].begin());
							temp1.north[j].erase(temp1.north[j].begin());
							q.push(temp1);
							if(temp.north[j].size()==1){
								continue;
							}
							int la=temp.north[j].size();
							temp1=temp;
							temp1.p=1;
							temp1.t=temp.t+1;
							temp1.r=temp.r-(temp.south[i][0].second==1)-(temp.north[j][la-1].second==1);
							temp1.play = temp.play+"South plays "+to_string(temp.south[i][0].first)+" "+to_string(i+1)+"\nNorth plays "+to_string(temp.north[j][la-1].first)+" "+to_string(j+1)+"\n";
							temp1.south[i].erase(temp1.south[i].begin());
							temp1.north[j].erase(temp1.north[j].begin()+la-1);
							q.push(temp1);
						}
					}
					if(temp.south[i].size()==1){
						continue;
					}
					for(int j=0;j<4;j++){
						int ls=temp.south[i].size();
						if(temp.north[j].size()==0){
							continue;
						}
						if(temp.south[i][ls-1].second==1){
							nd temp1 = temp;
							temp1.p=1;
							temp1.t=temp.t+1;
							temp1.r=temp.r-(temp.south[i][ls-1].second==1)-(temp.north[j][0].second==1);
							temp1.play = temp.play+"South plays "+to_string(temp.south[i][ls-1].first)+" "+to_string(i+1)+"\nNorth plays "+to_string(temp.north[j][0].first)+" "+to_string(j+1)+"\n";
							temp1.south[i].erase(temp1.south[i].begin()+ls-1);
							temp1.north[j].erase(temp1.north[j].begin());
							q.push(temp1);
							if(temp.north[j].size()==1){
								continue;
							}
							int la=temp.north[j].size();
							temp1=temp;
							temp1.p=1;
							temp1.t=temp.t+1;
							temp1.r=temp.r-(temp.south[i][ls-1].second==1)-(temp.north[j][la-1].second==1);
							temp1.play = temp.play+"South plays "+to_string(temp.south[i][ls-1].first)+" "+to_string(i+1)+"\nNorth plays "+to_string(temp.north[j][la-1].first)+" "+to_string(j+1)+"\n";
							temp1.south[i].erase(temp1.south[i].begin()+ls-1);
							temp1.north[j].erase(temp1.north[j].begin()+la-1);
							q.push(temp1);
						}
					}
				}
				else{
					if(temp.south[i][0].second==1 || temp.north[i][0].second==1){
						nd temp1 = temp;
						temp1.p = temp.south[i][0].first>temp.north[i][0].first;
						temp1.t=temp.t+1;
						temp1.r = temp.r-(temp.south[i][0].second==1)-(temp.north[i][0].second==1);
						temp1.play = temp.play+"South plays "+to_string(temp.south[i][0].first)+" "+to_string(i+1)+"\nNorth plays "+to_string(temp.north[i][0].first)+" "+to_string(i+1)+"\n";
						temp1.south[i].erase(temp1.south[i].begin());
						temp1.north[i].erase(temp1.north[i].begin());
						q.push(temp1);
					}
					if(temp.south[i].size()>1 && (temp.south[i][temp.south[i].size()-1].second==1 || temp.north[i][0].second==1)){
						nd temp1 = temp;
						temp1.p = temp.south[i][temp.south[i].size()-1].first>temp.north[i][0].first;
						temp1.t=temp.t+1;
						temp1.r = temp.r-(temp.south[i][temp.south[i].size()-1].second==1)-(temp.north[i][0].second==1);
						temp1.play = temp.play+"South plays "+to_string(temp.south[i][temp.south[i].size()-1].first)+" "+to_string(i+1)+"\nNorth plays "+to_string(temp.north[i][0].first)+" "+to_string(i+1)+"\n";
						temp1.south[i].erase(temp1.south[i].begin()+temp.south[i].size()-1);
						temp1.north[i].erase(temp1.north[i].begin());
						q.push(temp1);
					}
					if(temp.north[i].size()>1 && (temp.south[i][0].second==1 || temp.north[i][temp.north[i].size()-1].second==1)){
						nd temp1 = temp;
						temp1.p = temp.south[i][0].first>temp.north[i][temp.north[i].size()-1].first;
						temp1.t=temp.t+1;
						temp1.r = temp.r-(temp.south[i][0].second==1)-(temp.north[i][temp.north[i].size()-1].second==1);
						temp1.play = temp.play+"South plays "+to_string(temp.south[i][0].first)+" "+to_string(i+1)+"\nNorth plays "+to_string(temp.north[i][temp.north[i].size()-1].first)+" "+to_string(i+1)+"\n";
						temp1.south[i].erase(temp1.south[i].begin());
						temp1.north[i].erase(temp1.north[i].begin()+temp.north[i].size()-1);
						q.push(temp1);
					}
					if(temp.south[i].size()>1 && temp.north[i].size()>1 && (temp.south[i][temp.south[i].size()-1].second==1 || temp.north[i][temp.north[i].size()-1].second==1)){
						nd temp1 = temp;
						temp1.p = temp.south[i][temp.south[i].size()-1].first>temp.north[i][temp.north[i].size()-1].first;
						temp1.t=temp.t+1;
						temp1.r = temp.r-(temp.south[i][temp.south[i].size()-1].second==1)-(temp.north[i][temp.north[i].size()-1].second==1);
						temp1.play = temp.play+"South plays "+to_string(temp.south[i][temp.south[i].size()-1].first)+" "+to_string(i+1)+"\nNorth plays "+to_string(temp.north[i][temp.north[i].size()-1].first)+" "+to_string(i+1)+"\n";
						temp1.south[i].erase(temp1.south[i].begin()+temp.south[i].size()-1);
						temp1.north[i].erase(temp1.north[i].begin()+temp.north[i].size()-1);
						q.push(temp1);
					}
				}
			}
		}
		else{
			for(int i=0;i<4;i++){
				if(temp.north[i].size()==0){
					continue;
				}
				if(temp.south[i].size()==0){
					for(int j=0;j<4;j++){
						if(temp.south[j].size()==0){
							continue;
						}
						if(temp.north[i][0].second==1){
							nd temp1 = temp;
							temp1.p=0;
							temp1.r=temp.r-(temp.north[i][0].second==1)-(temp.south[j][0].second==1);
							temp1.t=temp.t+1;
							temp1.play = temp.play+"North plays "+to_string(temp.north[i][0].first)+" "+to_string(i+1)+"\nSouth plays "+to_string(temp.south[j][0].first)+" "+to_string(j+1)+"\n";
							temp1.north[i].erase(temp1.north[i].begin());
							temp1.south[j].erase(temp1.south[j].begin());
							q.push(temp1);
							if(temp.south[j].size()==1){
								continue;
							}
							int la=temp.south[j].size();
							temp1=temp;
							temp1.p=0;
							temp1.t=temp.t+1;
							temp1.r=temp.r-(temp.north[i][0].second==1)-(temp.south[j][la-1].second==1);
							temp1.play = temp.play+"North plays "+to_string(temp.north[i][0].first)+" "+to_string(i+1)+"\nSouth plays "+to_string(temp.south[j][la-1].first)+" "+to_string(j+1)+"\n";
							temp1.north[i].erase(temp1.north[i].begin());
							temp1.south[j].erase(temp1.south[j].begin()+la-1);
							q.push(temp1);
						}
					}
					if(temp.north[i].size()==1){
						continue;
					}
					for(int j=0;j<4;j++){
						int ls=temp.north[i].size();
						if(temp.south[j].size()==0){
							continue;
						}
						if(temp.north[i][ls-1].second==1){
							nd temp1 = temp;
							temp1.p=0;
							temp1.t=temp.t+1;
							temp1.r=temp.r-(temp.north[i][ls-1].second==1)-(temp.south[j][0].second==1);
							temp1.play = temp.play+"North plays "+to_string(temp.north[i][ls-1].first)+" "+to_string(i+1)+"\nSouth plays "+to_string(temp.south[j][0].first)+" "+to_string(j+1)+"\n";
							temp1.north[i].erase(temp1.north[i].begin()+ls-1);
							temp1.south[j].erase(temp1.south[j].begin());
							q.push(temp1);
							if(temp.south[j].size()==1){
								continue;
							}
							int la=temp.south[j].size();
							temp1=temp;
							temp1.p=0;
							temp1.t=temp.t+1;
							temp1.r=temp.r-(temp.north[i][ls-1].second==1)-(temp.south[j][la-1].second==1);
							temp1.play = temp.play+"North plays "+to_string(temp.north[i][ls-1].first)+" "+to_string(i+1)+"\nSouth plays "+to_string(temp.south[j][la-1].first)+" "+to_string(j+1)+"\n";
							temp1.north[i].erase(temp1.north[i].begin()+ls-1);
							temp1.south[j].erase(temp1.south[j].begin()+la-1);
							q.push(temp1);
						}
					}
				}
				else{
					if(temp.north[i][0].second==1 || temp.south[i][0].second==1){
						nd temp1 = temp;
						temp1.p = temp.north[i][0].first<temp.south[i][0].first;
						temp1.t=temp.t+1;
						temp1.r = temp.r-(temp.north[i][0].second==1)-(temp.south[i][0].second==1);
						temp1.play = temp.play+"North plays "+to_string(temp.north[i][0].first)+" "+to_string(i+1)+"\nSouth plays "+to_string(temp.south[i][0].first)+" "+to_string(i+1)+"\n";
						temp1.north[i].erase(temp1.north[i].begin());
						temp1.south[i].erase(temp1.south[i].begin());
						q.push(temp1);
					}
					if(temp.north[i].size()>1 && (temp.north[i][temp.north[i].size()-1].second==1 || temp.south[i][0].second==1)){
						nd temp1 = temp;
						temp1.p = temp.north[i][temp.north[i].size()-1].first<temp.south[i][0].first;
						temp1.t=temp.t+1;
						temp1.r = temp.r-(temp.north[i][temp.north[i].size()-1].second==1)-(temp.south[i][0].second==1);
						temp1.play = temp.play+"North plays "+to_string(temp.north[i][temp.north[i].size()-1].first)+" "+to_string(i+1)+"\nSouth plays "+to_string(temp.south[i][0].first)+" "+to_string(i+1)+"\n";
						temp1.north[i].erase(temp1.north[i].begin()+temp.north[i].size()-1);
						temp1.south[i].erase(temp1.south[i].begin());
						q.push(temp1);
					}
					if(temp.south[i].size()>1 && (temp.north[i][0].second==1 || temp.south[i][temp.south[i].size()-1].second==1)){
						nd temp1 = temp;
						temp1.p = temp.north[i][0].first<temp.south[i][temp.south[i].size()-1].first;
						temp1.t=temp.t+1;
						temp1.r = temp.r-(temp.north[i][0].second==1)-(temp.south[i][temp.south[i].size()-1].second==1);
						temp1.play = temp.play+"North plays "+to_string(temp.north[i][0].first)+" "+to_string(i+1)+"\nSouth plays "+to_string(temp.south[i][temp.south[i].size()-1].first)+" "+to_string(i+1)+"\n";
						temp1.north[i].erase(temp1.north[i].begin());
						temp1.south[i].erase(temp1.south[i].begin()+temp.south[i].size()-1);
						q.push(temp1);
					}
					if(temp.north[i].size()>1 && temp.south[i].size()>1 && (temp.north[i][temp.north[i].size()-1].second==1 || temp.south[i][temp.south[i].size()-1].second==1)){
						nd temp1 = temp;
						temp1.p = temp.north[i][temp.north[i].size()-1].first<temp.south[i][temp.south[i].size()-1].first;
						temp1.t=temp.t+1;
						temp1.r = temp.r-(temp.north[i][temp.north[i].size()-1].second==1)-(temp.south[i][temp.south[i].size()-1].second==1);
						temp1.play = temp.play+"North plays "+to_string(temp.north[i][temp.north[i].size()-1].first)+" "+to_string(i+1)+"\nSouth plays "+to_string(temp.south[i][temp.south[i].size()-1].first)+" "+to_string(i+1)+"\n";
						temp1.north[i].erase(temp1.north[i].begin()+temp.north[i].size()-1);
						temp1.south[i].erase(temp1.south[i].begin()+temp.south[i].size()-1);
						q.push(temp1);
					}
				}
			}
		}
	}
	cout<<"max top tricks: "<<ma<<endl;
	cout<<line_of_play;
}


int main(){
	encoding();
	cashing c;
	c.input();
	c.rank();
	c.search();
	return 0;
}