/* Hitori
 *
 * Desc:
 *   This program implements a Hitori game with the game board of
 * size 5 x 5. Each square in the game board has a number from 1-5.
 * At first, each horizontal and vertical row can have several identical
 * numbers, but the purpose is to remove numbers such that each horizontal
 * and vertical row has no duplicate numbers. However, it is not possible
 * to remove numbers in adjacent squares, and none of the remaining
 * numbers (squares) can be isolated from the other ones, i.e. it is not
 * possible to remove all numbers around it (from strictly above, below,
 * left, right).
 *   At first, the user is asked, if the game board will be filled with
 * randomly drawn numbers 1-5, or with user-given 25 numbers. In the first
 * option, a seed value for the random number generator will be asked next.
 * In the latter option, the user is asked to input 25 numbers.
 *   On each round, the user is asked for coordinates, i.e. two numbers.
 * The player wins if each horizantal and vertical row has at most one
 * instance of each number 1-5. The player loses if they remove a number,
 * the adjacent number of which has already been removed or if a number
 * becomes isolated.
 *   The program checks the user-given coordinates. They must be inside the
 * game board, and the square indicated by them must have a number, i.e.
 * a number cannot be removed again.
 *   When the game ends, the program tells if the player won or lost.
 *
 * Program author
 * Name: Veeti Lukin
 * Student number: 50797635
 * UserID: gtvelu
 * E-Mail: veeti.lukin@tuni.fi
 *
 * Notes about the program and it's implementation:
 *  Gameboard is impelementd in class that contains matrix of gameboards values
 *  Main will handle all (or atleast almost all) interaction with user
 *  All changes to gameboards state will be done from Gamboard instances public interface
 * */
#include "gameboard.hh"
#include <iostream>
#include <vector>
#include <string>

using std::endl;
using std::cout;
using std::vector;
using std::string;
using std::cin;
using std::getline;

const string RANDOMM_CHAR = "R";
const string INPUT_CHAR = "I";
const string QUIT_CHAR = "Q";

// converts given string to uppercase and returns it
string stringToUpper(string str){
    for (string::size_type i = 0; i < str.size(); i++) {
        str.at(i) = toupper(str.at(i));
    }
    return str;
}

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i){
        if(not isdigit(str.at(i))){
            is_numeric = false;
            break;
        }
    }
    if(is_numeric){
        return stoi(str);
    }
    else{
        return 0;
    }
}

// splits given string of ints *str* from every char *splitter*
// converts every string form int to int with <stoi_with_check> function
// returns vector of those ints
vector<unsigned int> splitStringToInts(string& str, char splitter, bool skip_empty=true) {
    vector<unsigned int> ints;
    string substr = "";
    size_t start = 0;
    size_t end = str.find(splitter);
    while (end != string::npos) {
        substr = str.substr(start, end - start);
        start = end +1;
        end = str.find(splitter, start);

        if (skip_empty && substr ==  "")
            continue;
        int substrAsInt = stoi_with_check(substr);
        ints.push_back(substrAsInt);
    }
    int substrAsInt = stoi_with_check(str.substr(start, end - start));
    ints.push_back(substrAsInt);
    return ints;
}


// Creates instance of Gameboard class
// Asks user input if user wants to fill squares or let them be randomized
Gameboard createGameboard() {
    while (true) {
        cout << "Select start ("<< RANDOMM_CHAR << " for random, "
             << INPUT_CHAR << " for input): ";
        string fillMode = "";
        getline(cin, fillMode);


        if (stringToUpper(fillMode) == RANDOMM_CHAR){
            return Gameboard();
        }
        if (stringToUpper(fillMode) == INPUT_CHAR){
            cout << "Input: ";
            string inputtedValues = "";
            getline(cin, inputtedValues);
            vector<unsigned int> inputtedValuesAsInts = splitStringToInts(inputtedValues, ' ');
            return Gameboard(inputtedValuesAsInts);
        }
    }
}


int main(){
    Gameboard gameboard = createGameboard();
    gameboard.print();

    while (true) {
        cout << "Enter removable element (x, y): ";
        string answer = "";
        getline(cin, answer);

        if (stringToUpper(answer) == QUIT_CHAR){
            cout << "Quitting" << endl;
            return EXIT_SUCCESS;
        }
        vector<unsigned int> coordinates = splitStringToInts(answer, ' ');

        if (coordinates.size() != 2){
            cout << "Enter X and Y coordinates" << endl;
            continue;
        }
        int x = coordinates.at(0);
        int y = coordinates.at(1);

        if (!(gameboard.removeSquare(x, y))){
            continue;
        }
        gameboard.print();

        if(gameboard.isWon()){
            cout << "You won" << endl;;
            return EXIT_SUCCESS;
        }
        if (gameboard.isLost()){
            cout << "You lost" << endl;
            return EXIT_SUCCESS;

        }
    }
}
