#!/usr/bin/python

####################################################
#
# handgenerator.py
#
# methods for generating random bridge hands
# (optionally, according to user specified criteria)
#
######################################################  

import random
from common import *

# boardnumber:(dealer,NSvul,EWvul)
DEALVULS = {1:('N',False,False), 2:('E',True,False), 3:('S',False,True), 
            4:('W',True,True), 5:('N',True, False), 6:('E', False, True), 
            7:('S',True,True), 8:('W',False,False), 9:('N',False,True), 
            10:('E',True,True), 11:('S',False,False), 12:('W',True,False),
            13:('N',True,True), 14:('E',False,False), 15:('S',True,False), 
            16:('W',False,True)}

# number of times to attempt to find a hand meeting specified criteria
NUMTOTRY = 100000

def randomdeal():
    """
    generates an arbitrary deal, returning
    an Auction with random boardnum, dealer, vul, hands
    """
    # copy-paste code seems necessary here since we need multiple
    # instances of the object "range('2'..'A')"
    scards = ['2','3','4','5','6','7','8','9','T','J','Q','K','A']
    hcards = scards[:]
    dcards = scards[:]
    ccards = scards[:]
    deck = {'S':scards, 'H':hcards, 'D':dcards, 'C':ccards}
    # fun with list comprehensions and dict() constructor
    newdeal = dict([(player,None) for player in PLAYERS])
    # generate a random hand for each player
    for player in PLAYERS:
        newhand = dict([(suit,[]) for suit in SUITS])
        #print "\n Player %s:" % player
        for i in range(13):
            dealt = False
            while not dealt:
                suit = random.choice(SUITS)
                thesuit = deck[suit]
                try:
                    thecard = random.choice(thesuit)
                    dealt = True
                except IndexError:
                    continue
                thesuit.remove(thecard)
        #        print "card %d is %s of %s" % (i + 1, thecard, suit)
                newhand[suit].append(thecard)
        for suit in SUITS:
            newsuit = Suit(list(newhand[suit]))
            newhand[suit] = newsuit
        hand = Hand(newhand['S'], newhand['H'], newhand['D'], newhand['C'])
        newdeal[player] = hand
    boardnum = random.randint(1,16)
    dealer = DEALVULS[boardnum][0]
    NSvul = DEALVULS[boardnum][1]
    EWvul = DEALVULS[boardnum][2]
    return Auction(dealer, NSvul, EWvul, boardnum, newdeal['N'],
                   newdeal['S'], newdeal['E'], newdeal['W'])


class Criteria:
    """
    attributes:
    1)suits is a dict indexed by PLAYERS
    each value is a dict indexed by SUITS
    each value is a dict of the form 
    {"strength":{"min":mins,"max":maxs}, "shape":{"min":minl, "max":maxl}}

    2)ind_strengths is a dict indexed by PLAYERS
    each value is a dict {"min":minhcp, "max":maxhcp}

    3)comb_strengths is a dict
    {'NS':{"min":mincombhcp, "max":maxcombhcp},
     'EW':{"min":mincombhcp, "max":maxcombhcp}}

    """
    def __init__(self, suits, ind_strengths, comb_strengths):
        self.suits = suits
        self.ind_strengths = ind_strengths
        self.comb_strengths = comb_strengths

def criteriadeal(criteria, dealer, vul):
    """
    check whether Criteria criteria are coherent.
    if not, return False
    otherwise, return a random deal satisfying those criteria
    (WARNING: works very stupidly for now)
    """
    for i in range(NUMTOTRY):
        #print "Testing hand", i
        deal = randomdeal()
        flag = True
        for player in PLAYERS:
            for suit in SUITS:
                if not (criteria.suits[player][suit]["shape"]["min"] <=
                        deal.hands[player].shape()[suit] <=
                        criteria.suits[player][suit]["shape"]["max"]):
                    #print "failed shape test for", player, suit
                    #print "deal:"
                    #print deal.hands[player].shape()
                    #print criteria.suits[player]
                    flag = False
                    continue
                if not (criteria.suits[player][suit]["strength"]["min"] <=
                        deal.hands[player].shape()[suit] <=
                        criteria.suits[player][suit]["strength"]["max"]):
                    #print "failed strength test for", player, suit
                    flag = False
                    continue
            if not (criteria.ind_strengths[player]["min"] <=
                    deal.hands[player].hcp() <=
                    criteria.ind_strengths[player]["max"]):
                #print "failed strength test for", player
                flag = False
        if not flag:
            continue
        if not (criteria.comb_strengths['NS']["min"] <=
                deal.hands['N'].hcp() + deal.hands['S'].hcp() <=
                criteria.comb_strengths['NS']["max"]):
            #print "failed strength test for NS"
            flag = False
        if not flag:
            continue
        if not (criteria.comb_strengths['EW']["min"] <=
                deal.hands['E'].hcp() + deal.hands['W'].hcp() <=
                criteria.comb_strengths['EW']["max"]):
            #print "failed strength test for EW"
            flag = False
        if flag:
            print "Success after", i, "tries"
            if not dealer == 'random':
                deal.dealer = dealer
                deal.boardnum = None
            if not vul == 'random':
                if vul == 'none':
                    for suit in SUITS:
                        deal.vuls[suit] = False
                elif vul == 'all':
                    for suit in SUITS:
                        deal.vuls[suit] = True
                else:
                    for suit in SUITS:
                        if suit in vul:
                            deal.vuls[suit] = True
                        else:
                            deal.vuls[suit] = False
                deal.boardnum = None
            return deal
    return False
 
    
            
        
        
