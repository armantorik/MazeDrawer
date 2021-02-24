// Arman Torikoglu 25005 Homework 1

#include <iostream>
#include "Stack.h"
#include "randgen.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// To be stored in stack
struct coordinates
{
	unsigned int x;
	unsigned int y;

	coordinates(unsigned int nX, unsigned int nY) :
		x(nX), y(nY) {}
	coordinates()
	{}
};

// To be stored in 2D Vector
struct cell
{
	bool visited = false;
	bool down;
	bool left;
	bool right;
	bool up;
};


int main()
{
	// Part I

	// User input
	unsigned int nMaze, nRows, nCols, mazeId, entryX, entryY, exitX, exitY;
	cout << "Enter the number of mazes: ";
	cin >> nMaze;
	cout << "Enter the number of rows and columns(M and N) : ";
	cin >> nRows >> nCols;


	RandGen rand;
	unsigned int dir; // Direction

	// Map to be stored in a 2D matrix 
	vector <vector<cell>> matrix(nRows, vector<cell>(nCols));


	// Initializing the borders of the matrix
	// False means it is a border wall so it cannot be knocked down 
	// True means it is allowed to be knocked down  

	/*****************************************************/
	// First Modify the top and bottom edges.
	for (unsigned int i = 0; i < nRows; i++)
	{
		matrix[i][0].left = false; // Left side edges should be false
		matrix[i][0].down = true; // Others should be true
		matrix[i][0].up = true;
		matrix[i][0].right = true;

		matrix[i][nCols - 1].right = false; //  Right edges also should be false
		matrix[i][nCols - 1].left = true;
		matrix[i][nCols - 1].down = true;
		matrix[i][nCols - 1].up = true;

	}

	// Then, modify the left and right edges
	for (unsigned int i = 0; i < nCols; i++)
	{
		matrix[0][i].down = false; // Bottom of the map is also false
		matrix[0][i].left = true;
		matrix[0][i].up = true;
		matrix[0][i].right = true;

		matrix[nRows - 1][i].up = false; // Top is also false
		matrix[nRows - 1][i].right = true;
		matrix[nRows - 1][i].down = true;
		matrix[nRows - 1][i].left = true;
	}
	/*****************************************************/

	// The corners will also be modified
	matrix[0][0].left = false;
	matrix[0][0].down = false;
	matrix[0][0].visited = true;

	matrix[0][nCols - 1].right = false;
	matrix[0][nCols - 1].down = false;

	matrix[nRows - 1][0].up = false;
	matrix[nRows - 1][0].left = false;

	matrix[nRows - 1][nCols - 1].up = false;
	matrix[nRows - 1][nCols - 1].right = false;

	// The inside of the borders will be all true since we want them to be destructable
	for (unsigned int i = 1; i < nCols - 1; i++)
	{
		for (unsigned int k = 1; k < nRows - 1; k++)
		{
			matrix[k][i].right = true;
			matrix[k][i].left = true;
			matrix[k][i].up = true;
			matrix[k][i].down = true;
		}
	}

	vector <vector<vector<cell>>> mazes(nMaze, matrix); // Depending on how many map user wants maps will be stored in also a vector

	// Other variables...
	unsigned int x = 0, y = 0;
	bool allVisited;
	ofstream out;
	unsigned int nVisit, nCells = nCols * nRows; // Number of visits starts from 1 since we already started at (0,0)
	string fname;
	stringstream stm;
	Stack<coordinates> stack;
	coordinates point;
	size_t index;

	// For each maze do this
	for (size_t i = 0; i < nMaze; i++)
	{
		// Name of files
		index = i + 1;
		stm.str("");
		stm << "maze_" << index << ".txt";
		fname = stm.str();
		out.open(fname.c_str());

		
		out << nRows << " " << nCols << endl;
		allVisited = false;
		nVisit = 1;
		stack.clear();

		// Coordinate object that will be modified and be thrown to the stack
		x = 0;
		y = 0;

		point.x = x, point.y = y;
		stack.push(point);
		// Iterate until no cell remains unvisited
		while (!allVisited)
		{

			// First check if there is any movable direction otherwise pop     
			if ((mazes[i][y][x].right == true && !mazes[i][y][x + 1].visited) || (mazes[i][y][x].up == true && !mazes[i][y + 1][x].visited) || (mazes[i][y][x].left == true && !mazes[i][y][x - 1].visited) || (mazes[i][y][x].down == true && !mazes[i][y - 1][x].visited))
			{

				// (1 = Right), (2 =  Up), (3 = Left), (4 = Down)
				dir = rand.RandInt(1, 4); // Random generator decides the direction

				// Check if the cell in that direction is a visited or an indestructable wall if not, change the coordinates, push to stack and note that it is visited
				if (dir == 1 && mazes[i][y][x].right == true && !mazes[i][y][x + 1].visited)
				{
					mazes[i][y][x].right = false;
					mazes[i][y][x + 1].left = false;
					x++;
					point.x = x;
					stack.push(point);
					nVisit++;
				}
				else if (dir == 2 && mazes[i][y][x].up == true && !mazes[i][y + 1][x].visited)
				{
					mazes[i][y][x].up = false;
					mazes[i][y + 1][x].down = false;
					y++;
					point.y = y;
					stack.push(point);
					nVisit++;
				}
				else if (dir == 3 && mazes[i][y][x].left == true && !mazes[i][y][x - 1].visited)
				{
					mazes[i][y][x].left = false;
					mazes[i][y][x - 1].right = false;
					x--;
					point.x = x;
					stack.push(point);
					nVisit++;
				}
				else if (dir == 4 && mazes[i][y][x].down == true && !mazes[i][y - 1][x].visited)
				{
					mazes[i][y][x].down = false;
					mazes[i][y - 1][x].up = false;
					y--;
					point.y = y;
					stack.push(point);
					nVisit++;
				}
				mazes[i][y][x].visited = true;
			}
			else if (!stack.isEmpty()) // Backtrack to find any movable cell
			{
				stack.pop(point);
				x = point.x;
				y = point.y;
			}
			if (nVisit >= nCells) // If all visited then stop 
			{
				allVisited = true;
			}
		}

		// Revert back the outside walls to be true
		/***************************************************/
		for (size_t k = 0; k < nRows; k++)  // For left and right outside walls
		{
			mazes[i][k][0].left = true;
			mazes[i][k][nCols - 1].right = true;
		}
		for (size_t k = 0; k < nCols; k++) // For up and down outside walls
		{
			mazes[i][0][k].down = true;
			mazes[i][nRows - 1][k].up = true;
		}
		/***************************************************/

		// Output
		for (size_t y = 0; y < nRows; y++)
		{
			for (size_t x = 0; x < nCols; x++)
			{
				out << "x=" << x << " y=" << y << " l=" << int(mazes[i][y][x].left) << " r=" << int(mazes[i][y][x].right) << " u=" << int(mazes[i][y][x].up) << " d=" << int(mazes[i][y][x].down) << endl;
				mazes[i][y][x].visited = false;
			}
		}

		out.close();
	}


	// Part II	

	// User Input
	cout << "All mazes are generated.\n";
	cout << "Enter a maze ID between 1 to 5 inclusive to find a path : ";
	cin >> mazeId;
	cout << "Enter x and y coordinates of the entry points(x, y) or (column, row) : ";
	cin >> entryX >> entryY;
	cout << "Enter x and y coordinates of the exit points(x, y) or (column, row) : ";
	cin >> exitX >> exitY;


	matrix = mazes[mazeId - 1]; // Main matrix

	// File naming
	stm.str("");
	stm << "maze_" << mazeId << "_path_" << entryX << "_" << entryY << "_" << exitX << "_" << exitY << ".txt";
	fname = stm.str();
	out.open(fname);
	
	stack.clear();
	x = entryX, y = entryY;
	point.x = x, point.y = y;
	stack.push(point);
	
	while (x != exitX || y != exitY) // Similar to part 1
	{
		if ((matrix[y][x].right == false && !matrix[y][x + 1].visited)  // Check if there is any nearby suitable cell.
			|| (matrix[y][x].up == false && !matrix[y + 1][x].visited) // Else, backtrack from stack.
			|| (matrix[y][x].left == false && !matrix[y][x - 1].visited) 
			|| (matrix[y][x].down == false && !matrix[y - 1][x].visited))
		{
			dir = rand.RandInt(1, 4); // Random Direction

			if (dir == 1 && matrix[y][x].right == false && !matrix[y][x + 1].visited) 
			{
				x++;
				point.x = x;
				stack.push(point);
			}	
			else if (dir == 2 && matrix[y][x].up == false && !matrix[y + 1][x].visited)
			{
				y++;
				point.y = y;
				stack.push(point);
			}
			else if (dir == 3 && matrix[y][x].left == false && !matrix[y][x - 1].visited)
			{
				x--;
				point.x = x;
				stack.push(point);
			}
			else if (dir == 4 && matrix[y][x].down == false && !matrix[y - 1][x].visited)
			{
				y--;
				point.y = y;
				stack.push(point);
			}
			matrix[y][x].visited = true;
		}
		else
		{
			stack.pop(point);
			x = point.x;
			y = point.y;
		}
	}
	
	// Edit: Output 
	Stack<coordinates> temp;
	while (!stack.isEmpty())
	{
		stack.pop(point);
		temp.push(point);
	}

	while (!temp.isEmpty())
	{
		temp.pop(point);
		out << point.x << " " << point.y << endl;
	}

	out.close();
	return 0;
}