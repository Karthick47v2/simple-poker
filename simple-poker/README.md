# simple-poker

This is a simple implementation of command-line based Texas Hold 'em Poker game made for 4th Semi module 'CO2210 Programming Quest' using c++.

Game take place with all 52 cards in the card pack. Every card has a Value (2 to 10, Jack, Queen, King, and Aces) and Shape (Spade, Diamond, Heart, and Club). Dealer shuffles the cards, removes the first two cards in the pack, and distributes five cards for each player including himself. 


run, **run.bat** to compile and link cpp files

Each hand get a score based on the combination it can form as listed below with the ascending order of the scores.
__1. High card
2. One pair
3. Two pairs
4. Three of a kind
5. Straight
6. Flush
7. Full house
8. Four of a kind
9. Straight Flush__

If there is a tie situation, the one with the highest score card wins the game.

The winner receives 10 points. The losers get -1 point. The dealer does not receive or loose any points.

All the activities will be logged to file.