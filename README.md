# othello-c
Implementation of the game othello or reversi in c.
Options:
-t: plays through the game and prints the state of the specified games. Doesn't output to file
Description:
Prints the result of the game in arg 1 to a file with the name specified by arg 2
## Game format
<Player1-name>,<B/N> // the players and their color
<Player2-name>,<B/N>
<B/N>                // the color that moves first
<move>               // moves in the form of coordinates such as A1, B3 C4
<move>               // a newline here means a pass.
<move>
