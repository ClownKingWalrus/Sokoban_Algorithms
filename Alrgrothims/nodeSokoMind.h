#pragma once
#include "node.h"

//this class of node will also hold the boards
class NodeSokoMind:Node {
public:
	NodeSokoMind();// default constructor
	NodeSokoMind(NodeSokoMind* inputNode);
	//NodeSokoMind(NodeSokoMind* inputNode, int Distance);
	~NodeSokoMind();
	std::vector<char>* sokoMind = new std::vector<char>; //will change to array once i figure it out
	std::vector<char>::iterator robotIterator = sokoMind->begin();
	std::vector<char>::iterator supplyPointa = sokoMind->begin(); //basically store the posistion of supply points incase robot runs over it
	std::vector<char>::iterator supplyPointb = sokoMind->begin();
	std::vector<char>::iterator supplyPointc = sokoMind->begin();
	std::vector<char>::iterator supplyPointd = sokoMind->begin();
	std::vector<int> supplyPointX;
	bool win = false;
	int distance = 0;//robot iterator distance
	int distancea = 0;
	int distanceb = 0;
	int distancec = 0;
	int distanced = 0;
	int height = 0;
	int width = 0;
	int count = 0;
	
	const static int checkArrSize = 5;
	char checkArr[checkArrSize] = { 'A','B','C','D', 'X'};
	std::vector<NodeSokoMind*> childVector;
	

	void ReadPuzzelFirstTime(std::string inputString);
	void LegalMoveChecks(NodeSokoMind* inputNode);
	void PrintBoard();
	void PrintBoard(NodeSokoMind* inputNode);
	void CreateNewBoard(NodeSokoMind* inputNode, NodeSokoMind* newNode, std::vector<char>::iterator Move, int Distance);//move robot
	void CreateNewBoard(NodeSokoMind* inputNode, NodeSokoMind* newNode, std::vector<char>::iterator Move, std::vector<char>::iterator BoxMove, int Distance); // we dont need box type since where the player moves is always where the box was before
	int BoxChecker(std::vector<char>::iterator Robot, int Direction);
	void SupplyPointReset(NodeSokoMind* inputNode);
	void SupplyPointSetter(NodeSokoMind* parentNode);
	void SupplyPointSpecialReset(NodeSokoMind* parentNode);
	bool WinCheck(NodeSokoMind* inputNode);
	int NodesExpanded(NodeSokoMind* rootNode);
	void BoxCleared(NodeSokoMind* inputNode, char supplypoint);
	std::vector<NodeSokoMind*> getChildVector();
};