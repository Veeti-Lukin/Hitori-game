# Hitori-game
Object oriented Hitori game with text based UI

## About the game
https://en.wikipedia.org/wiki/Hitori

## About the program
This program implements a Hitori game with the game board of
size 5 x 5. Each square in the game board has a number from 1-5.
At first, each horizontal and vertical row can have several identical
numbers, but the purpose is to remove numbers such that each horizontal
and vertical row has no duplicate numbers. However, it is not possible
to remove numbers in adjacent squares, and none of the remaining
numbers (squares) can be isolated from the other ones, i.e. it is not
possible to remove all numbers around it (from strictly above, below,
left, right). 

At first, the user is asked, if the game board will be filled with
randomly drawn numbers 1-5, or with user-given 25 numbers. In the first
option, a seed value for the random number generator will be asked next.
In the latter option, the user is asked to input 25 numbers.
On each round, the user is asked for coordinates, i.e. two numbers.
The player wins if each horizantal and vertical row has at most one
instance of each number 1-5. The player loses if they remove a number,
the adjacent number of which has already been removed or if a number
becomes isolated.
The program checks the user-given coordinates. They must be inside the
game board, and the square indicated by them must have a number, i.e.
a number cannot be removed again.
When the game ends, the program tells if the player won or lost.

## Notes about the program and it's implementation:
Gameboard is impelementd in class that contains matrix of gameboards values
Main will handle all (or atleast almost all) interaction with user
All changes to gameboards state will be done from Gamboard instances public interface
