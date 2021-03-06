#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

using namespace std;

map<char,int> se;
map<char,int> ce;
map<int,char> ce1;
map<int,char> he;

void encoding(){
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

he[0]='N';
he[1]='E';
he[2]='S';
he[3]='W';
}

void samples(vector<vector<string> > hands){
	vector<string> temp(4,"");
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(hands[i][j]==""){
				temp[i]+="- ";
			}
			else{
				temp[i]+=hands[i][j]+" ";
			}
		}
	}
	string predeal = "redeal -N '"+temp[0]+"' -E '"+temp[1]+"' -S '"+temp[2]+"' -W '"+temp[3]+"' -n 50 > samples.txt";
	// cout<<predeal<<endl;
	char cmd[1000];
	strcpy(cmd,predeal.c_str());
	system(cmd);
}


string pbn_util(string s,vector<string> played){
	string pbn="";
	int ind=0;
	for(int i=3;i<s.size();i++){
		if(isalnum(s[i])){
			string check=played[ind];
			bool flag = false;
			for(int j=0;j<check.size();j++){
				if(s[i]==check[j]){
					flag=true;
					continue;
				}
			}
			if(!flag){
				pbn=pbn+s[i];
			}
		}
		else{
			i=i+2;
			pbn=pbn+".";
			ind++;
		}
	}
	return pbn;
}

vector<string> pbn(vector<vector<string> > cards_played){
	ifstream inf;
	inf.open("samples.txt");
	if(!inf){
		cout<<"Unable to open samples.txt!"<<endl;
		exit(1);
	}
	vector<string> pbn;
	string s;
	while(inf>>s){
		if(s[0]=='T'){
			continue;
		}
		string temp="";
		temp=pbn_util(s,cards_played[0]);
		inf>>s;
		temp=temp+" "+pbn_util(s,cards_played[1]);
		inf>>s;
		temp=temp+" "+pbn_util(s,cards_played[2]);
		inf>>s;
		temp=temp+" "+pbn_util(s,cards_played[3]);
		if(temp=="" || temp[0]==' '){
			continue;
		}
		pbn.push_back(temp);
		// cout<<temp<<endl;
	}
	inf.close();
	return pbn;
}

pair<int,char> solve(int trump,int first,vector<string> pbn,vector<pair<int,int> > played){
	// cout<<"lol"<<endl;
	map<pair<int,char>,int> best;
	int ma=INT_MIN;
	// cout<<pbn.size()<<endl;
	for(int i=0;i<pbn.size();i++){
		// cout<<i<<" pbn "<<best.size()<<endl;
		ofstream ouf;
		ouf.open("inp.txt");
		ouf<<trump<<endl;
		ouf<<first<<endl;
		for(int j=0;j<3;j++){
			ouf<<played[j].first<<endl;
		}
		for(int j=0;j<3;j++){
			ouf<<played[j].second<<endl;
		}
		ouf<<pbn[i]<<endl;
		char cmd[100];
		strcpy(cmd,"./SolveBoardPBN");
		system(cmd);
		ifstream inf;
		inf.open("tt.txt");
		string ss;
		while(inf>>ss){
			inf>>ss;
			int suit=se[ss[0]];
			inf>>ss;
			char card=ss[0];
			inf>>ss;
			string temp;
			inf>>temp;
			int val=stoi(temp);
			best[{suit,card}]+=val;
			ma=max(ma,best[{suit,card}]);
			if(ss=="-"){
				continue;
			}
			for(int j=0;j<ss.size();j++){
				best[{suit,ss[j]}]+=val;
				ma=max(ma,best[{suit,ss[j]}]);
			}
		}
	}
	cout<<ma<<endl;
	pair<int,char> ans;
	for(auto i=best.begin();i!=best.end();i++){
		pair<int,char> ll=i->first;
		cout<<ll.first<<" "<<ll.second<<" "<<i->second<<endl;
		if(i->second==ma){
			ans=i->first;
		}
	}
	// cout<<"done pplplp"<<endl;
	return ans;
}

//int main(){
	// vector<vector<string> > hands(4,vector<string>(4,""));
	// hands[0][0]="QJ6";
	// hands[0][1]="K652";
	// hands[0][2]="J85";
	// hands[0][3]="T98";
	// hands[2][0]="K5";
	// hands[2][1]="T83";
	// hands[2][2]="KQ9";
	// hands[2][3]="A7652";
	// hands[1][0]="A";
	// hands[3][0]="2";
	// vector<vector<string> > cards_played(4,vector<string>(4,""));
	// cards_played[0][0]="Q";
	// cards_played[2][0]="K";
	// cards_played[1][0]="A";
	// cards_played[3][0]="2";
	// // samples(hands);
	// vector<string> pbn=solve(cards_played);
//}

int main(){
	encoding();
	
	int trump;
	int first;
	cout<<"Trump:";
	cin>>trump;
	cout<<"First:";
	cin>>first;

	string north;
	cout<<"North:";
	cin>>north;
	string south;
	cout<<"South:";
	cin>>south;

	int won=0;

	vector<vector<string> > hands(4,vector<string>(4,""));
	vector<vector<string> > cards_played(4,vector<string>(4,""));

	vector<string> su; 
    boost::split(su, north, boost::is_any_of("."));
    for(int i=0;i<4;i++){
    	hands[0][i]=su[i];
    }
    boost::split(su, south, boost::is_any_of("."));
    for(int i=0;i<4;i++){
    	hands[2][i]=su[i];
    }

    // for(int i=0;i<4;i++){
    // 	for(int j=0;j<4;j++){
    // 		cout<<hands[i][j]<<" ";
    // 	}
    // 	cout<<endl;
    // }
	
	int tricks=0;
	while((tricks++)<13){
		vector<pair<int,int> > played(4,{0,0});
		for(int c=0;c<4;c++){
			// cout<<c<<endl;
			int ch=(first+c)%4;
			if(ch%2==0){
				cout<<he[ch]<<" turn to play."<<endl;
				samples(hands);
				vector<string> pb = pbn(cards_played);
				// for(int i=0;i<pb.size();i++){
				// 	cout<<pb[i]<<endl;
				// }
				// cout<<"pbn done!"<<endl;
				// solve(trump,first,pb,played);	
				pair<int,char> ans=solve(trump,first,pb,played);
				// cout<<"solve done!"<<endl;
				cout<<"Playing: "<<ans.first<<" "<<ans.second<<endl;
				played[c].first=ans.first;
				played[c].second=ce[ans.second];
				// hands[ch][ans.first]+=hands[ch][ans.first]+ans.second;
				cards_played[ch][ans.first]=cards_played[ch][ans.first]+ans.second;
			}
			else{
				cout<<he[ch]<<" turn to play."<<endl;
				cout<<"Suit:";
				int suit;
				cin>>suit;
				played[c].first=suit;
				cout<<"Card:";
				char card;
				cin>>card;
				played[c].second=ce[card];
				hands[ch][suit]=hands[ch][suit]+card;
				cards_played[ch][suit]=cards_played[ch][suit]+card;
			}
		}
		cout<<tricks<<" tricks done!"<<endl;
		int ma=played[first].second;
		int ind=first;
		for(int i=1;i<4;i++){
			if(played[first].first==played[i].first && ma<played[i].second){
				ma=played[i].second;
				ind=(i+first)%4;
			}
		}
		if(ind%2==0){
			won++;
		}
		first=ind;
	}
	cout<<won<<endl;
}