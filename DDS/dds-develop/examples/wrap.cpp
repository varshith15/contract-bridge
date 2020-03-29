#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

using namespace std;

#define DDS_HANDS 4
#define DDS_SUITS 4
#define DDS_FULL_LINE 80
#define DDS_HAND_OFFSET 12
#define DDS_HAND_LINES 12
#define RETURN_NO_FAULT 1

unsigned short int dbitMapRank[16] =
{
  0x0000, 0x0000, 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020,
  0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000
};

unsigned char dcardRank[16] =
{ 
  'x', 'x', '2', '3', '4', '5', '6', '7',
  '8', '9', 'T', 'J', 'Q', 'K', 'A', '-'
};

map<char,int> se;
map<char,int> ce;
map<int,char> ce1;

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
}

int IsACard(char cardChar)
{
  switch (cardChar)
  {
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    case 'T':
      return 10;
    case 'J':
      return 11;
    case 'Q':
      return 12;
    case 'K':
      return 13;
    case 'A':
      return 14;
    case 't':
      return 10;
    case 'j':
      return 11;
    case 'q':
      return 12;
    case 'k':
      return 13;
    case 'a':
      return 14;
    default :
      return 0;
  }
}

void PrintHand(char title[],
               unsigned int remainCards[DDS_HANDS][DDS_SUITS])
{
  int c, h, s, r;
  char text[DDS_HAND_LINES][DDS_FULL_LINE];

  for (int l = 0; l < DDS_HAND_LINES; l++)
  {
    memset(text[l], ' ', DDS_FULL_LINE);
    text[l][DDS_FULL_LINE - 1] = '\0';
  }

  for (h = 0; h < DDS_HANDS; h++)
  {
    int offset, line;
    if (h == 0)
    {
      offset = DDS_HAND_OFFSET;
      line = 0;
    }
    else if (h == 1)
    {
      offset = 2 * DDS_HAND_OFFSET;
      line = 4;
    }
    else if (h == 2)
    {
      offset = DDS_HAND_OFFSET;
      line = 8;
    }
    else
    {
      offset = 0;
      line = 4;
    }

    for (s = 0; s < DDS_SUITS; s++)
    {
      c = offset;
      for (r = 14; r >= 2; r--)
      {
        if ((remainCards[h][s] >> 2) & dbitMapRank[r])
          text[line + s][c++] = static_cast<char>(dcardRank[r]);
      }

      if (c == offset)
        text[line + s][c++] = '-';

      if (h != 3)
        text[line + s][c] = '\0';
    }
  }
  // printf("%s", title);
  char dashes[80];
  int l = static_cast<int>(strlen(title)) - 1;
  for (int i = 0; i < l; i++)
    dashes[i] = '-';
  dashes[l] = '\0';
  printf("%s\n", dashes);
  for (int i = 0; i < DDS_HAND_LINES; i++)
    printf("%s\n", text[i]);
  printf("\n\n");
}



int ConvertPBN(char * dealBuff,
               unsigned int remainCards[DDS_HANDS][DDS_SUITS])
{
  int bp = 0, firstl, card, hand, handRelFirst, suitInHand, h, s;

  for (h = 0; h < DDS_HANDS; h++)
    for (s = 0; s < DDS_SUITS; s++)
      remainCards[h][s] = 0;

  while (((dealBuff[bp] != 'W') && (dealBuff[bp] != 'N') &&
          (dealBuff[bp] != 'E') && (dealBuff[bp] != 'S') &&
          (dealBuff[bp] != 'w') && (dealBuff[bp] != 'n') &&
          (dealBuff[bp] != 'e') && (dealBuff[bp] != 's')) && (bp < 3))
    bp++;

  if (bp >= 3)
    return 0;

  if ((dealBuff[bp] == 'N') || (dealBuff[bp] == 'n'))
    firstl = 0;
  else if ((dealBuff[bp] == 'E') || (dealBuff[bp] == 'e'))
    firstl = 1;
  else if ((dealBuff[bp] == 'S') || (dealBuff[bp] == 's'))
    firstl = 2;
  else
    firstl = 3;

  bp++;
  bp++;

  handRelFirst = 0;
  suitInHand = 0;

  while ((bp < 80) && (dealBuff[bp] != '\0'))
  {
    card = IsACard(dealBuff[bp]);
    if (card)
    {
      switch (firstl)
      {
        case 0:
          hand = handRelFirst;
          break;
        case 1:
          if (handRelFirst == 0)
            hand = 1;
          else if (handRelFirst == 3)
            hand = 0;
          else
            hand = handRelFirst + 1;
          break;
        case 2:
          if (handRelFirst == 0)
            hand = 2;
          else if (handRelFirst == 1)
            hand = 3;
          else
            hand = handRelFirst - 2;
          break;
        default:
          if (handRelFirst == 0)
            hand = 3;
          else
            hand = handRelFirst - 1;
      }

      remainCards[hand][suitInHand] |=
        static_cast<unsigned>((dbitMapRank[card] << 2));

    }
    else if (dealBuff[bp] == '.')
      suitInHand++;
    else if (dealBuff[bp] == ' ')
    {
      handRelFirst++;
      suitInHand = 0;
    }
    bp++;
  }
  return RETURN_NO_FAULT;
}



void PrintPBNHand(char title[], char remainCardsPBN[])
{
  unsigned int remainCards[DDS_HANDS][DDS_SUITS];
  ConvertPBN(remainCardsPBN, remainCards);
  PrintHand(title, remainCards);
}



string updatePBN(string pbn,int suit,int rank,int hand){
	vector<string> h; 
    boost::split(h, pbn, boost::is_any_of(" "));

	string word=h[hand];

	vector<string> su; 
    boost::split(su, word, boost::is_any_of("."));

	string word1=su[suit];

	string temp="";
	for(int i=0;i<word1.size();i++){
		if(word1[i]!=ce1[rank]){
			temp+=word1[i];
		}
	}
	word1=temp;
	su[suit]=word1;
	word="";
	for(int i=0;i<3;i++){
		word=word+su[i]+".";
	}
	word=word+su[3];

	h[hand]=word;

	pbn="";
	for(int i=0;i<3;i++){
		pbn=pbn+h[i]+" ";
	}
	pbn=pbn+h[3];
	return pbn;
}

int main(){
	encoding();

	int won=0;
	int trump;
	int first;
	string pbn="";
	cout<<"Trump:";
	cin>>trump;
	cout<<"First:";
	cin>>first;
	cout<<"PBN:";
	string temp;
	cin>>temp;
	pbn=pbn+temp+" ";
	cin>>temp;
	pbn=pbn+temp+" ";
	cin>>temp;
	pbn=pbn+temp+" ";
	cin>>temp;
	pbn=pbn+temp;
	int i=0;
	while(i<13){
		// cout<<"wqdqwdwdqw"<<endl;
		vector<pair<int,int> > played(4,{0,0});
		for(int play=0;play<4;play++){
			string pri="N:"+pbn;
			char line[100];
			char pri1[100];
			strcpy(pri1,pri.c_str());
			strcpy(line,"TITLE");
			cout<<(first+play)%4<<" "<<"To play"<<endl;
			PrintPBNHand(line,pri1);


			ofstream mf;
			mf.open("inp.txt");
			mf<<trump<<endl;
			// cout<<trump<<endl;
			mf<<first<<endl;
			// cout<<first<<endl;
			for(int i=0;i<3;i++){
				mf<<played[i].first<<endl;
				// cout<<played[i].first<<endl;
			}
			for(int i=0;i<3;i++){
				mf<<played[i].second<<endl;
				// cout<<played[i].second<<endl;
			}
			mf<<pbn<<endl;
			// cout<<pbn<<endl;
			if(((play+first)%4)%2==0){
				char cmd[100];
				strcpy(cmd,"./SolveBoardPBN");
				system(cmd);
				ifstream mf1;
				mf1.open("tt.txt");
				int temp;
				mf1>>temp;
				char s;
				mf1>>s;
				cout<<s<<" ";
				int suit=se[s];
				mf1>>s;
				cout<<s<<endl;
				int rank=ce[s];
				played[play].first=suit;
				played[play].second=rank;
				// cout<<suit<<" "<<rank<<endl;
				mf1.close();
				// cout<<pbn<<endl;
				// cout<<(play+first)%4<<endl;
				pbn=updatePBN(pbn,suit,rank,(play+first)%4);
				// cout<<pbn<<endl;		
			}
			else{
				cout<<"Play Card";
				cin>>played[play].first;
				cin>>played[play].second;
				cout<<played[play].first<<" "<<played[play].second<<endl;
				// cout<<pbn<<endl;
				// cout<<(play+first)%4<<endl;
				pbn=updatePBN(pbn,played[play].first,played[play].second,(play+first)%4);
				// cout<<pbn<<endl;
			}
		}
		int s=played[0].first;
		int r=played[0].second;
		int fi=first;
		for(int j=1;j<4;j++){
			if(s==played[j].first && r<played[j].second){
				r=played[j].second;
				fi=(j+first)%4;
			}
		}
		if(fi%2==0){
			won++;
		}
		first=fi;
		i++;
	}
	cout<<won<<endl;
	// char cmd[100];
	// strcpy(cmd,"make SolveBoardPBN");
	// system(cmd);
	// strcpy(cmd,"./SolveBoardPBN");
	// system(cmd);
	return 0;
}