from redeal import * # this is "reasonably" safe

predeal = {"S": H("- 96532 A864 T962")} # H is a hand constructor.

def accept(deal):
   if len(deal.north.spades) >= 5 and deal.north.hcp >= 12:
      return True
