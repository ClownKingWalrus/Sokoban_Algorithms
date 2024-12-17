#include "Tree.h"

Tree::Tree(std::string inputString) {
	rootNode = new SeanNode();
	finalNode = SeanNode();
	SeanNode::customReturn Temp;
	rootNode->parent = 0;
	Temp = rootNode->ReadPuzzelFirstTime(inputString); // this returns a struct with alot of data we need
	width = Temp.width; //copy width of map
	height = Temp.height; //copy height of map
	sokoMind = Temp.sokoMind; // copy T/F map
	finalNode.xBoxes = Temp.standerdSupplyPoints; //copy Named supply points
	for (auto pair : Temp.boxMap) {
		for (auto pair2 : Temp.supplyMap) {
			if (pair.first == (pair2.first - 32)) {
				finalNode.specialBoxes.push_back(pair2.second); // push same letterd boxes sequentially to save space
				rootNode->specialBoxes.push_back(pair.second);
			}
		}
	}
	//need to figure out why i made a complete map node when its finalNode prob due to delete
	CompleteMapNode = finalNode;
}

Tree::~Tree() {
	delete rootNode; //starts deconstruct chain of nodes
	rootNode = nullptr;
}