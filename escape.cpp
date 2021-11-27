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
int abs(size_t x) {
    return x >= 0 ? x : -x;
}



MyGrid escape(MyGrid grid) {
    assert(grid(1,1) == Floor); // Check that the initial tile is valid.
    
     //Finding the exit
     Tile exit = Wall;
     size_t exit_row;
     size_t exit_col;
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
     // fillig the visited array with false (not visited)
     for (size_t i = 0; i < grid.rows(); i++) {
         for (size_t j = 0; j < grid.cols(); j++) {
             visited[i][j] = false;
         }
     }

     // making cost array array
     size_t** cost2darray = new size_t* [grid.rows()];
     for (size_t i = 0; i < grid.rows(); i++) {
         cost2darray[i] = new size_t[grid.cols()];
     }
     // fillig the visited array with an arbitrary high number
     for (size_t i = 0; i < grid.rows(); i++) {
         for (size_t j = 0; j < grid.cols(); j++) {
             cost2darray[i][j] = 99999;
         }
     }


     vector<Tile>open;
     vector<size_t>closed;


     // IMPLEMENT A STAR PATHFINDING ALGORITHM

     Tile standing = grid(1, 1);
     visited[1][1] = true;
     open.push_back(grid(1,1)); // putting the starting tile on the open list

     size_t standing_row = 1;
     size_t standing_col = 1;
     size_t h_cost = 0; // distance from current to start (first position)
     size_t e_cost= abs(exit_row - 1) + abs(exit_col - 1); // distance from current to exit
     size_t t_cost = h_cost + e_cost; // total cost
     cost2darray[1][1] = t_cost;

     bool found = false;
     while (found) {
         //finding the unvisited tile with the lowest cost
         for (size_t i = 0; i < grid.rows(); i++) {
             for (size_t j = 0; j < grid.cols(); j++) {
                 
                     size_t t_cost_current = abs(i - 1) + abs(j - 1) + abs(i - exit_row) + abs(j - exit_col);
                     if (t_cost_current < t_cost) {
                         t_cost = t_cost_current;
                         e_cost = abs(i - exit_row) + abs(j - exit_col);
                         h_cost = abs(i - 1) + abs(j - 1);
                         standing_row = i;
                         standing_col = j;
                         standing = grid(i, j);
                         visited[i][j] = true;

                         

                     }
                 
             }
         }


         size_t minneighbor_row; // the row of the neighbor with the minimum cost
         size_t minneighbor_col; // the column of the neighbor with the minimum cost
         size_t t_cost_min = 99999;
         size_t e_cost_min;

         size_t rightneighbor_row;
         size_t rightneighbor_col;
         size_t t_cost_r;
         size_t leftneighbor_row;
         size_t leftneighbor_col;
         size_t t_cost_l;
         size_t topneighbor_row;
         size_t topneighbor_col;
         size_t t_cost_t;
         size_t downneighbor_row;
         size_t downneighbor_col;
         size_t t_cost_d;


         // neighbors of the standing tile

         // checking thr right neighbor
         if (grid(standing_row, standing_col+1) == Floor && grid.validPosition(standing_row, standing_col + 1)) {
             
             rightneighbor_row = standing_row;
             rightneighbor_row = standing_col +1;
             t_cost_r = abs(rightneighbor_row - exit_row) + abs(rightneighbor_col - exit_col) + abs(rightneighbor_row - 1) + abs(rightneighbor_col - 1);
             cost2darray[rightneighbor_row][rightneighbor_row] = t_cost_r;
             if (t_cost_r < t_cost_min) {
                 minneighbor_row = rightneighbor_row;
                 minneighbor_col = rightneighbor_col;
                 t_cost_min = t_cost_r;
                 e_cost_min = abs(exit_row - rightneighbor_row) + abs(exit_col - rightneighbor_col);
                 
             }
         }
         // checking the left neighbor
         if (grid(standing_row, standing_col-1) == Floor && grid.validPosition(standing_row,standing_col-1)) {
             
             leftneighbor_row = standing_row;
             leftneighbor_col = standing_col-1;
             t_cost_l = abs(leftneighbor_row - exit_row) + abs(leftneighbor_col - exit_col) + abs(leftneighbor_row - 1) + abs(leftneighbor_col - 1);
             cost2darray[leftneighbor_row][leftneighbor_row] = t_cost_l;
             if (t_cost_l < t_cost_min) {
                 minneighbor_row = leftneighbor_row;
                 minneighbor_col = leftneighbor_col;
                 t_cost_min = t_cost_l;
                 e_cost_min = abs(exit_row - leftneighbor_row) + abs(exit_col - leftneighbor_col);
             }
         }
         // checking top neighbor
         if (grid(standing_row-1, standing_col) == Floor && grid.validPosition(standing_row-1, standing_col)) {
             
             topneighbor_row = standing_row-1;
             topneighbor_col = standing_col;
             t_cost_t = abs(topneighbor_row - exit_row) + abs(topneighbor_col - exit_col) + abs(topneighbor_row - 1) + abs(topneighbor_col - 1);
             cost2darray[topneighbor_row][topneighbor_row] = t_cost_t;
             if (t_cost_t < t_cost_min) {
                 minneighbor_row = topneighbor_row;
                 minneighbor_col = topneighbor_col;
                 t_cost_min = t_cost_t;
                 e_cost_min = abs(exit_row - topneighbor_row) + abs(exit_col - topneighbor_col);
             }
         }
         // checking down neighbor
         if (grid(standing_row+1, standing_col) == Floor && grid.validPosition(standing_row+1, standing_col)) {
             
             downneighbor_row = standing_row +1;
             downneighbor_col = standing_col;
             t_cost_d = abs(downneighbor_row - exit_row) + abs(downneighbor_col - exit_col) + abs(downneighbor_row - 1) + abs(downneighbor_col - 1);
             cost2darray[downneighbor_row][downneighbor_row] = t_cost_d;
             if (t_cost_d < t_cost_min) {
                 minneighbor_row = downneighbor_row;
                 minneighbor_col = downneighbor_col;
                 t_cost_min = t_cost_d;
                 e_cost_min = abs(exit_row - downneighbor_row) + abs(exit_col - downneighbor_col);
             }
         }

         standing_row = minneighbor_row;
         standing_col = minneighbor_col;


         // Checking if path is found
         if (standing_row == exit_row && standing_col == exit_col && e_cost_min == 0) {
             found = true;
             grid(standing_row, standing_col) = Path;


             // drawing the path on the grid
             while (grid(1, 1) == Path) {
                 size_t mincost = 99999999;
                 size_t tcost;
                 size_t dcost;
                 size_t rcost;
                 size_t lcost;
                 // checking top neighbor
                 if (grid(standing_row -1, standing_col) == Floor) {
                     tcost = cost2darray[standing_row - 1][standing_col];
                     if (mincost > tcost)
                         mincost = tcost;
                 }

                 // checking down neighbor
                 if (grid(standing_row + 1, standing_col) == Floor) {
                     dcost = cost2darray[standing_row + 1][standing_col];
                     if (mincost > dcost)
                         mincost = dcost;
                 }
                 // checking right neighbor
                 if (grid(standing_row, standing_col+1) == Floor) {
                     rcost = cost2darray[standing_row][standing_col+1];
                     if (mincost > rcost)
                         mincost = rcost;
                 }
                 // checking left neighbor
                 if (grid(standing_row, standing_col-1) == Floor) {
                     lcost = cost2darray[standing_row][standing_col-1];
                     if (mincost > lcost)
                         mincost = lcost;
                 }



                 //assigning the Path to the tile with the minimum total cost
                 if (mincost == tcost) {
                     grid(standing_row - 1, standing_col) == Path;
                     standing_row = standing_row - 1;

                 }
                 else if (mincost == dcost) {
                     grid(standing_row + 1, standing_col) == Path;
                     standing_row = standing_row + 1;
                 }
                 else if (mincost == rcost) {
                     grid(standing_row, standing_col + 1) == Path;
                     standing_col = standing_col + 1;
                 }
                 else {
                     grid(standing_row, standing_col - 1) == Path;
                     standing_col = standing_col - 1;

                 }
             }

         }
         
             
     }
     

     


    
    // TODO implement some path finding algorithm find a correct path to an
    // exit tile, and then write that path to the grid.

     


    return grid;
}