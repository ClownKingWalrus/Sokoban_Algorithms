#pragma once
#include "node.h"
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <chrono>
//this class of node will also hold the boards
class SeanNode {
public:
	SeanNode();// default constructor
	SeanNode(SeanNode* inputNode);
	~SeanNode();
	SeanNode* parent = 0;
	std::pair<int, int> robot;
	std::vector<std::pair<int, int>> specialBoxes;//could potentially just stack these 2 next to eachother
	std::vector<std::pair<int, int>> xBoxes;
	bool win = false;
	//std::vector<SeanNode*> childVector;

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
		std::vector<std::pair<SeanNode*, std::vector<char>>> nodeVector;
	};

	customReturn ReadPuzzelFirstTime(std::string inputString);
	static legalReturn LegalMoveChecks(SeanNode* inputNode, int height, int width, std::vector<bool> sokoMind, SeanNode FinalNode);
	static void PrintBoard(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode);
	static void PrintWinnerBoard(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode);
	static void CreateNewBoard(SeanNode* inputNode, SeanNode* newNode, int Direction, int box, int height, int width, SeanNode FinalNode); // we dont need box type since where the player moves is always where the box was before
	static int BoxChecker(int robotpos, int Direction, int width, int height, std::vector<bool> sokoMind);
	static void BoxCleared(SeanNode* inputNode, std::pair<int, int> boxLocation, std::pair<int,int> newBoxLocation, SeanNode FinalNode);
	static bool WinCheck(SeanNode* InputNode, SeanNode FinalNode);
	static std::vector<char> CreateCharSokoMind(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode);
	static std::string CreateStringSokoMind(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode);
	void InfoSheet(SeanNode* inputNode, int height, int width, std::vector<bool> sokoMind, SeanNode CompleteMapNode, std::chrono::time_point<std::chrono::high_resolution_clock> startTime, int NodesExpanded);

};