#pragma once
#include "tree.h"
#include <functional>
#include <queue>
class ASTAR {
public:

	struct AStarPair {
		std::pair<int, SeanNode*> aStarPair;
		bool operator<(const AStarPair& other) const {
			return aStarPair.first > other.aStarPair.first;
		}
	};

	std::priority_queue<AStarPair> priorityQueue;

	//create custom hash
	int VectToStringToInt(std::vector<char> inputvec) {
		std::string holder(inputvec.begin(), inputvec.end());
		std::hash<std::string> Hasher;
		int temp = Hasher(holder);
		return temp;
	}

	int AStarValue(SeanNode* inputNode, SeanNode FinalNode, int distanceFromRoot) {
		int mapValue = 0;
		int robotDistanceToCloesetBox = 9999;
		for (auto it = inputNode->specialBoxes.begin(); it != inputNode->specialBoxes.end(); ++it) {
			auto it2 = FinalNode.specialBoxes.begin();
			//get the manhatten distance between the boxes
			int num1 = it->first - it2->first;
			int num2 = it->second - it2->second;

			if (num1 < 0) {
				num1 = num1 * -1;
			}
			if (num2 < 0) {
				num2 = num2 * -1;
			}

			int robotdistX = (inputNode->robot.first - it->first);
			int robotdistY = (inputNode->robot.second - it->second);

			if (robotdistX < 0) {
				robotdistX = robotdistX * -1;
			}

			if (robotdistY < 0) {
				robotdistY = robotdistY * -1;
			}

			if ((robotdistX + robotdistY) < robotDistanceToCloesetBox) {
				robotDistanceToCloesetBox = (robotdistX + robotdistY); //if any are less we will add here  fw
			}
			//store them so we can convert it into a A* value
			mapValue += num1;
			mapValue += num2;
		}

		for (auto it = inputNode->xBoxes.begin(); it != inputNode->xBoxes.end(); ++it) {
			int boxClosesToStorage = 999;//some ridiculously high number
			for (auto it2 = FinalNode.xBoxes.begin(); it2 != FinalNode.xBoxes.end(); ++it2) {
				int num1 = it->first - it2->first;
				int num2 = it->second - it2->second;

				if (num1 < 0) {
					num1 = num1 * -1;
				}
				if (num2 < 0) {
					num2 = num2 * -1;
				}

				if (num1 + num2 < boxClosesToStorage) {
					boxClosesToStorage = (num1 + num2); //set box closest to storage to be the = to the new closest storage
				}
				int robotdistX = (inputNode->robot.first - it->first);
				int robotdistY = (inputNode->robot.second - it->second);

				if (robotdistX < 0) {
					robotdistX = robotdistX * -1;
				}

				if (robotdistY < 0) {
					robotdistY = robotdistY * -1;
				}

				if ((robotdistX + robotdistY) < robotDistanceToCloesetBox) {
					robotDistanceToCloesetBox = (robotdistX + robotdistY); //if any are less we will replace the prior one
				}

				if (it2 == (FinalNode.xBoxes.end() - 1)) {
					mapValue += boxClosesToStorage; //once we are at the end we know we checked all boxes possible for one box
				}
			}
		}
		//once we caculate all values for ASTAR we add them together the three are
		// Distance from Orginal node + Box distances + Robot distance from closest box
		mapValue += robotDistanceToCloesetBox;
		mapValue += distanceFromRoot;
		return mapValue;
	}

	SeanNode utilnode;
	std::unordered_set<int>* testSet = new std::unordered_set<int>;

	void ASTAROVERHAUL(SeanNode* inputNode, int width, int height, std::vector<bool> sokoMind, SeanNode FinalNode, SeanNode CompleteMapNode, std::chrono::time_point<std::chrono::high_resolution_clock> startTime, std::string mapName) {
		//debug
		//int mapAStar = 0;
		//inputNode->PrintBoard(inputNode, sokoMind, width, height, FinalNode);
		//mapAStar = AStarValue(inputNode, FinalNode, 0);
		//DebugAStar(inputNode, width, height, sokoMind, FinalNode, mapAStar, 0);
		//debug

		//store first node in the hash
		testSet->insert(VectToStringToInt((inputNode->CreateCharSokoMind(inputNode, sokoMind, width, height, FinalNode))));
		int distanceFromRoot = 0;
		uint64_t counter = 0;
		uint64_t counter2 = 0;
		while (!inputNode->win) {
			//std::cout << "CurrentParent:" << std::endl;
			//inputNode->PrintBoard(inputNode, sokoMind, width, height, FinalNode);
			//std::cout << "^^^CurrentParent^^^" << std::endl;
			//check all legal moves of the curren node
			SeanNode::legalReturn tempReturn = SeanNode::LegalMoveChecks(inputNode, height, width, sokoMind, FinalNode);
			//determin there validity
			int tempHash = 0;
			for (int i = 0; i < tempReturn.nodeVector.size(); i++) {
				tempHash = VectToStringToInt(tempReturn.nodeVector[i].second);
				if (testSet->find(tempHash) != testSet->end()) {
					//take out the whole std::pair since neither are unique
					tempReturn.nodeVector.erase(tempReturn.nodeVector.begin() + i);
					i--;
					continue;
				}
				else {
					//should be unique if it passes the if statement so we put it into the hash here
					testSet->insert(tempHash);
					if (tempReturn.nodeVector[i].first->win) {
						std::string searchAlgorithm = "A_STAR";
						uint64_t TotalNodes = testSet->size();
						CompleteMapNode.InfoSheet(tempReturn.nodeVector[i].first, height, width, sokoMind, CompleteMapNode, startTime, counter, TotalNodes, mapName, searchAlgorithm);
						CompleteMapNode.PrintBoard(tempReturn.nodeVector[i].first, sokoMind, width, height, CompleteMapNode);
						std::cout << "\nWinner" << std::endl;
						std::cout << "NODES EXPANDED: " << counter << std::endl;
						std::cout << '\n';
						return; //break out of loop early  since the while loop will end since the winner node is now the input node
					}
				}
			}
			//once the nodevector is cleared of copies get the a* values
			AStarPair tempAStarPair;

			//get the depth
			SeanNode* tempNode = new SeanNode(inputNode);
			distanceFromRoot = 0;
			while (!tempNode->parent == 0) {
				distanceFromRoot++;
				tempNode = tempNode->parent;
			}

			for (auto it = tempReturn.nodeVector.begin(); it != tempReturn.nodeVector.end(); ++it) {
				tempHash = AStarValue(it->first, FinalNode, distanceFromRoot);
				tempAStarPair.aStarPair = { tempHash, it->first };
				priorityQueue.push(tempAStarPair);
				//debug
				//DebugAStar(it->first, width, height, sokoMind, FinalNode, tempHash, distanceFromRoot);
			}
			if (!priorityQueue.empty()) {
				inputNode = priorityQueue.top().aStarPair.second;

				//std::cout << "Canidiate Chosen AstarValue: " << priorityQueue.top().aStarPair.first << std::endl;
				//inputNode->PrintBoard(priorityQueue.top().aStarPair.second, sokoMind, width, height, FinalNode);
				//std::cout << "\n^^^Canidiate Chosen AstarValue^^^: " << priorityQueue.top().aStarPair.first << std::endl;

				priorityQueue.pop();
				counter++;
				if (counter > (100000 * counter2)) {
					std::cout << "NODES EXPANDED: " << counter << std::endl;;
					counter2++;
				}
			}
			else {
				std::cout << "Not possible solution" << std::endl;
			}
		}
	}
	
	void DebugAStar(SeanNode* inputNode, int width, int height, std::vector<bool> sokoMind, SeanNode FinalNode, int aStarValue, int distanceFromRoot) {
		//print Current Canidits with there values
		std::cout << "Canditiate to be chosen AStarValue: " << aStarValue << " Distance From Root: " << distanceFromRoot << " \nnote algorithim can go back if candites values are higher than another canidate already in queue" << std::endl;
		inputNode->PrintBoard(inputNode, sokoMind, width, height, FinalNode);
	}
};