#include "node.h"

/*******************************************//**
* Default constructor
***********************************************/
Node::Node() {
	name = "";
	data = 0;
	childVector = {};
}

Node::Node(int Data, std::string Name) {
	name = Name;
	data = Data;
	childVector = {};
}

Node::Node(int Data) {
	name = "";
	data = Data;
	childVector = {};
}

Node::~Node() {
	for (int i = 0; i < childVector.size(); i++) {
		delete childVector[i]; //start the destructors for the children nodes
		childVector[i] = nullptr; //set the ptr to null so no blackhat hackers can mess up my day
	}
	childVector.clear(); // make sure child vector is free
}

/*******************************************//**
* Create a new node with data
***********************************************/
Node* Node::CreateNewNode(int Data) {
	Node* newNode = new Node(Data); //#optimized
	return newNode;
}

//for a double tree will need to be overwriten for other algrothims
void Node::AddChild(Node* inputNode, int Data) {
	Node* newNode = new Node(Data);
	if (inputNode->childVector.empty()) {
		newNode->name = "Left";
	}
	else {
		newNode->name = "Right";
	}
	inputNode->childVector.push_back(newNode);
}

void Node::RecursivePrintNodes(Node* inputNode) {
	//print the current node
	std::cout << "Name: " << inputNode->name << " Data: " << inputNode->data << " Child Vector Size: " << inputNode->childVector.size() << std::endl;

	for (auto it = inputNode->childVector.begin(); it != inputNode->childVector.end(); ++it) {
		Node::RecursivePrintNodes(*it); // calls the next child untill it hits end then tree works back up
	}
	std::cout << "no more children going back up" << std::endl;
}

std::vector<Node*> Node::getChildVector() {
	return childVector;
}