# NQueens Puzzle

**What is NQueens?** 

NQueens is a puzzle that where on an N by N chessboard there are N Queens. The Task is to disperse the queens on the board such that there is no queens in the same row or column and that no queens are next to each other on a diagonal.

# Board Value 

A Board can have a value meaning how many queens are in the same row or column or diagonal. For everytime there is a conflict with two queens on the board we add one point. 

So the Board Value is equal to

***V(Board) = # of pairs of queens in conflict***

**Our Goal**

Have ***V(Board) = 0*** meaning no Queens in conflict


# How do we solve it? 

**Hill Climbing Approach**

Get a random configuration of the Queens Board. Look at all possible successors by for each queen, moving a single Queen to all the other open spots vertically in its column and recording the boards value. Then pick the board configuration with the smallest value and repeat until a time limit is reached and hopefully a local minimum is found.

**Problems**

This personal project is to show the shortcomings of hill climbing. Hill Climbing under the above method is prone to getting stuck in a local minimum that may be a good solution but not the global minimum.

**Partial Optimization**(good for small boards but bad for big boards):
Since we're prone to getting caught in local minimums, we can throw in a random restart if its been a good amount of time since we had found a smaller board. The random restart gives us a random board configuration in the hopes of taking a different path to get to a smaller value.

**Drawback**:
This works for a small board, but when we have to use hillclimbing on a large board, we lose time due to the amount of time it takes to generate succesorrs of a board. So a random restart may be thrown when instead of being trapped in a local minimum, the computational time prevented enough depth from being covered in the search.

# Simulated Annealing 
Simulated Annealing performs well where HillClimbing falls short. Instead of choosing local neighbors simulated annealing chooses a random position and may even take a board with a higher value in the hopes of that worse board having a better configuration, using exponential probablities. As well instead of taking all successors we chose a queen and move it to a random position, a random successor.

This reduces the amount of time needed for computational complexity in looking at successors and allows for a global minimum board to be found in much less time.

# How to Run 

In terminal type `make` and hit enter. You will be greeted with an initial board configuration and 40.0 seconds later both the HillClimbing and Simulated Annealing boards are ran. Gave each local search 20.0 to run to generate the best possible solution they could find.

# Edit Board Configuration

Changing the board configuration is simple, all it requires is editing one line.
On line 8 the makefile currently reads `./$(EXEC) 12 12` which configures a 12 by 12 board. To change the board to the configuration you desire the change is with no parenthese of course

`./$(EXEC) (YOUR NUMBER HERE) (YOUR NUMBER HERE)`
