#include "Maze.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
using namespace std;


Maze::Maze()
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				myArray[i][j][k] = 1;
			}
		}
	}
}

bool Maze::find(int x, int y, int z) 
{
	//
	//

	Solution.push_back("(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")");
	if (x == 4 && y == 4 && z == 4) { //if we get to the end enter true
		return true;
	}
	if (x > 4 || x < 0 || y < 0 || y > 4 || z < 0 || z > 4) { //Prevents from falling off the cube
		if (Solution.size() >= 1) {
			Solution.pop_back();
		}
			
		return false;
	}
	if (myArray[x][y][z] == 2 || myArray[x][y][z] == 0) {//Prevents back tracking
		Solution.pop_back();
		return false;

	}

	myArray[x][y][z] = 2;

	if (find(x, y - 1, z) || find(x, y + 1, z) || find(x + 1, y, z) || find(x - 1, y, z) || find(x, y, z + 1) || find(x, y, z - 1)) {
		return true;
	}
	else {
		Solution.pop_back();
		return false;
	}
			
	
}

string Maze::getMaze()
{
	stringstream ss;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (myArray[i][j][k] == 2) {
					myArray[i][j][k] = 1;
				}
				ss << myArray[i][j][k] << " ";
			}
			ss << endl;
		}
		ss << endl;
	}
	return ss.str();
}

void Maze::createRandomMaze()
{ 
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if ((i == 0 && j == 0 && k == 0) || (i == 4 && j == 4 && k == 4)) {
					myArray[i][j][k] = 1;
				}
				else {
					myArray[i][j][k] = rand() % 2;
				}
			}
			
		}
	}
}

bool Maze::importMaze(string file_name)
{
	/*
	Check kun: 
	1) sakto ba ang mga numbers?
	2) nag sugod ug tapos sa 1?
	3) 0 or 1 tanan?
	*/
	int tempMaze[5][5][5];
	string line = " ";
	stringstream ss;
	fstream file;
	string passmein;
	int counter = 0;
	int number = 0;
	
	file.open(file_name);

	if (!file.is_open()) {//covers for when file is non-existant
		return false;
	}
	else {
		while (file >> line) {
			counter++;
		}

		if (counter != 125) {
			return false;
		}
		else {
			file.close();
			file.open(file_name);

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						for (int k = 0; k < 5; k++) {
							file >> number;
							if (number != 1 && number!=0) {
								return false;
							}
							else {				
								tempMaze[i][j][k] = number;
							}
						}

					}
				}
			
			if (tempMaze[0][0][0] != 1 || tempMaze[4][4][4] != 1) {//does it also need to include [4][4][4]?
				return false;
			}
			else {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					for (int k = 0; k < 5; k++) {

						myArray[i][j][k] = tempMaze[i][j][k];
					}
				}
			}
				file.close();
				return true;
			}
		}
	}
}

vector<string> Maze::solveMaze()
{
	stringstream ss;
	string addme;
	Solution.clear();
	find(0, 0, 0);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (myArray[i][j][k] == 2) {
					myArray[i][j][k] = 1;
				}
				
			}
		}
	}
												//all you want to do here is call find, set 2s to 1s and return solution
												//inside the find function push and pop
	///if I can go to the next one push the coordinate onto the vector and pop back if you can't go any further
	
	return Solution;
}

Maze::~Maze() {

}
