#include <iostream>

using namespace std;
const int a = 9;
//array that holds the sudoku values
int sudoku[a][a] = 
{
    {3, 0, 0, 0, 8, 0, 0, 0, 0}, 
    {0, 0, 0, 1, 3, 0, 6, 0, 0}, 
    {0, 0, 5, 9, 4, 0, 0, 3, 8}, 
    {0, 0, 0, 0, 0, 0, 7, 6, 3}, 
    {7, 0, 0, 0, 0, 0, 0, 0, 9}, 
    {4, 5, 6, 0, 0, 0, 0, 0, 0}, 
    {1, 8, 0, 0, 6, 4, 2, 0, 0}, 
    {0, 0, 9, 0, 5, 3, 0, 0, 0}, 
    {0, 0, 0, 0, 9, 0, 0, 0, 7}, 
};

/**
 * Checks if number exists in the column
 * @param column the column of the sudoku
 * @param number the number being searched
 * @return returns true if number exists in column
 *         returns false if number does not exist in column
 */ 
bool columnChecker(int column, int number)
{
    for(int row = 0; row != a; row++)
    {
        if(sudoku[row][column] == number)
        {
            return true;
        }
    }
    return false;
}

/**
 * Checks if number exists in the row
 * @param row the row of the sudoku
 * @param number the number being searched
 * @return returns true if number exists in row
 *         returns false if number does not exist in row
 */
bool rowChecker(int row, int number)
{
    for(int column = 0; column != a; column++)    
    {
        if(sudoku[row][column] == number)
        {
            return true;
        }
    }
    return false; 
}

/**
 * Checks if number exists in the region
 * @param regionRow the row of the region
 * @param regionColumn the column of the region
 * @param number the number being searched
 * @return returns true if number exists in the region
 *         returns false if number does not exist in the region
 */
bool regionChecker(int regionRow, int regionColumn, int number)
{
    for(int row = 0; row < 3; row++)
    {
        for(int column = 0; column < 3; column++)
        {
            if(sudoku[row+regionRow][column+regionColumn] == number)
            {
                return true;
            }
        }
    }
    return false; 
}

/**
 * Checks if the [row][column] is empty
 * @param &row the row 
 * @param &column the column 
 * @return returns true if the [row][column] is equal to 0
 *         returns false if the [row][column] is not equal to 0
 */
bool emptyChecker(int &row, int &column)
{
    for(row = 0; row < a; row++)
    {
        for(column = 0; column < a; column++)
        {
            if(sudoku[row][column] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * Checks if the [row][column] is available
 * @param row the row 
 * @param column the column 
 * @param number the number being searched
 * @return returns true if the row, column, and region are available
 *         returns true if the row, column, and region are not available
 */
bool available(int row, int column, int number)
{
    return !rowChecker(row, number) && !columnChecker(column, number) && 
           !regionChecker(row-row%3, column-column%3, number);
}

/**
 * Uses the above functions to solve the sudoku puzzle if possible.
 * @return returns true if the [row][column] is empty or if the slot is available.
 *         returns false if the [row][column] is not empty or if the slot is not available.
 */
bool solve()
{
    int row, column;
    if(!emptyChecker(row, column))
    {
        return true;
    }
    for(int i = 1; i != 10; i++)
    {
        //checks if the slot is available
        if(available(row, column, i))
        {
            //sets the [row][column] to the number
            sudoku[row][column] = i;
            //recursively checks if it can be solved.
            if(solve())
            {
                return true;
            }
            //otherwise sets it to 0
            sudoku[row][column] = 0;
        }
    }
    return false;
}

/**
 * Creates the sudoku grid 
 */
void createSudoku()
{
    for(int row = 0; row < a; row++)
    {
        if(row == 0)
        {
            cout << "-------------\n";
        }
        for(int column = 0; column < a; column++)
        {
           
            if(column == 0)
            {
                cout << "|";
            }
            if(column == 3 || column == 6)
            {
                cout << "|";
            }
            cout << sudoku[row][column];
            if(column == 8)
            {
                cout << "|";
            }
        }
        if(row == 2 || row == 5)
        {
            cout << "\n" << "-------------"; 
        }
        cout << "\n";
        if(row == 8)
        {
            cout << "-------------";
        }
    }
}

int main()
{
    
    if(solve())
    {
        createSudoku();
    }
    else
    {
        cout << "Cannot solve given Sudoku puzzle";
    }

    return 0;
}