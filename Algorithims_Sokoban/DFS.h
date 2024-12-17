#pragma once
#include "tree.h"
#include <functional>

class DFS {
public:
	int count2 = 1;
	std::stack<SeanNode*> fringe;
	//create custom hash
	int VectToStringToInt(std::vector<char> inputvec) {
		std::string holder(inputvec.begin(), inputvec.end());
		std::hash<std::string> Hasher;
		int temp = Hasher(holder);
		return temp;
	}

	SeanNode utilnode;
	std::unordered_set<int>* testSet = new std::unordered_set<int>;
	
	void DFSCheckOverhaul(SeanNode* inputNode, int width, int height, std::vector<bool> sokoMind, SeanNode FinalNode, SeanNode CompleteMapNode, std::chrono::time_point<std::chrono::high_resolution_clock> startTime, std::string mapName) {
		//if you get a out of bounds error here it means you inputted a mapname thats not in the folder
		testSet->insert(VectToStringToInt((inputNode->CreateCharSokoMind(inputNode, sokoMind, width, height, FinalNode)))); //store first map
		uint64_t counter = 1;
		uint64_t counter2 = 0;
		while (!inputNode->win) { //input node does not get affected by this
			SeanNode::legalReturn tempStruct = inputNode->LegalMoveChecks(inputNode, height, width, sokoMind, FinalNode);
			for (auto it = tempStruct.nodeVector.begin(); it != tempStruct.nodeVector.end(); ++it) {
				if (testSet->find(VectToStringToInt(it->second)) != testSet->end()) { //scan if it already exist
					//std::cout << "redundent node found";
					//this child is not unique so dont bother adding it
				} else {
					fringe.push(it->first);
					testSet->insert(VectToStringToInt(it->second));
					if (it->first->win) {
						std::string searchAlgorithm = "DFS";
						uint64_t TotalNodes = testSet->size();
						CompleteMapNode.InfoSheet(it->first, height, width, sokoMind, CompleteMapNode, startTime, counter, TotalNodes, mapName, searchAlgorithm);
						CompleteMapNode.PrintBoard(it->first, sokoMind, width, height, CompleteMapNode);
						std::cout << "\nWinner" << std::endl;
						std::cout << "NODES EXPANDED: " << counter << std::endl;
						std::cout << '\n';
						return; //break out of loop early  since the while loop will end since the winner node is now the input node
					}
				}
			}
			if (!fringe.empty()) { //after children pushed in we can set the new parent to the top most child
				inputNode = fringe.top();
				counter++;
				if (counter > (100000 * counter2)) {
					std::cout << "NODES EXPANDED: " << counter << std::endl;;
					counter2++;
				}
				fringe.pop();
			}
			else {
				std::cout << "No Valid Path to beat map\n";
				return;
			}
		}
	}
};