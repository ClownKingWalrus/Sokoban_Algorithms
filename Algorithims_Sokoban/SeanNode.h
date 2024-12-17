#pragma once
#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <stack>
#include <chrono>
//this class of node will also hold the boards
class SeanNode {
public:
	SeanNode();// default constructor
	SeanNode(SeanNode* inputNode);
	~SeanNode();
	SeanNode* parent = 0;
	std::pair<int, int> robot; //where the robot is x and y
	std::vector<std::pair<int, int>> specialBoxes;//could potentially just both vectors together to save space but at this time not nessesary
	std::vector<std::pair<int, int>> xBoxes;
	bool win = false;

	struct customReturn
	{
		int height = 0;
		int width = 0;
		std::vector<bool> sokoMind;
		std::unordered_map<char, std::pair<int, int>> boxMap;
		std::unordered_map<char, std::pair<int, int>> supplyMap;
		std::vector<std::pair<int, int>> standerdSupplyPoints;
	};

	struct legalReturn {
		//Node on left the map of said node on right
		std::vector<std::pair<SeanNode*, std::vector<char>>> nodeVector;
	};

	struct sizeOfNode {
		//due to sizeOfOperator being misleading we will not be using it
		int nodeItself = 8;
		int parent = 8; //pointers take 8 bytes
		int robot = 8;
		int SpBox = 40;
		int xBox = 40;
		int win = 8; //bools including allinment take 8 bytes but is only 1 byte of data

		//we will have to cacualte the SpBox and xBox seperatly since it can vary
		int total = win + robot + parent + nodeItself;
	};

	//this function reads the inital state of the puzzel and returns information for the Tree class to use
	customReturn ReadPuzzelFirstTime(std::string inputString);
	//this function checks all four directions for legal moves and returns a vector of nodes and map states so the Search algorithms can use that info
	static legalReturn LegalMoveChecks(SeanNode* inputNode, int height, int width, std::vector<bool> sokoMind, SeanNode FinalNode);
	//this prints out a board for std::cout debugging puropses
	static void PrintBoard(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode);
	//same thing but this has a bit of spice to show its a winner board
	static void PrintWinnerBoard(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode);
	//this creates a board based on the move that was deemed from LegalMoveChecks
	static void CreateNewBoard(SeanNode* inputNode, SeanNode* newNode, int Direction, int box, int height, int width, SeanNode FinalNode); // we dont need box type since where the player moves is always where the box was before
	//this checks if there boxes and if the move is legal with said box
	static int BoxChecker(int robotpos, int Direction, int width, int height, std::vector<bool> sokoMind);
	//if a box "clears"/ lands on a supplypoint thats valid it will call winCheck if it returns true we set inputNode->winChecker = true;
	static void BoxCleared(SeanNode* inputNode, std::pair<int, int> boxLocation, std::pair<int,int> newBoxLocation, SeanNode FinalNode);
	//this checks if all boxes are on there supply point if it is we return true
	static bool WinCheck(SeanNode* InputNode, SeanNode FinalNode);
	//this creats a vector of chars in a format for the code to do its checks on the board -its format is the same as PrintBoard();
	static std::vector<char> CreateCharSokoMind(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode);
	//this converts the vector into a string for Hashing purposes
	static std::string CreateStringSokoMind(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode);
	//this function makes the infosheet saved in the folder for seeing various amounts of data
	void InfoSheet(SeanNode* inputNode, int height, int width, std::vector<bool> sokoMind, SeanNode CompleteMapNode, std::chrono::time_point<std::chrono::high_resolution_clock> startTime, uint64_t NodesExpanded, uint64_t TotalNodes, std::string mapName, std::string SearchAlgorithm);

};