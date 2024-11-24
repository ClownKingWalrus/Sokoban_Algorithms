#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
/*******************************************//**
 * This class is the base node class that may be inhertied by other algrothims node classes
 ***********************************************/
class Node {
public:
	/*******************************************//**
	 * Default constructor
	 ***********************************************/
	Node();
	Node(int Data, std::string Name);
	Node(int Data);
	~Node();

	/*******************************************//**
	 * Class Varibles
	 ***********************************************/
	std::string name;
	int data;
	std::vector<Node*> childVector;

	/*******************************************//**
	 * Class Functions
	 ***********************************************/
	static Node* CreateNewNode(int Data); //returns new node
	void AddChild(Node* inputNode, int Data); //adds child to inputed node
	void RecursivePrintNodes(Node* inputNode);
	std::vector<Node*> getChildVector();
};