#include "nodeSokoMind.h"

NodeSokoMind::NodeSokoMind() {
	height = 0;
	width = 0;
}

NodeSokoMind::NodeSokoMind(NodeSokoMind* inputNode) {
	sokoMind->assign(inputNode->sokoMind->begin(), inputNode->sokoMind->end()); //copy values over to the new board
	supplyPointX.assign(inputNode->supplyPointX.begin(), inputNode->supplyPointX.end()); //copy 'S' supply points over
	distance = inputNode->distance;
	width = inputNode->width;
	height = inputNode->height;
	robotIterator = (sokoMind->begin() + distance); //initlize the iterator somewhere will not be correct on new boards
	SupplyPointSetter(inputNode); //sets all the distances and supplypoint It
}

NodeSokoMind::~NodeSokoMind() {
	sokoMind->clear();
	childVector.clear();
}
//this reads the puzzel and should return the data or set the nodes data
void NodeSokoMind::ReadPuzzelFirstTime(std::string inputString) {
	int i = 0;
	std::ifstream fileData(inputString); // create a way to access the file
	std::string oneLine;
	
	while (getline(fileData, oneLine)) {
		height++;//returns correct height
		for (int i = 0; i < oneLine.size(); i++) {
			sokoMind->push_back(oneLine[i]);
			if (oneLine[i] == 'R') {
				distance = std::distance(sokoMind->begin(), (sokoMind->end() - 1));
			}
			//save supply points distance so we can set them once robot or box is off
			if (oneLine[i] == 'a') {
				distancea = std::distance(sokoMind->begin(), (sokoMind->end() - 1));
			}
			if (oneLine[i] == 'b') {
				distanceb = std::distance(sokoMind->begin(), (sokoMind->end() - 1));
			}
			if (oneLine[i] == 'c') {
				distancec = std::distance(sokoMind->begin(), (sokoMind->end() - 1));
			}
			if (oneLine[i] == 'd') {
				distanced = std::distance(sokoMind->begin(), (sokoMind->end() - 1));
			}
			if (oneLine[i] == 'S') {
				supplyPointX.push_back(std::distance(sokoMind->begin(), (sokoMind->end() - 1))); //push each point into here
			}
		}
	}


	width = oneLine.size();
	for (auto it = sokoMind->begin(); it != sokoMind->end(); ++it) { //this only gets ran once not every node so leave it its not actually slow
		if (i == width) {
			std::cout << std::endl;
			i = 0;
		}

		std::cout << *it;
		i++;
	}
	robotIterator = (sokoMind->begin() + distance); // get the actual robot iterator after we are done pushing back
	if (distancea == 0) {
		distancea = -1;
	}
	if (distanceb == 0) {
		distanceb = -1;
	}
	if (distancec == 0) {
		distancec = -1;
	}
	if (distanced == 0) {
		distanced = -1;
	}
	fileData.close(); //close the file
}

void NodeSokoMind::LegalMoveChecks(NodeSokoMind* inputNode) {
	//since we know the height and width we can add +/- width to see top and bottom row checks
	//make a check with the parent iterator posistion so we do not create a extra move back in the same place
	//std::cout << "\n\nCURRENT PARENT NODE\n\n";
	//PrintBoard(inputNode);
	//std::cout << "\n\nCURRENT PARENT NODE\n\n";
	if (win) {
		return; // this node is a winner no need to do any checks
	}

	//BOTTOM CHECK
	if (*(inputNode->robotIterator + width) != 'O') {//if going in we know there is no wall down
		switch (BoxChecker(inputNode->robotIterator, 1)) {
		case 1: {//down legal move with box
			int newDistance = (distance + width);
			NodeSokoMind* newNode = new NodeSokoMind(inputNode);
			*newNode->robotIterator = 32; //set the current posistion to empty space
			CreateNewBoard(inputNode, newNode, (newNode->robotIterator + width), ((newNode->robotIterator) + (width * 2)), newDistance);
			if (win) {
				break; // this node is a winner no need to do any checks
			}
			break;
		}
		case 0: {//bottom legal move No Box
			//create a new node here so we can ajust Its sokomind board and not the prior one
			int newDistance = (distance + width);
			NodeSokoMind* newNode = new NodeSokoMind(inputNode);
			*newNode->robotIterator = 32; //set the current posistion to empty space
			CreateNewBoard(inputNode, newNode, (newNode->robotIterator + width), newDistance);
			break;
		}
		case -1: //another box is in direction of push
			break;
		default:
			break;
		}
	}

	//TOP CHECK
	if (*(inputNode->robotIterator - width) != 'O') {//if going in we know there is no wall left
		switch (BoxChecker(inputNode->robotIterator, 2)) {
		case 2: {//left legal move with box
			int newDistance = (distance - width);
			NodeSokoMind* newNode = new NodeSokoMind(inputNode);
			*newNode->robotIterator = 32; //set the current posistion to empty space
			CreateNewBoard(inputNode, newNode, (newNode->robotIterator - width), ((newNode->robotIterator) - (width * 2)), newDistance);
			if (win) {
				break; // this node is a winner no need to do any checks
			}
			break;
		}
		case 0: { //top legal move No Box
			//create a new node here so we can ajust Its sokomind board and not the prior one
			int newDistance = (distance - width);
			NodeSokoMind* newNode = new NodeSokoMind(inputNode);
			*newNode->robotIterator = 32; //set the current posistion to empty space
			CreateNewBoard(inputNode, newNode, (newNode->robotIterator - width), newDistance);
			break;
		}
		case -1: //another box is in direction of push
			break;
		default:
			break;
		}
	}

	//LEFT CHECK
	if (*(inputNode->robotIterator - 1) != 'O') {//if going in we know there is no wall left
		switch (BoxChecker(inputNode->robotIterator, 3)) {
		case 3: {//left legal move with box
			int newDistance = (distance - 1);
			NodeSokoMind* newNode = new NodeSokoMind(inputNode);
			*newNode->robotIterator = 32; //set the current posistion to empty space
			CreateNewBoard(inputNode, newNode, ((newNode->robotIterator) - 1), ((newNode->robotIterator) - 2), newDistance);
			if (win) {
				break; // this node is a winner no need to do any checks
			}
			break;
		}
		case 0: {//Left legal move No Box
			int newDistance = (distance - 1);
			NodeSokoMind* newNode = new NodeSokoMind(inputNode);
			*newNode->robotIterator = 32; //set the current posistion to empty space
			CreateNewBoard(inputNode, newNode, (newNode->robotIterator - 1), newDistance);
			break;
		}
		case -1: //another box is in direction of push
			break;
		default:
			break;
		}
	}

	//RIGHT CHECK
	if (*(inputNode->robotIterator + 1) != 'O') {//if going in we know there is no wall left
		switch (BoxChecker(inputNode->robotIterator, 4)) {
		case 4: {//left legal move with box
			int newDistance = (distance + 1);
			NodeSokoMind* newNode = new NodeSokoMind(inputNode);
			*newNode->robotIterator = 32; //set the current posistion to empty space
			
			CreateNewBoard(inputNode, newNode, (newNode->robotIterator + 1), ((newNode->robotIterator) + 2), newDistance);
			if (win) {
				break; // this node is a winner no need to do any checks
			}
			break;
		}
		case 0: {//right legal move No Box
			int newDistance = (distance + 1);
			NodeSokoMind* newNode = new NodeSokoMind(inputNode);
			*newNode->robotIterator = 32; //set the current posistion to empty space
			CreateNewBoard(inputNode, newNode, (newNode->robotIterator + 1), newDistance);
			break;
		}
		case -1: //another box is in direction of push
			break;
		default:
			break;
		}
	}
}

void NodeSokoMind::CreateNewBoard(NodeSokoMind* inputNode, NodeSokoMind* newNode, std::vector<char>::iterator Move, int Distance) {
	newNode->robotIterator = Move; //set actual iterator to new posistion
	//NOTE YOU CANNOT PRINT AND SEE R UNTIL THIS IS SET AS THE PRIOR FUNCTION TECHINCALLY REMOVES R TEMP
	newNode->SupplyPointSetter(newNode);
	*newNode->robotIterator = 'R'; //visually update
	newNode->distance = Distance;//update distance so when constructed next child has correct coordinates
	NodeSokoMind::SupplyPointReset(newNode);
	inputNode->childVector.push_back(newNode); //push newly created node in old node
}

//only used if box move is valid // also Move is effectivly where the box currently is since the player is pushing into box but hasent been set yet so box is still there
void NodeSokoMind::CreateNewBoard(NodeSokoMind* inputNode, NodeSokoMind* newNode, std::vector<char>::iterator Move, std::vector<char>::iterator BoxMove, int Distance) {
	//Box Move and Move are both on the newNodes sokomind board already
	if ((*BoxMove - 32) == *Move || (*BoxMove) == 'S' && *Move == 'X') { //since the box has to move onto lowercase letters we take 20 away
		if (*BoxMove == 'S' && *Move == 'X' && newNode->supplyPointX.size() != 0) {
			//std::cout << "\n\nX&S box break\n\n";
			auto distance = std::distance(newNode->sokoMind->begin(), BoxMove);
			for (auto it = newNode->supplyPointX.begin(); it < newNode->supplyPointX.end(); ++it) {
				if (*it == distance) {
					newNode->supplyPointX.erase(it); // erase the supply point from the distance chart
				}
				break;
			}
		}
		if ((*BoxMove - 32) == *Move) {
		//std::cout << "\n\nnamed box break\n\n";
		//newNode->PrintBoard(newNode);
		NodeSokoMind::BoxCleared(newNode, *BoxMove); //find which distance to set to -1 to signify that its cleared;
		//std::cout << "Box cleared\n";
		}
		*BoxMove = 32; //set it to empty space to remove both from board
	} else {
		*BoxMove = *Move; //update box visually on graph
	}
	newNode->robotIterator = Move; //set actual iterator to new posistion
	//NOTE YOU CANNOT PRINT AND SEE R UNTIL THIS IS SET AS THE PRIOR FUNCTION TECHINCALLY REMOVES R TEMP
	*newNode->robotIterator = 'R'; //visually update robots posistion
	newNode->distance = Distance;//update distance so when constructed next child has correct coordinates
	//std::cout << "\nparentbelow\n";
	//PrintBoard(inputNode);
	//std::cout << "\n";
	newNode->SupplyPointSpecialReset(newNode);
	NodeSokoMind::SupplyPointReset(newNode);
	/*std::cout << "\childbelow\n";
	PrintBoard(newNode);
	std::cout << "\n";*/
	inputNode->childVector.push_back(newNode);
	if (WinCheck(newNode)) {
		newNode->win = true;
		inputNode->win = true;
		return;
	}
}

int NodeSokoMind::BoxChecker(std::vector<char>::iterator Robot, int Direction) {
	for (int i = 0; i < checkArrSize; i++) {
		//bottom check
		if (Direction == 1) {
			if (*(Robot + width) == 32) {
				return 0;
			}
			if (*(Robot + width) == checkArr[i]) {//check to make sure there isnt another box in the direction of movement
				if (*(Robot + (width * 2)) != 'O' && *(Robot + (width * 2)) != 'A' && *(Robot + (width * 2)) != 'B' && *(Robot + (width * 2)) != 'C' && *(Robot + (width * 2)) != 'D' && *(Robot + (width * 2)) != 'X') { //cannot move legally right if theres a box
					return 1;
				} else {
					return -1;
				}
			}
			continue;
		}
		//top check
		if (Direction == 2) {
			if (*(Robot - width) == 32) {
				return 0;
			}
			if (*(Robot - width) == checkArr[i]) {//check to make sure there isnt another box in the direction of movement
				if (*(Robot - (width * 2)) != 'O' && *(Robot - (width * 2)) != 'A' && *(Robot - (width * 2)) != 'B' && *(Robot - (width * 2)) != 'C' && *(Robot - (width * 2)) != 'D' && *(Robot - (width * 2)) != 'X') { //cannot move legally right if theres a box
					return 2;
				} else {
					return -1;
				}
			}
			continue;
		}
		//left check
		if (Direction == 3) {
			if (*(Robot - 1) == 32) {
				return 0;
			}
			if (*(Robot - 1) == checkArr[i]) {//check to make sure there isnt another box in the direction of movement
				if (*(Robot - (2)) != 'O' && *(Robot - (2)) != 'A' && *(Robot - (2)) != 'B' && *(Robot - (2)) != 'C' && *(Robot - (2)) != 'D' && *(Robot - (2)) != 'X') { //cannot move legally right if theres a box
					return 3;
				} else {
					return -1;
				}
			}
			continue;
		}
		//right check
		if (Direction == 4) {
			if (*(Robot + 1) == 32) {
				return 0;
			}
			if (*(Robot + 1) == checkArr[i]) {//check to make sure there isnt another box in the direction of movement
				if (*(Robot + (2)) != 'O' && *(Robot + (2)) != 'A' && *(Robot + (2)) != 'B' && *(Robot + (2)) != 'C' && *(Robot + (2)) != 'D' && *(Robot + (2)) != 'X') { //cannot move legally right if theres a box
					return 4;
				} else {
					return -1;
				}
			}
			continue;
		}
	}
	return 0; //outside for loop no boxes found
}

void NodeSokoMind::SupplyPointReset(NodeSokoMind* inputNode) {
	if (inputNode->distancea != -1) {
		if (*inputNode->supplyPointa == 32) {
			*inputNode->supplyPointa = 'a';
		}
	}
	if (inputNode->distanceb != -1) {
		if (*inputNode->supplyPointb == 32) {
			*inputNode->supplyPointb = 'b';
		}
	}
	if (inputNode->distancec != -1) {
		if (*inputNode->supplyPointc == 32) {
			*inputNode->supplyPointc = 'c';
		}
	}
	if (inputNode->distanced != -1) {
		if (*inputNode->supplyPointd == 32) {
			*inputNode->supplyPointd = 'd';
		}
	}
}

void NodeSokoMind::PrintBoard() {
	int i = 0;
	for (auto it = sokoMind->begin(); it != sokoMind->end(); ++it) {
		if (i == width) {
			std::cout << "\n";
			i = 0;
		}
		std::cout << *it;
		i++;
	}
}

void NodeSokoMind::PrintBoard(NodeSokoMind* inputNode) {
	int i = 0;
	for (auto it = inputNode->sokoMind->begin(); it != inputNode->sokoMind->end(); ++it) {
		if (i == inputNode->width) {
			std::cout << "\n";
			i = 0;
		}
		std::cout << *it;
		i++;
	}
}

bool NodeSokoMind::WinCheck(NodeSokoMind* inputNode) {
	if (inputNode->distancea == -1 && inputNode->distanceb == -1 && inputNode->distancec == -1 && inputNode->distanced == -1 && inputNode->supplyPointX.size() == 0) {
		std::cout << "Win Check Passed" << std::endl;
		inputNode->win = true;
		std::cout << "\n\n========================= WINNERS BOARD ======================" << std::endl;
		PrintBoard(inputNode);
		std::cout << "\n\n========================= WINNERS BOARD ======================" << std::endl;
		return true;
	}
	return false;
}

void NodeSokoMind::BoxCleared(NodeSokoMind* inputNode, char supplypoint) {
	switch(supplypoint) {
		case 'a':
			inputNode->distancea = -1;
			*inputNode->supplyPointa = 32;
			break;
		case 'b':
			inputNode->distanceb = -1;
			*inputNode->supplyPointb = 32;
			break;
		case 'c':
			inputNode->distancec = -1;
			*inputNode->supplyPointc = 32;
			break;
		case 'd': 
			inputNode->distanced = -1;
			*inputNode->supplyPointd = 32;
			break;
	}
}

int NodeSokoMind::NodesExpanded(NodeSokoMind* inputNode) {
	count++;
	for (auto it = inputNode->childVector.begin(); it != inputNode->childVector.end(); ++it) {
		NodesExpanded(*it);
	}
	return count;
}

void NodeSokoMind::SupplyPointSetter(NodeSokoMind* parentNode) {
	if (parentNode->distancea != -1) {
		distancea = parentNode->distancea;
		supplyPointa = (sokoMind->begin() + distancea); //set the supply iterators no clue if this is faster than checking it vs distance
	}
	else {
		distancea = -1;//redudent?
	}
	if (parentNode->distanceb != -1) {
		distanceb = parentNode->distanceb;
		supplyPointb = (sokoMind->begin() + distanceb);
	}
	else {
		distanceb = -1;
	}
	if (parentNode->distancec != -1) {
		distancec = parentNode->distancec;
		supplyPointc = (sokoMind->begin() + distancec);
	}
	else {
		distancec = -1;
	}
	if (parentNode->distanced != -1) {
		distanced = parentNode->distanced;
		supplyPointd = (sokoMind->begin() + distanced);
	}
	else {
		distanced = -1;
	}
	if (supplyPointX.size() != 0) {
		for (auto it = sokoMind->begin(); it < sokoMind->end(); ++it) {
			for (int j = 0; j < parentNode->supplyPointX.size(); j++) {
				if (*it == 32) {
					it += parentNode->supplyPointX[j];
					*it = 'S';
					it -= parentNode->supplyPointX[j];
				}
			}
			break;
		}
	}
}

void NodeSokoMind::SupplyPointSpecialReset(NodeSokoMind* inputNode) {
	if (inputNode->supplyPointX.size() != 0) {
		for (auto it = inputNode->sokoMind->begin(); it < inputNode->sokoMind->end(); ++it) {
			for (int j = 0; j < inputNode->supplyPointX.size(); j++) {
				if (*it == 32) {
					it += inputNode->supplyPointX[j];
					*it = 'S';
					it -= inputNode->supplyPointX[j];
				}
			}
			break;
		}
	}
}

std::vector<NodeSokoMind*> NodeSokoMind::getChildVector() {
	return childVector;
}