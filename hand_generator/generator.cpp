#include <bits/stdc++.h>
using namespace std;

void encoding(map<char,int> &rank){
    rank['A']=0;
    rank['K']=1;
    rank['Q']=2;
    rank['J']=3;
    rank['T']=4;
    rank['9']=5;
    rank['8']=6;
    rank['7']=7;
    rank['6']=8;
    rank['5']=9;
    rank['4']=10;
    rank['3']=11;
    rank['2']=12;
}

bool hpc_check(vector<vector<string> > cards,vector<int> hcp){
    map<char,int> points;
    points['A']=4;
    points['K']=3;
    points['Q']=2;
    points['J']=1;

    for(int i=0;i<4;i++){
        if(hcp[i]==-1){
            continue;
        }
        int sc=0;
        for(int j=0;j<4;j++){
            string h=cards[i][j];
            for(int k=0;k<h.size();k++){
                sc+=points[h[k]];
            }
        }
        if(sc<hcp[i]){
            return false;
        }
    }
    return true;
}

vector<vector<string> > generate(vector<vector<int> > grid, vector<vector<int> > len, vector<int> suitl, vector<int> handl, vector<vector<string> > cards,vector<string>left){
    // cout<<"pp"<<endl;
    srand((unsigned) time(NULL));
    // cout<<"pp1"<<endl;
    // for(int i=0;i<4;i++){
    // 	cout<<handl[i]<<" "<<suitl[i]<<endl;
    // }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(j==3){
                grid[i][j]+=handl[i];
                handl[i]-=handl[i];
                suitl[j]-=handl[i];
                continue;
            }
            if(i==3){
                // cout<<suitl[j]<<"pp"<<endl;
                grid[i][j]+=suitl[j];
                handl[i]-=suitl[j];
                suitl[j]-=suitl[j];
                continue;
            }
            int low = 0;
            int up =100000;
            int ch=0;
            // for(int k=j+1;k<4;k++){
            //     ch+=len[i][k];
            // }
            up = min(up,handl[i]);
            // ch=0;
            // for(int k=i+1;k<4;k++){
            //     ch+=len[k][j];
            // }
            up = min(up,suitl[j]);
            // cout<<handl[i]<<" "<<suitl[j]<<endl;
            int wt=up-low+1;
            // cout<<"pp2"<<endl;
            int val = rand()%wt;
            // cout<<"pp3"<<endl;
            grid[i][j]+=val;
            handl[i]-=val;
            suitl[j]-=val;
        }
    }
    bool add = true;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(grid[i][j]<len[i][j]){
                add = false;
                break;
            }
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<grid[i][j]<<" "<<len[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<add<<endl;
    if(add){
        for(int j=0;j<4;j++){
            string temp = left[j];
            shuffle(temp.begin(),temp.end(),default_random_engine((unsigned) time(NULL)));
            // cout<<temp<<endl;
            int l=0;
            for(int i=0;i<4;i++){
                string sub = temp.substr(l,grid[i][j]);
                l+=grid[i][j];
                cards[i][j]=cards[i][j]+sub;
            }
        }
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(cards[i][j]==""){
                    cout<<"- ";
                    continue;
                }
                cout<<cards[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    return cards;
}

int main(){
    string templ="AKQJT98765432";
    vector<vector<string> > cards(4,vector<string>(4,""));
    vector<string> left(4,"");
    vector<vector<bool> > check(4,vector<bool>(13,false));
    vector<int> suitl(4,0);
    vector<int> handl(4,0);
    map<char,int> rank;
    encoding(rank);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
        	string temp;
            cin>>temp;
            cards[i][j]=temp;
            if(cards[i][j]=="-"){
                cards[i][j]="";
                continue;
            }
            handl[i]+=temp.size();
            for(int k=0;k<temp.size();k++){
                check[j][rank[temp[k]]]=true;
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<13;j++){
            if(check[i][j]==false){
                left[i]+=templ[j];
            }
        }
        suitl[i]=left[i].size();
        // cout<<left[i]<<endl;
        // cout<<suitl[i]<<" "<<handl[i]<<endl;
    }
    vector<vector<int> > len(4,vector<int>(4,0));
    // vector<vector<int> > len_up(4,vector<int>(4,0));
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
        	int x;
            cin>>x;
            len[i][j]=x;
            if(len[i][j]==-1){
                continue;
            }
            if(len[i][j]>=cards[i][j].size()){
                len[i][j]=len[i][j]-(cards[i][j].size());
            }
            else{
            	len[i][j]=0;
            }
        }
    }
    vector<vector<int> > grid=len;
    for(int i=0;i<4;i++){
        handl[i]=13-handl[i];
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            handl[i]-=grid[i][j];
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            suitl[i]-=grid[j][i];
        }
    }
    // for(int i=0;i<4;i++){
    //     for(int j=0;j<4;j++){
    //         cout<<grid[i][j]<<" "<<len[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    generate(grid,len,suitl,handl,cards,left);
}
