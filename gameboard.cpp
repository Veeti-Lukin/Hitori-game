/*
* Program author
* Name: Veeti Lukin
* Student number: 50797635
* UserID: gtvelu
* E-Mail: veeti.lukin@tuni.fi
*
* Notes about the program and it's implementation:
*   This is only class implemention.
*   Check header file for more infomation.
*/

#include "gameboard.hh"
#include <random>
#include <algorithm>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::getline;

Gameboard::Gameboard(){
    // initializes random values to squares in <squares_>
    parseVectorToMatrix(generateRandomValues());
}

Gameboard::Gameboard(const vector<unsigned int>& givenValues){
    // initializes given values to squares in <squares_>
    parseVectorToMatrix(givenValues);
}

void Gameboard::print(){
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int row = 0; row < BOARD_SIDE; ++row){
        cout << "| " << row + 1 << " | ";
        for(unsigned int column = 0; column < BOARD_SIDE; ++column){
            if(squares_.at(row).at(column) == 0){
                cout << EMPTY << " ";
            }
            else{
                cout << squares_.at(row).at(column) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

bool Gameboard::removeSquare(unsigned int column,unsigned int row){
    // given coordinates should be 1 more than actual indexes int <squares_> matrix
    // this is because <print> method starts printin coordinates from 1
    row -= 1;
    column -= 1;
    // no need to check if coordinate is <0
    // because unsigned int will flip to 4 byte maxium if it goes under 0
    if (!(row < BOARD_SIDE) || !(column < BOARD_SIDE)){
        cout << "Out of board" << endl;
        return false;
    }
    if (squares_.at(row).at(column) == 0){
        cout << "Already removed" << endl;
        return false;
    }
    squares_.at(row).at(column) = 0;
    return true;
}

bool Gameboard::isWon(){
    // looping trough matrix value by value
    for(unsigned int row = 0; row < BOARD_SIDE; ++row){
        for(unsigned int column = 0; column < BOARD_SIDE; ++column){
            unsigned int value = squares_.at(row).at(column);
            // there is no need to count values that are 0
            if (value == 0) {
                continue;
            }
            // count needs to be set  as -1,
            // because value will be atleast once on row and colu
            int valueCount = -1;
            // looping trough current row and current column
            for(unsigned int iterator = 0; iterator < BOARD_SIDE; ++iterator) {
                // check row
                if (squares_.at(row).at(iterator) == value) {
                    valueCount += 1;
                }
                // check column
                if (squares_.at(iterator).at(column) == value) {
                    valueCount += 1;
                }
            }

            // reuturn false if multiple values on same row or column
            if (valueCount > 1){
                return false;
            }
        }
    }
    // no dublicate values on rows or coulmn found
    return true;
}

bool Gameboard::isLost(){
    // loop trough <squares_> matrix value by value
    // and calculating how many nonzero and zero neighbours it has.
    // If value != 0 it should have atleas one nonzero neigbour or it is isolated
    // if value == 0 it should not have any zero neighbours
    for (unsigned int row = 0; row < BOARD_SIDE; ++row){
        for ( unsigned int column = 0; column < BOARD_SIDE; ++column){
            int neighbourNonZeroCount = 0;
            int neighbourZeroCount = 0;
            if (row != 0){
                if (squares_.at(row-1).at(column) != 0){
                    neighbourNonZeroCount += 1;
                }
                else {
                    neighbourZeroCount += 1;
                }
            }
            if (column != 0){
                if (squares_.at(row).at(column-1) != 0){
                    neighbourNonZeroCount += 1;
                }
                else {
                    neighbourZeroCount += 1;
                }
            }
            if (row != BOARD_SIDE -1){
                if (squares_.at(row +1).at(column) != 0){
                    neighbourNonZeroCount += 1;
                }
                else {
                    neighbourZeroCount += 1;
                }
            }
            if (column != BOARD_SIDE -1){
                if (squares_.at(row).at(column+1) != 0){
                    neighbourNonZeroCount += 1;
                }
                else {
                    neighbourZeroCount += 1;
                }
            }
            if (neighbourNonZeroCount == 0){
                return true;
            }
            if (squares_.at(row).at(column) == 0 && neighbourZeroCount > 0){
                return true;
            }
        }
    }
    return false;
}

void Gameboard::parseVectorToMatrix(const vector<unsigned int> values){
    //check header file for refrence picture of the <squares_> matrix
    //loops over the values in *values* and forms subvectors of size BOARD_SIZE
    vector<unsigned int> subVector = {};

    for (vector<unsigned int>::size_type index = 0; index < values.size(); index++) {
        subVector.push_back(values.at(index));
        // checking if should go to next "row"
        if ((index+1) % BOARD_SIDE == 0) {
            squares_.push_back(subVector);
            subVector.clear();
        }
    }
}

vector<unsigned int> Gameboard::generateRandomValues() const{
    // getting seed value from user
    cout << "Enter a seed value: ";
    string seedString = "";
    getline(cin, seedString);
    int seed = stoi(seedString);

    // initializing random number generator
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<unsigned int> distr(MIN_INT_VALUE, MAX_INT_VALUE);

    // generating integer values for whole gameboard area
    unsigned int area = BOARD_SIDE * BOARD_SIDE;
    vector<unsigned int> generatedValues = {};
    for (unsigned int i = 0; i < area; i++) {
        generatedValues.push_back(distr(generator));
    }
    return generatedValues;
}
