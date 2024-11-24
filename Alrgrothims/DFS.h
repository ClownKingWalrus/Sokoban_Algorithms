#pragma once
#include "tree.h"
#include <stack>
#include <unordered_set>
#include <iostream>
#include <string>

class DFS {
public:
	//std::stack<std::vector<char>*> closedListMap;

	//create custom hash
	std::string VectToString(std::vector<char>* inputVec) {
		std::string holder(inputVec->begin(), inputVec->end());
		return holder;
	}

	int count = 0;
	bool completed = false;
	std::unordered_set<std::string> testSet;

	void DFSCheck(NodeSokoMind* inputNode) {
		inputNode->win = completed;
		if (completed == true) { //if its a winner
			return;//dosent work just returns to the prior function call of this recrusive function lol
		}
		testSet.insert(VectToString(inputNode->sokoMind)); //store map state
		count++;
		/*if (inputNode->supplyPointX.size() == 0) {
			std::cout << "we are in a 0 SupplypointX: Board Below\n";
			std::cout << "\n";
			inputNode->PrintBoard(inputNode);
			std::cout << "\n";
		}*/
		//std::cout << "\n\n\n" << count << "\n";
		//inputNode->PrintBoard(inputNode);
		inputNode->LegalMoveChecks(inputNode); //legal move checks on the first child
		if (inputNode->win) {
			completed = true;
			return;
		}
		for (auto it = inputNode->childVector.begin(); it < inputNode->childVector.end(); ++it) {
			if (completed) {
				return;
			}
			if (testSet.find(VectToString((*it)->sokoMind)) != testSet.end()) {//check new child map aganst stored maps 
				//std::cout << "found same move moving next child" << std::endl;
				continue; //should go to next child if that child already exist in the table
			}
			else {
				DFSCheck(*it); //if unique move this will
			}
		}
		return;
	}
};