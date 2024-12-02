#pragma once
#include "tree.h"
#include <stack>
#include <unordered_set>
#include <iostream>
#include <string>
#include <functional>

class DFS {
public:
	//std::stack<std::vector<char>*> closedlistmap;
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

	//		utilnode.LegalMoveChecks(inputnode); //input node now becomes child node
	//		if (!fringe.empty()) {
	//			fringe.pop();
	//		}
	//		for (auto it = inputnode->childvector.begin(); it < inputnode->childvector.end(); ++it) {
	//			if (testset->find(vecttostring((*it)->sokomind)) != testset->end()) {//check new child map aganst stored maps
	//				//if not unique do nothing
	//			} else {
	//				fringe.push(*it);
	//				count2++;
	//					//inputnode = *it; // set input node to the child that is valid
	//					//break;
	//				}
	//			continue; //should go to next child if that child already exist in the table
	//		}
	//		inputnode = fringe.top();
	//	}
	//	if (inputnode->win) {
	//		completed = true;
	//	}
	//	return;
	//}
	
	void DFSCheckOverhaul(SeanNode* inputNode, int width, int height, std::vector<bool> sokoMind, SeanNode FinalNode, SeanNode CompleteMapNode, std::chrono::time_point<std::chrono::high_resolution_clock> startTime) {
		testSet->insert(VectToStringToInt((inputNode->CreateCharSokoMind(inputNode, sokoMind, width, height, FinalNode)))); //store first map
		long long int counter = 1;
		long long int counter2 = 0;
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
						CompleteMapNode.InfoSheet(it->first, height, width, sokoMind, CompleteMapNode, startTime, counter);
						CompleteMapNode.PrintBoard(it->first, sokoMind, width, height, CompleteMapNode);
						std::cout << "Winner" << std::endl;
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