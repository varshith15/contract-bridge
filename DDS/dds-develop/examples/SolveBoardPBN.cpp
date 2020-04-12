#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dll.h"
#include "hands.h"

using namespace std;

int main()
{
  dealPBN dlPBN;
  futureTricks fut;

  int target;
  int solutions;
  int mode;
  int threadIndex = 0;
  int res;
  char line[80];

#if defined(__linux) || defined(__APPLE__)
  SetMaxThreads(0);
#endif
  ifstream mf;
  mf.open("inp.txt");

  mf>>dlPBN.trump;
  mf>>dlPBN.first;
  mf>>dlPBN.currentTrickSuit[0];
  mf>>dlPBN.currentTrickSuit[1];
  mf>>dlPBN.currentTrickSuit[2];

  mf>>dlPBN.currentTrickRank[0];
  mf>>dlPBN.currentTrickRank[1];
  mf>>dlPBN.currentTrickRank[2];

  string pbn="";
  string temp;
  mf>>temp;
  pbn=pbn+temp+" ";
  mf>>temp;
  pbn=pbn+temp+" ";
  mf>>temp;
  pbn=pbn+temp+" ";
  mf>>temp;
  pbn=pbn+temp;
  pbn="N:"+pbn;
  // cout<<pbn<<endl;
  strcpy(dlPBN.remainCards,pbn.c_str());
  target=-1;
  solutions=3;
  mode=1;
  res = SolveBoardPBN(dlPBN,target,solutions,mode,&fut,0);

  if (res != RETURN_NO_FAULT){
      ErrorMessage(res, line);
      printf("DDS error: %s\n", line);
  }
  //printf("%s\n",dlPBN.remainCards);
  // PrintPBNHand(dlPBN.remainCards);
  //sprintf(line, "solutions == 3\n");
  PrintFut(line, &fut);

  // for (int handno = 0; handno < 1; handno++)
  // {
  //   dlPBN.trump = 4;
  //   dlPBN.first = 2;

  //   dlPBN.currentTrickSuit[0] = 0;
  //   dlPBN.currentTrickSuit[1] = 0;
  //   dlPBN.currentTrickSuit[2] = 0;

  //   dlPBN.currentTrickRank[0] = 0;
  //   dlPBN.currentTrickRank[1] = 0;
  //   dlPBN.currentTrickRank[2] = 0;

  //   strcpy(dlPBN.remainCards, PBN[handno]);
  //   printf("%s\n",PBN[handno]);
  //   target = -1;
  //   solutions = 3;
  //   mode = 0;
  //   res = SolveBoardPBN(dlPBN, target, solutions, mode, &fut3, 0);

    // if (res != RETURN_NO_FAULT)
    // {
    //   ErrorMessage(res, line);
    //   printf("DDS error: %s\n", line);
    // }

  //   match3 = CompareFut(&fut3, handno, solutions);

  //   solutions = 2;
  //   res = SolveBoardPBN(dlPBN, target, solutions, mode, &fut2, 0);
  //   if (res != RETURN_NO_FAULT)
  //   {
  //     ErrorMessage(res, line);
  //     printf("DDS error: %s\n", line);
  //   }

  //   match2 = CompareFut(&fut2, handno, solutions);

  //   sprintf(line,
  //           "SolveBoardPBN, hand %d: solutions 3 %s, solutions 2 %s\n",
  //           handno + 1,
  //           (match3 ? "OK" : "ERROR"),
  //           (match2 ? "OK" : "ERROR"));

  //   PrintPBNHand(line, dlPBN.remainCards);

    // sprintf(line, "solutions == 3\n");
    // PrintFut(line, &fut3);
  //   sprintf(line, "solutions == 2\n");
  //   PrintFut(line, &fut2);
  // }
}
