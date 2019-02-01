//
//
//  Marie-Claire Salha
//  mjs170530
//
//  This program will read in at least one sudoku puzzle, and then will tell the user if it's valid, invalid, or solved by checking the
//  horizontal lines, veritcal lines, and all the 3x3 grids.
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// prototypes
bool checkRow (char* puzzle, int boardNum);
bool checkColumn (char* puzzle, int boardNum);
bool checkSquare (char* puzzle, int boardNum);
bool checkSolved (char* puzzle);

int main()
{
    fstream file, outputFile;
    int boardNum;
    string line;
    bool endOfFile = false;
    char* puzzle = new char[81]; // creates a dynamic array
    
    // opens the input file
    file.open("puzzles.txt", ios::in);
    
    // if the file opens correctly
    if(file)
    {
        // while it's not the end of the file, then it will go through this while loop
        while(!file.eof())
        {
            // this will read in the number of the puzzle (so: this is puzzle #1, or puzzle #345)
            file >> boardNum;
            
            // ignores the endline
            file.ignore();
            
            // this entire for loop and the inner nested for loop will go through each number in the sudoku
            // puzzle and fill in each number for each element in the array
            for(int i = 0; i < 9; i++)
            {
                for(int h = 0; h < 9; h++)
                {
                    // this will make the value of that element equal to what the certain character is
                    *puzzle = file.get();
                    // increments puzzle so it will go to the next element
                    puzzle++;
                }
                
                // gets the rest of the line so that the array doesn't read in any spaces
                getline(file, line);
            }
            // this moves the puzzle pointer back to its original spot in the beginning of the array
            puzzle -= 81;
            
            
            // if the rows are all valid, then it will call the other functions
            if(checkRow(puzzle, boardNum))
            {
                // if the columns are all valid, then it will call the other functions
                if(checkColumn (puzzle, boardNum))
                {
                    // if all of the squares are valid, then it will check to see if the puzzle is solved
                    if( checkSquare (puzzle, boardNum))
                       {
                           // this will open my output file
                           outputFile.open("solutions.txt", ios::out | ios::binary | ios::app);
                           
                           // if the function returns true, then it is solved
                           if(checkSolved (puzzle))
                           {
                               // outputs to the file that this specific puzzle is solved
                               outputFile << setw(8) << left << boardNum << "solved" << endl;
                           }
                           // if the function returns false, then we just say that it is valid
                           else
                           {
                               // outputs to the file that this specific puzzle is just valid
                               outputFile << setw(8) << left << boardNum << "valid" << endl;
                           }
                           
                           // closes the output file
                           outputFile.close();
                           
                       }
                }
            }
            
            // checks if it's the end of the input file, and also checks for endlines
            getline(file, line);
            endOfFile = file.eof();
        }
        
        // closes the input file that we were reading from
        file.close();
    }
    // if the file cannot open, then it gives the user an error message
    else
    {
        // tells the user on the console screen that the file could not be found
        cout << "The file does not exist";
    }
    
    delete []puzzle;
    
    return 0;
}




// This function goes through each row and checks if they're valid or not
bool checkRow (char* puzzle, int boardNum)
{
    bool valid = true;          // tells us if the row is valid or not
    char* pointer = puzzle;     // this sets a second pointer that will move throughout the dynamic array and will compare those values to the original pointer
    char* placeHolder = puzzle; // acts as a place holder to put pack the original pointer at the beginning of the array at the end of the program
    fstream outputFile;
    

    // opens up the output file
    outputFile.open("solutions.txt", ios::out | ios::binary | ios::app);
    
    // if the output file opens correctly, then the function will continue
    if(outputFile)
    {
        // this for loop will go through all of the rows in the program
        for(int row = 0; row < 9; row++)
        {
            // this for loop will go through the columns in the program
            for(int col = 0; col < 9; col++)
            {
                // this for loop will go through all of the individual squares in the row
                for(int inc = col; inc < 9; inc++)
                {
                    // if the addresses are the same, then it will increment the second pointer anyway and will start the loop over
                    if(puzzle == pointer)
                    {
                        pointer = pointer + 1;
                        continue;
                    }
                    
                    // if the values are the same, and it's not a space, then it will say that it's an invalid value, and will return that bool back to main()
                    if(*puzzle == *pointer && *pointer != ' ')
                    {
                        outputFile << setw(8) << left << boardNum << "invalid\t\t" << "multiple " << *puzzle << "'s in row " << (row + 1) << endl;
                        valid = false;
                        return valid;
                    }
                    
                    // increments pointer so that it goes across each row
                    pointer = pointer + 1;
                }
                
                // increments puzzle so everything can be compared to that
                puzzle = puzzle + 1;
                
                // sets pointer to where puzzle is so it can start the comparisons there
                pointer = puzzle;
            }
            
            // not necessary, but kept just in case
                // puzzle += 1;
                // pointer = puzzle;
            
        }
    
    }
    
    
    // returns the original pointer the the beginning of the array
    puzzle = placeHolder;
    
    // closes the output file
    outputFile.close();
    
    // returns either true or false
    return valid;

}


// The function will check through the columns in the puzzle
bool checkColumn (char* puzzle, int boardNum)
{
    bool valid = true;          // this sets the valid bool to true saying that it's valid at first
    char* pointer = puzzle;     // makes a second pointer that will move throughout the array
    char* placeHolder = puzzle; // holds the original spot of the array
    fstream outputFile;
    
    // opens the output file
    outputFile.open("solutions.txt", ios::out | ios::binary | ios::app);
    
    // if the output file opens correctly
    if(outputFile)
    {
        // loops through where the original pointer is going to move to after it goes through one column
        for(int i = 0; i < 9; i++)
        {
            // goes through each column
            for(int col = 0; col < 9; col++)
            {
                
                // goes through each row
                for(int row = 0; row < 8; row++)
                {
                    // move secondary pointer through each row
                    pointer += 9;
                    
                    // if they have the same address, then it will start the loop over
                    if(puzzle == pointer)
                    {
                        continue;
                    }
                    
                    // if the values are the same, and there isn't a white space, then it will say that it's invalid
                    if(*puzzle == *pointer && *pointer != ' ')
                    {
                        // outputs that it's invalid and returns that bool to the main function
                        outputFile << setw(8) << left << boardNum << "invalid\t\t" << "multiple " << *puzzle << "'s in column " << (i + 1) << endl;
                        valid = false;
                        return valid;
                    }
                    
                }
                
                // increments puzzle to the next part in the column to be compared with
                puzzle += 9;
                
                // moves pointer back to the beginning of the next column
                pointer -= 72;
            }
            
            // moves puzzle to the next column
            puzzle -= 71;
            
            // increments pointer by 1 so that it is not in the same place as puzzle
            pointer++;
        }
    }
    
    // returns puzzle back to its original place
    puzzle = placeHolder;
    
    // closes the file
    outputFile.close();

    // returns the bool
    return valid;
}




// This function checks through all of the squares
bool checkSquare (char* puzzle, int boardNum)
{
    char* placeHolder = puzzle;
    fstream outputFile;
    bool found[9] = {false, false, false, false, false, false, false, false, false};
    int val = 0, boxAddition = 0;
    string box = "";
    
    // opens the output file
    outputFile.open("solutions.txt", ios::out | ios::binary | ios::app);
    //

    // if the file opened
    if(outputFile)
    {
        
        // this goes through the outer row
        for(int outRow = 0; outRow < 3; outRow++)
        {
            // this goes through the outer column
            for(int outCol = 0; outCol < 3; outCol++)
            {
                //
                
                // this goes through the inner row
                for(int inRow = 0; inRow < 3; inRow++)
                {
                    // this goes through the inner column
                    for(int inCol = 0; inCol < 3; inCol++)
                    {
                        // if the value of puzzle is not a space then
                        if(*puzzle != ' ')
                        {
                            // set the temp value to the number inside of puzzle
                            val = *puzzle - '0';
                            val -= 1;
                            
                            // if this is false, then send out a message into the output file saying that this is false
                            if(found[val])
                            {
                                // the following if statements will check what box the error is technically in
                                if((outRow + outCol) == 0 || (outRow + outCol) == 3 || (outRow + outCol) == 6)
                                {
                                    // this is the prefix
                                    box = box + "upper";
                                }
                                else if((outRow + outCol) == 1 || (outRow + outCol) == 4 || (outRow + outCol) == 7)
                                {
                                    // prefix unless it's equal to 4, then it just says "center"
                                    box = box + "center";
                                }
                                else if((outRow + outCol) == 2 || (outRow + outCol) == 5 || (outRow + outCol) == 8)
                                {
                                    // prefix
                                    box = box + "bottom";
                                }
                                
                                // this add the suffix if it's not equal to 4, thus only saying "center" and wouldn't go into this if statement
                                if((outRow + outCol) != 4)
                                {
                                    boxAddition = (outRow + outCol)/3;
                                    if(boxAddition == 0)
                                    {
                                        // suffix
                                        box = box + " left";
                                    }
                                    else if(boxAddition == 1)
                                    {
                                        // suffix
                                        box = box + " middle";
                                    }
                                    else if(boxAddition == 2)
                                    {
                                        // suffix
                                        box = box + " right";
                                    }
                                    
                                }
                                
                                outputFile << setw(8) << left << boardNum << "invalid\t\t" << "multiple " << *puzzle << "'s in " << box << " square " << endl;
                                return false;
                            }
                            // other wise, say that it is true
                            else
                            {
                                found[val] = true;
                            }
                            
                        }
                        
                        // increments puzzle
                        puzzle++;
                    }
                    
                    // sets puzzle back to the top right of the next square
                    puzzle -= 3;
                    puzzle += 9;
                }
                
                // this will go through and set all of the bools in found back to false
                for(int i = 0; i < 9; i++)
                {
                    found[i] = false;
                    
                }
                
                // sets it to the top
                puzzle -= (9 * 3);
                puzzle += 3;
            }
            
            // goes back to the top of the next square
            puzzle += (9 * 3);
            puzzle -= 9;
        }
        
    }
    
    // closes the output file
    outputFile.close();
    
    // puts back the original address
    puzzle = placeHolder;
    
    // returns true to main()
    return true;
    
}


    
// The only thing that needs to be passed into here is the dynamic array
// goes through the dynamic array and checks for spaces
bool checkSolved(char* puzzle)
{
    char* placeHolder = puzzle;
    
    // makes a boolean called solved to check if our array is solved or just valid
    bool solved = true;
    
        // loops through the entire array
        for(int i = 0; i < 81; i++)
        {
            // the first time it finds a space, it sets solved to false and it returns that value,
            // thus leaving the function
            if(*puzzle == ' ')
            {
                // sets solved to false
                solved = false;
                // leaves function and returns that the puzzle is not solved
                return solved;
            }
        
            puzzle++;
        }
    
    //was removed
        // keeps solved set to true
        //solved = true;
    
    // returns puzzle to original place
    puzzle = placeHolder;
    
    // returns the value of solved
    return solved;
    
}





















