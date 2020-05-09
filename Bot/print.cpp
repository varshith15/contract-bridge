#include <bits/stdc++.h>
#include "print.h"

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