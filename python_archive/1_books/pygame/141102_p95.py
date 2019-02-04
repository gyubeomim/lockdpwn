'''
Created on Nov 2, 2014

@author: tigerk0430
'''


import random
import time
import sys


def displayIntro():
    print("you are in a land full of dragons. in fornt of you,")
    print("you see two caves. In one cave, the dragon is friendly")
    print("and will share his treasure with you. The oter dragon")
    print("is greedy and hungry, and will eat you on sight")
    print()
    
  
def chooseCave():
    cave = ''
    cnt = 0
    while cave != '1' and cave != '2':
        print("Which cave will you go into? (1 or 2)")
        cave = input()
        cnt += 1   
        
        if cnt==5:
            print("hmm.. are you ok?")
            continue 
        if cnt==10:
            print("oh my god.. you are freaky nerd")
            sys.exit()
    return cave


def checkCave(chosenCave):
    print("You approach the cave...")
    time.sleep(2)
    print('It is dark and spooky...')
    time.sleep(2)
    print("A large dragon jumps out in front of you! He opens his jaws and...")
    print()
    time.sleep(2)
    
    
    friendlyCave = random.randint(1,2)
    
    if chosenCave == str(friendlyCave):
        print("Gives you his treasure!")
    else:
        print('Gobbles you down in one bite!')
    
    
    
playAgain = 'yes'
while playAgain == 'yes' or playAgain == 'y':
    
    displayIntro()
    
    caveNumber = chooseCave()
    
    checkCave(caveNumber)
    
    print('Do you want to play again? (yes or no)')
    
    playAgain = input()
    
    
    
    
    
    
    
    
    
    
    