#include <cstddef>
#include <cassert>

// Feel free to include additional headers here!
using namespace std;
#include<queue>
#include<list>
#include "MyGrid.hpp"
#include <cstdlib>
#include<vector>
#include <tuple>

// Feel free to define auxiliary functions here!
MyGrid escape(MyGrid grid) {
    assert(grid(1,1) == Floor); // Check that the initial tile is valid.

     //Finding the exit
     Tile exit = Wall;
     int exit_row;
     int exit_col;
     for (size_t i = 0; i < grid.rows(); i++) {
         if (grid(i, 0) == Floor) {
             exit = grid(i, 0);
             exit_row = i;
             exit_col = 0;
             break;
         }
         else if (grid(i, grid.cols()) == Floor) {
             exit = grid(i, grid.cols());
             exit_row = i;
             exit_col = grid.cols();
             break;
         }
     }
     if (exit == Wall) {
         for (size_t j = 0; j < grid.cols(); j++) {
             if (grid(0, j) == Floor) {
                 exit = grid(0, j);
                 exit_row = 0;
                 exit_col = j;
                 break;
             }
             else if (grid(grid.rows(), j)  == Floor) {
                 exit = grid(grid.cols(), j );
                 exit_row = grid.rows();
                 exit_col = j;
                 break;
             }
         }
     }
     // making boolen visited array
     bool** visited = new bool*[grid.rows()];
     for (size_t i = 0; i < grid.rows(); i++) {
         visited[i] = new bool[grid.cols()];
     }
     // fillig the visited array with false
     for (size_t i = 0; i < grid.rows(); i++) {
         for (size_t j = 0; j < grid.cols(); j++) {
             visited[i][j] = false;
         }
     }




     // IMPLEMENT A STAR PATHFINDING ALGORITHM
     Tile standing = grid(1, 1);
     visited[1][1] = true;
     size_t standing_row = 1;
     size_t standing_col = 1;
     size_t h_cost = 0; // distance from current to home (first position)
     size_t e_cost= abs(exit_row - 1) + abs(exit_col - 1); // distance from current to exit
     size_t t_cost = h_cost + e_cost; // total cost

     //finding the visited tile with the lowest cost
     for (size_t i = 0; i < grid.rows(); i++) {
         for (size_t j = 0; j < grid.cols(); j++) {
             if (visited[i][j]) {
                 size_t t_cost_parse = abs(i - 1) + abs(j - 1) + abs(i - exit_row) + abs(j - exit_col);
                 if (t_cost_parse < t_cost) {
                     t_cost = t_cost_parse;
                     e_cost = abs(i - exit_row) + abs(j - exit_col);
                     h_cost = abs(i - 1) + abs(j - 1);
                     standing_row = i;
                     standing_col = j;
                     standing = grid(i, j);
                 }
             }
         }
     }

        
    
    // TODO implement some path finding algorithm find a correct path to an
    // exit tile, and then write that path to the grid.


    return grid;
}
