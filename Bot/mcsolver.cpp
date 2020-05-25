#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include "print.h"

using namespace std;


map<char,int> se;
map<char,int> ce;
map<int,char> ce1;
map<int,char> he;
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

he[0]='N';
he[1]='E';
he[2]='S';
he[3]='W';

	cout<<"Suit Encoding: "<<endl;
	cout<<"SPADES   \xE2\x99\xA0  ---------  0"<<endl;
	cout<<"HEARTS   \xE2\x99\xA5  ---------  1"<<endl;
	cout<<"DIAMONDS \xE2\x99\xA6  ---------  2"<<endl;
	cout<<"CLUBS    \xE2\x99\xA3  ---------  3"<<endl;
	cout<<"NO TRUMP    ---------  4"<<endl;
	cout<<endl;
	cout<<"Hand Encoding: "<<endl;
	cout<<"NORTH  --------  0"<<endl;
	cout<<"EAST   --------  1"<<endl;
	cout<<"SOUTH  --------  2"<<endl;
	cout<<"WEST   --------  3"<<endl;
	cout<<endl;
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
	set<string> check;
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
		if(check.find(temp)!=check.end()){
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
		// cout<<pbn[i]<<endl;
		// char title[100];
		// char phand[200];
		// strcpy(title,"ll");
		// strcpy(phand,("N:"+pbn[i]).c_str());
		// PrintPBNHand(title,phand);
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
	pair<int,char> tp={-1,'P'};
	pair<int,char> ans={-1,'P'};
	for(auto i=best.begin();i!=best.end();i++){
		pair<int,char> ll=i->first;
		cout<<sye[ll.first]<<" "<<ll.second<<" "<<i->second<<endl;
	}
	for(auto i=best.begin();i!=best.end();i++){
		pair<int,char> ll=i->first;
		// cout<<ll.first<<" "<<ll.second<<" "<<i->second<<endl;
		if(i->second==ma){
			if(ans==tp){
				ans=i->first;
			}
			else if(ce[ans.second]>ce[(i->first).second]){
				ans=i->first;
			}
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

vector<string> remainingcards(vector<vector<string> > diff , vector<vector<string> > cards_played){
	vector<string> remhands(4,"");
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			string h=diff[i][j];
			string c=cards_played[i][j];
			string temp="";
			for(int a=0;a<h.size();a++){
				bool flag=1;
				for(int b=0;b<c.size();b++){
					if(h[a]==c[b]){
						flag=0;
						break;
					}
				}
				if(flag){
					temp=temp+h[a];
				}
			}
			if(j!=3){
				remhands[i]=remhands[i]+temp+".";
			}
			else{
				remhands[i]=remhands[i]+temp;
			}
		}
	}
	return remhands;
}

int main(){
	encoding();
	
	int trump;
	int first;
	int dec;
	cout<<"Trump Suit:";
	cin>>trump;
	cout<<"First Hand:";
	cin>>first;
	cout<<"Declarer:";
	cin>>dec;
	cin.ignore();
	cout<<"Deal in PBN format:";
	string deal;
	getline(cin,deal);
	vector<string> ha;
	boost::split(ha,deal,boost::is_any_of(" "));
	string north = ha[(0+dec)%4];
	string east = ha[(1+dec)%4];
	string south = ha[(2+dec)%4];
	string west = ha[(3+dec)%4];
	first = (first-dec+4)%4;
	ha[0]=north;
	ha[1]=east;
	ha[2]=south;
	ha[3]=west;
	int won=0;

	vector<vector<string> > hands(4,vector<string>(4,""));
	vector<vector<string> > diff(4,vector<string>(4,""));
	vector<vector<string> > cards_played(4,vector<string>(4,""));

	vector<string> su; 
    boost::split(su, north, boost::is_any_of("."));
    for(int i=0;i<4;i++){
    	diff[0][i]=su[i];
    }
    boost::split(su, east, boost::is_any_of("."));
    for(int i=0;i<4;i++){
    	diff[1][i]=su[i];
    }
    boost::split(su, south, boost::is_any_of("."));
    for(int i=0;i<4;i++){
    	diff[2][i]=su[i];
    }
    boost::split(su, west, boost::is_any_of("."));
    for(int i=0;i<4;i++){
    	diff[3][i]=su[i];
    }

    hands[0]=diff[0];
    hands[2]=diff[2];
    // for(int i=0;i<4;i++){
    // 	for(int j=0;j<4;j++){
    // 		cout<<hands[i][j]<<" ";
    // 	}
    // 	cout<<endl;
    // }
	int tricks=0;
	while((tricks++)<13){
		int tsuit=-1;
		vector<pair<int,int> > played(4,{0,0});
		for(int c=0;c<4;c++){
			// cout<<endl;
			cout<<"Press C to continue!"<<endl;
			string cs;
			while(cin>>cs){
			cout << "\033[2J\033[1;1H";
				break;
			}
			cout<<endl;
			
			cout<<"Suit Encoding: "<<endl;
			cout<<"SPADES   \xE2\x99\xA0  ---------  0"<<endl;
			cout<<"HEARTS   \xE2\x99\xA5  ---------  1"<<endl;
			cout<<"DIAMONDS \xE2\x99\xA6  ---------  2"<<endl;
			cout<<"CLUBS    \xE2\x99\xA3  ---------  3"<<endl;
			cout<<"NO TRUMP    ---------  4"<<endl;
			cout<<endl;

			if(c!=0){
				cout<<"Cards Played Previously in the Trick: "<<endl;
				for(int pl=0;pl<c;pl++){
					cout<<sye[played[pl].first]<<" "<<ce1[played[pl].second]<<endl;
				}
			}
			int ch=(first+c)%4;
			if(ch%2==0){
				cout<<he[(ch+dec)%4]<<" turn to play."<<endl;
				samples(hands);
				vector<string> pb = pbn(cards_played);
				// for(int i=0;i<pb.size();i++){
				// 	cout<<pb[i]<<endl;
				// }
				// cout<<"pbn done!"<<endl;
				// solve(trump,first,pb,played);	
				pair<int,char> ans=solve(trump,first,pb,played);
				// cout<<"solve done!"<<endl;
				cout<<"Playing: "<<sye[ans.first]<<" "<<ans.second<<endl;
				if(tsuit==-1){
					tsuit=ans.first;
				}
				played[c].first=ans.first;
				played[c].second=ce[ans.second];
				// hands[ch][ans.first]+=hands[ch][ans.first]+ans.second;
				cards_played[ch][ans.first]=cards_played[ch][ans.first]+ans.second;
			}
			else{
				cout<<he[(ch+dec)%4]<<" turn to play."<<endl;
				vector<string> remhands = remainingcards(diff,cards_played);
				string print;
				if(ch==1){
					vector<string> format(4,"...");
					format[(ch+dec)%4]=remhands[1];
					format[(dec+2)%4]=remhands[2];
					print="N:"+format[0]+" "+format[1]+" "+format[2]+" "+format[3];
				}
				else if(ch==3){
					vector<string> format(4,"...");
					format[(ch+dec)%4]=remhands[3];
					format[(dec+2)%4]=remhands[2];
					print="N:"+format[0]+" "+format[1]+" "+format[2]+" "+format[3];
				}
				// cout<<print<<endl;
				// print="N:A.2.3.4 ... ... ...";
				char title[100];
				char cprint[1000];
				strcpy(title,"lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll");
				strcpy(cprint,print.c_str());
				PrintPBNHand(title,cprint);
				vector<string> remcards;
				boost::split(remcards, remhands[ch], boost::is_any_of("."));
				cout<<"Suit in number:";
				int suit;
				// cin>>suit;
				while(cin>>suit){
					if(tsuit==-1){
						tsuit=suit;
						break;
					}
					if(remcards[tsuit]==""){
						break;
					}
					if(tsuit!=suit){
						cout<<"Wrong Suit Played Try Again!"<<endl;
						cout<<"Playable Suit is: "<<tsuit<<endl;
						cout<<"Suit in number:";
					}
					else{
						break;
					}
				}
				played[c].first=suit;
				cout<<"Card in char:";
				char card;
				cin>>card;
				while(cin>>card){
					bool flg=false;
					for(int f=0;f<remcards[suit].size();f++){
						if(remcards[suit][f]==card){
							flg=true;
							break;
						}
					}
					if(!flg){
						cout<<"You don't hold that Card! Try Again!"<<endl;
						cout<<"Playable Cards are: "<<remcards[suit]<<endl;
						cout<<"Card in char:";
					}
					else{
						break;
					}
				}
				played[c].second=ce[card];
				hands[ch][suit]=hands[ch][suit]+card;
				cards_played[ch][suit]=cards_played[ch][suit]+card;
			}
		}
		cout<<endl;
		cout<<tricks<<" tricks done!"<<endl;
		// cout<<endl;
		int ma=played[0].second;
		int tch=played[0].first;
		int ind=first;
		for(int i=1;i<4;i++){
			if(played[i].first==trump && tch!=trump){
				tch=trump;
				ma=-1;
			}
			if(tch==played[i].first && ma<played[i].second){
				ma=played[i].second;
				ind=(i+first)%4;
			}
		}
		if(ind%2==0){
			won++;
		}
		first=ind;
		cout<<he[(ind+dec)%4]<<" won the trick!"<<endl;
		cout<<endl;
	}
	cout<<"Tricks Won by North-South: ";
	cout<<won<<endl;
}