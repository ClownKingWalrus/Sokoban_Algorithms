#pragma once
#include "SeanNode.h"
class Tree {
public:
/*******************************************//**
* Default constructor
***********************************************/
	//Tree();
	Tree(std::string inputString);
	~Tree();

/*******************************************//**
* Class Varibles
***********************************************/
	SeanNode* rootNode;
	SeanNode finalNode;
	SeanNode CompleteMapNode;
	std::vector<bool> sokoMind;
	int width = 0;
	int height = 0;

/*******************************************//**
* Class Functions
***********************************************/

};