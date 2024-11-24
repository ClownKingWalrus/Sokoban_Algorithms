#include "tree.h"
//
//Tree::Tree() {
//	rootNode = new NodeSokoMind();
//	rootNode->name = "RootNode";
//}

Tree::Tree(NodeSokoMind* inputNode) {
	rootNode = inputNode;
}

Tree::~Tree() {
	delete rootNode; //starts deconstruct chain of nodes
	rootNode = nullptr;
}