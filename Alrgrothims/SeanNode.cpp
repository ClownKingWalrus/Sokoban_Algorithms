#include "SeanNode.h"
SeanNode::SeanNode() {
	parent = 0;
}

SeanNode::SeanNode(SeanNode* inputNode) {
	parent = inputNode;
	xBoxes = inputNode->xBoxes;
	specialBoxes = inputNode->specialBoxes;
	robot = inputNode->robot;
}

SeanNode::~SeanNode() {
	xBoxes.clear();
	specialBoxes.clear();
}

//this reads the puzzel and should return the data or set the nodes data
SeanNode::customReturn SeanNode::ReadPuzzelFirstTime(std::string inputString) {
	std::ifstream filedata(inputString); // create a way to access the file
	std::string oneline;
	std::vector<bool> sokoMind; //will change to array once i figure it out
	std::unordered_map<char, std::pair<int, int>> boxMap; //leave here its just for cross comparing
	std::unordered_map<char, std::pair<int, int>> supplyMap;
	std::vector<std::pair<int, int>> standerdSupplyPoints;
	//int i = 0;
	int height = 0;
	int x = 0;
	int y = 0;
	while (getline(filedata, oneline)) {
		height++;//returns correct height
		for (int i = 0; i < oneline.size(); i++) {
			if (oneline[i] == 'O') {
				sokoMind.push_back(false);
			}
			else {
				sokoMind.push_back(true);
			}

			if (x >= oneline.size()) {
				y++;
				x = 0;
			};

			if (oneline[i] == 'R') {
				robot = { x, y };
			}
			//save Special Boxes in map
			if (oneline[i] >= 'A' && oneline[i] <= 'Z' && oneline[i] != 'X' && oneline[i] != 'S' && oneline[i] != 'O' && oneline[i] != 'R') {
				boxMap[oneline[i]] = { x,y };
			}

			//save supply point specials in map
			if (oneline[i] >= 'a' && oneline[i] <= 'z') {
				supplyMap[oneline[i]] = { x,y };
			}

			if (oneline[i] == 'S') {
				standerdSupplyPoints.push_back({ x,y });
			}

			if (oneline[i] == 'X') {
				//boxMap['X'] = { x,y };
				xBoxes.push_back({ x, y }); //push each point into here
			}
			x++;
		}
	}
	int width = oneline.size();
	filedata.close(); //close the file
	for (auto pair : boxMap) {
		for (auto pair2 : supplyMap) {
			if (pair.first == (pair2.first - 32)) { //check to see if same letter
				
			}
		}
	}
	SeanNode::customReturn Temp;
		Temp.height = height;
		Temp.width = width;
		Temp.sokoMind = sokoMind;
		Temp.boxMap = boxMap;
		Temp.supplyMap = supplyMap;
		Temp.standerdSupplyPoints = standerdSupplyPoints;
		return Temp;
}

SeanNode::legalReturn SeanNode::LegalMoveChecks(SeanNode* inputNode, int height, int width, std::vector<bool> sokoMind, SeanNode FinalNode) {
	int nodeAmount = 0;
	//since we know the height and width we can add +/- width to see top and bottom row checks
	//make a check with the parent iterator posistion so we do not create a extra move back in the same place
	int robotpos = inputNode->robot.first + (inputNode->robot.second * width); //width can never be zero because how the map is made
	legalReturn nodeReturner;
	bool bot = false;
	bool top = false;
	bool left = false;
	bool right = false;
	//std::cout << "\n\n================== PARENT =====================\n";
	//inputNode->PrintBoard(inputNode, sokoMind, width, height, FinalNode);
	//std::cout << "\n================== PARENT =====================\n";
	if (sokoMind.at((robotpos + width)) == true) {
		bot = true;
	}
	if (sokoMind.at((robotpos - width)) == true) {
		top = true;
	}
	if (sokoMind.at((robotpos + 1)) == true) {
		right = true;
	}
	if (sokoMind.at((robotpos - 1)) == true) {
		left = true;
	}
	if (!inputNode->specialBoxes.empty()) {  // set named boxes
			for (auto it = inputNode->specialBoxes.begin(); it != inputNode->specialBoxes.end(); ++it) {
				sokoMind.at((it->first + (it->second * width))) = false;
			}
		}
	if (!inputNode->xBoxes.empty()) { // set unamed boxes
		for (auto it = inputNode->xBoxes.begin(); it != inputNode->xBoxes.end(); ++it) {
			sokoMind.at((it->first + (it->second * width))) = false;
		}
	}

	//bottom check
	if (bot) {//if going in we know there is no wall down
		switch ((inputNode->BoxChecker(robotpos, 1, width, height, sokoMind))) {
		case 1: { //down legal move with box
			SeanNode* newNode = new SeanNode(inputNode);
			inputNode->CreateNewBoard(inputNode, newNode, 1, 1, height, width, FinalNode);
			std::vector<char> compareArr = CreateCharSokoMind(newNode, sokoMind, width, height, FinalNode);
			nodeReturner.nodeVector.push_back({ newNode, compareArr });
			if (newNode->win) {
				return nodeReturner;
			}
			nodeAmount++;
			//std::cout << "\n\n================== CHILD BOTTOM BOX =====================\n";
			//inputNode->PrintBoard(newNode, sokoMind, width, height, FinalNode);
			//std::cout << "\n================== CHILD BOTTOM BOX =====================\n";
			break;
		}
		case 0: {//bottom legal move no box
			//create a new node here so we can ajust its sokoMind board and not the prior one
			SeanNode* newNode = new SeanNode(inputNode);
			inputNode->CreateNewBoard(inputNode, newNode, 1, 0, height, width, FinalNode);
			std::vector<char> compareArr = CreateCharSokoMind(newNode, sokoMind, width, height, FinalNode);
			nodeReturner.nodeVector.push_back({ newNode, compareArr });
			nodeAmount++;
			//std::cout << "\n\n================== CHILD BOTTOM =====================\n";
			//inputNode->PrintBoard(newNode, sokoMind, width, height, FinalNode);
			//std::cout << "\n================== CHILD BOTTOM =====================\n";
			break;
		}
		case -1: //another box is in direction of push
			break;
		default:
			break;
		}
	}

	//top check
	if (top) {//if going in we know there is no wall above
		switch ((inputNode->BoxChecker(robotpos, 2, width, height, sokoMind))) {
		case 2: { //Top legal move with box
			SeanNode* newNode = new SeanNode(inputNode);
			inputNode->CreateNewBoard(inputNode, newNode, 2, 1, height, width, FinalNode);
			std::vector<char> compareArr = CreateCharSokoMind(newNode, sokoMind, width, height, FinalNode);
			if (newNode->win) {
				nodeReturner.nodeVector.clear();
				nodeReturner.nodeVector.push_back({ newNode, compareArr });
				return nodeReturner;
			}
			nodeReturner.nodeVector.push_back({ newNode, compareArr });
			nodeAmount++;
			//std::cout << "\n\n================== CHILD TOP BOX =====================\n";
			//inputNode->PrintBoard(newNode, sokoMind, width, height, FinalNode);
			//std::cout << "\n================== CHILD TOP BOX =====================\n";
			break;
		}
		case 0: {//top legal move no box
			//create a new node here so we can ajust its sokoMind board and not the prior one
			SeanNode* newNode = new SeanNode(inputNode);
			inputNode->CreateNewBoard(inputNode, newNode, 2, 0, height, width, FinalNode);
			std::vector<char> compareArr = CreateCharSokoMind(newNode, sokoMind, width, height, FinalNode);
			nodeReturner.nodeVector.push_back({ newNode, compareArr });
			nodeAmount++;
			//std::cout << "\n\n================== CHILD TOP =====================\n";
			//inputNode->PrintBoard(newNode, sokoMind, width, height, FinalNode);
			//std::cout << "\n================== CHILD TOP =====================\n";
			break;
		}
		case -1: //another box is in direction of push
			break;
		default:
			break;
		}
	}

	//left check
	if (left) {//make sure we dont go out of bounds on the left hand wall
		switch ((inputNode->BoxChecker(robotpos, 3, width, height, sokoMind))) {
		case 3: { //down legal move with box
			SeanNode* newNode = new SeanNode(inputNode);
			inputNode->CreateNewBoard(inputNode, newNode, 3, 1, height, width, FinalNode);
			std::vector<char> compareArr = CreateCharSokoMind(newNode, sokoMind, width, height, FinalNode);
			if (newNode->win) {
				nodeReturner.nodeVector.clear();
				nodeReturner.nodeVector.push_back({ newNode, compareArr });
				return nodeReturner;
			}
			nodeReturner.nodeVector.push_back({ newNode, compareArr });
			nodeAmount++;
			//std::cout << "\n\n================== CHILD LEFT BOX =====================\n";
			//inputNode->PrintBoard(newNode, sokoMind, width, height, FinalNode);
			//std::cout << "\n================== CHILD LEFT BOX =====================\n";
			break;
		}
		case 0: {//left legal move no box
			//create a new node here so we can ajust its sokoMind board and not the prior one
			SeanNode* newNode = new SeanNode(inputNode);
			inputNode->CreateNewBoard(inputNode, newNode, 3, 0, height, width, FinalNode);
			std::vector<char> compareArr = CreateCharSokoMind(newNode, sokoMind, width, height, FinalNode);
			nodeReturner.nodeVector.push_back({ newNode, compareArr });
			nodeAmount++;
			//std::cout << "\n\n================== CHILD LEFT =====================\n";
			//inputNode->PrintBoard(newNode, sokoMind, width, height, FinalNode);
			//std::cout << "\n================== CHILD LEFT =====================\n";
			break;
		}
		case -1: //another box is in direction of push
			break;
		default:
			break;
		}
	}

	//right check
	if (right) {//if going in we know there is no wall right
		switch ((inputNode->BoxChecker(robotpos, 4, width, height, sokoMind))) {
		case 4: { //down legal move with box
			SeanNode* newNode = new SeanNode(inputNode);
			inputNode->CreateNewBoard(inputNode, newNode, 4, 1, height, width, FinalNode);
			std::vector<char> compareArr = CreateCharSokoMind(newNode, sokoMind, width, height, FinalNode);
			if (newNode->win) {
				nodeReturner.nodeVector.clear();
				nodeReturner.nodeVector.push_back({ newNode, compareArr });
				return nodeReturner;
			}
			nodeReturner.nodeVector.push_back({ newNode, compareArr });
			nodeAmount++;
			//std::cout << "\n\n================== CHILD RIGHT BOX =====================\n";
			//inputNode->PrintBoard(newNode, sokoMind, width, height, FinalNode);
			//std::cout << "\nn================== CHILD RIGHT BOX =====================\n";
			break;
		}
		case 0: {//right legal move no box
			//create a new node here so we can ajust its sokoMind board and not the prior one
			SeanNode* newNode = new SeanNode(inputNode);
			inputNode->CreateNewBoard(inputNode, newNode, 4, 0, height, width, FinalNode);
			std::vector<char> compareArr = CreateCharSokoMind(newNode, sokoMind, width, height, FinalNode);
			nodeReturner.nodeVector.push_back({ newNode, compareArr });
			nodeAmount++;
			//std::cout << "\n\n================== CHILD RIGHT =====================\n";
			//inputNode->PrintBoard(newNode, sokoMind, width, height, FinalNode);
			//std::cout << "\nn================== CHILD RIGHT =====================\n";
			break;
		}
		case -1: //another box is in direction of push
			break;
		default:
			break;
		}
	}
	//std::cout << "\nExpected Nodes is: " << nodeAmount << std::endl;
	return nodeReturner;
}

void SeanNode::CreateNewBoard(SeanNode* inputNode, SeanNode* newNode, int direction, int box, int height, int width, SeanNode FinalNode) {
	//box move and move are both on the newnodes sokoMind board already
	std::pair<int, int> boxLocation = {0,0};
	std::pair<int, int> newBoxLocation = {0,0};
	switch (box)
	{
		case 1: //box
			switch (direction) { // a new node is created for each case statement
				case 1://down
					boxLocation = { newNode->robot.first, (newNode->robot.second + 1) };
					newBoxLocation = { newNode->robot.first, (newNode->robot.second + 2) };
					SeanNode::BoxCleared(newNode, boxLocation, newBoxLocation, FinalNode);
					break;
				case 2://up
					boxLocation = { newNode->robot.first, (newNode->robot.second - 1) };
					newBoxLocation = { newNode->robot.first, (newNode->robot.second - 2) };
					SeanNode::BoxCleared(newNode, boxLocation, newBoxLocation, FinalNode);
					break;
				case 3://left
					boxLocation = { newNode->robot.first - 1, newNode->robot.second };
					newBoxLocation = { (newNode->robot.first - 2), newNode->robot.second };
					SeanNode::BoxCleared(newNode, boxLocation, newBoxLocation, FinalNode);
					break;
				case 4://right
					boxLocation = { newNode->robot.first + 1, newNode->robot.second };
					newBoxLocation = { newNode->robot.first + 2, newNode->robot.second };
					SeanNode::BoxCleared(newNode, boxLocation, newBoxLocation, FinalNode);
					break;
				default:
					break;
			}

		case 0://no box
			switch (direction) {
				case 1://down
					newNode->robot.second = (newNode->robot.second + 1);
					break;
				case 2://up
					newNode->robot.second = (newNode->robot.second - 1);
					break;
				case 3://left
					newNode->robot.first = (newNode->robot.first - 1);
					break;
				case 4://right
					newNode->robot.first = (newNode->robot.first + 1);
					break;
				default:
					break;
		}
	}
	return; //if switch fails to return
}

int SeanNode::BoxChecker(int robotpos, int Direction, int width, int height, std::vector<bool> sokoMind) {
	//int count = 0;
	//int count2 = 0;
//for (int i = 0; i < sokoMind.size(); i++) {
//	if (count >= width) {
//	std::cout << '\n';
//	count = 0;
//	}
//	if (count2 == (robotpos + width)) {
//	std::cout << "R";
//	} else {
//	std::cout << sokoMind[i];
//	}
//	count++;
//	count2++;
//}
	//bottom check
	switch (Direction) {
	case 1:
		if (sokoMind.at(robotpos + width) == true) { //no box just walk
			return 0;
		}
		if (sokoMind.at(robotpos + width) == false) {//false == box directly down
			if (sokoMind.at(robotpos + (width * 2)) == true) { //true == no box below the box in prior if statement
				return 1;
			}
			else {
				return -1;
			}
		}
		break;
	case 2:
		if (sokoMind.at(robotpos - width) == true) {
			return 0;
		}
		if (sokoMind.at(robotpos - width) == false) {//false == box directly Above
			if (sokoMind.at(robotpos - (width * 2)) == true) { //true == no box Above the box in prior if statement
				return 2;
			}
			else {
				return -1;
			}
		}
		break;
	case 3:
		if (sokoMind.at(robotpos - 1) == true) {
			return 0;
		}
		if (sokoMind.at(robotpos - 1) == false) {//false == box directly Left
			if (sokoMind.at(robotpos - 2) == true) { //true == no box Left the box in prior if statement
				return 3;
			}
			else {
				return -1;
			}
		}
		break;
	case 4:
		if (sokoMind.at(robotpos + 1) == true) {
			return 0;
		}
		if (sokoMind.at(robotpos + 1) == false) {//false == box directly Right
			if (sokoMind.at(robotpos + 2) == true) { //true == no box Right the box in prior if statement
				return 4;
			}
			else {
				return -1;//box in way
			}
		}
		break;
	}
	return 0; //no boxes found? shouldent get to here ever
}

void SeanNode::PrintBoard(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode) {
	std::vector<char> sokoMindBoard;
	int Checker = 0;
	for (auto it = sokoMind.begin(); it != sokoMind.end(); ++it) {
		if (!*it) {
			sokoMindBoard.push_back('O');//wall
		}
		else {
			sokoMindBoard.push_back(32);//space
		}
	} 

	if (!FinalNode.xBoxes.empty()) {//set set unnamed supply points points
		for (auto it = FinalNode.xBoxes.begin(); it < FinalNode.xBoxes.end(); ++it) {
			sokoMindBoard.at(it->first + (it->second * width)) = 'S';
		}
	}
	//set X boxes

	if (!inputNode->xBoxes.empty()) {//set set unnamed supply points points
		for (auto it = inputNode->xBoxes.begin(); it < inputNode->xBoxes.end(); ++it) {
			sokoMindBoard.at(it->first + (it->second * width)) = 'X';
		}
	}
	if (!inputNode->xBoxes.empty() && !FinalNode.xBoxes.empty()) {
		for (auto it = inputNode->xBoxes.begin(); it < inputNode->xBoxes.end(); ++it) {
			for (auto itFinal = FinalNode.xBoxes.begin(); itFinal < FinalNode.xBoxes.end(); ++itFinal) {
				if (*it == *itFinal) {
					sokoMindBoard.at(it->first + (it->second * width)) = 'Z';
				}
			}
		}

	}
	//set named boxes down
	if (!inputNode->specialBoxes.empty()) {
		int count = 'A';
		for (auto it = inputNode->specialBoxes.begin(); it != inputNode->specialBoxes.end(); ++it) {
			if (it->second != Checker) { //print all pairs that are not zero zero
				sokoMindBoard.at(((it->second * width) + it->first)) = char(count);//set to correct character
			}
			count++;//start at a and count up once we place or deemed already got
		}
	}
	//set named supply points down
	if (!FinalNode.specialBoxes.empty()) {
		int count = 'a';
		for (auto it = FinalNode.specialBoxes.begin(); it != FinalNode.specialBoxes.end(); ++it) {
			if (it->second != Checker) {
				sokoMindBoard.at(((it->second * width) + it->first)) = char(count);//set to correct character
			}
			count++;//start at a and count up once we place or deemed already got
		}
	}
	// set robot
	sokoMindBoard[((inputNode->robot.second * width) + inputNode->robot.first)] = 'R';
	//actually start printing the board below
	int i = 0;
	for (auto it = sokoMindBoard.begin(); it != sokoMindBoard.end(); ++it) {
		if (i == width) {
			std::cout << "\n";
			i = 0;
		}
		std::cout << *it;
		i++;
	}
}

std::vector<char> SeanNode::CreateCharSokoMind(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode) {
	std::vector<char> sokoMindBoard;
	std::pair<int, int> x = { 0,0 };
	for (auto it = sokoMind.begin(); it != sokoMind.end(); ++it) {
		if (!*it) {
			sokoMindBoard.push_back('O');//wall
		}
		else {
			sokoMindBoard.push_back(32);//space
		}
	} // set robot

	if (!FinalNode.xBoxes.empty()) {//set set unnamed supply points points
		for (auto it = FinalNode.xBoxes.begin(); it < FinalNode.xBoxes.end(); ++it) {
			sokoMindBoard.at(it->first + (it->second * width)) = 'S';
		}
	}
	//set named supply points down
	if (!FinalNode.specialBoxes.empty()) {
		int count = 'a';
		for (auto it = FinalNode.specialBoxes.begin(); it != FinalNode.specialBoxes.end(); ++it) {
			if (*it != x) {
				sokoMindBoard.at(((it->second * width) + it->first)) = char(count);//set to correct character
			}
			count++;//start at a and count up once we place or deemed already got
		}
	}
	//set named boxes down
	if (!inputNode->specialBoxes.empty()) {
		int count = 'A';
		for (auto it = inputNode->specialBoxes.begin(); it != inputNode->specialBoxes.end(); ++it) {
			if (*it != x) { //print all pairs that are not zero zero
				sokoMindBoard.at(((it->second * width) + it->first)) = char(count);//set to correct character
			}
			count++;//start at a and count up once we place or deemed already got
		}
	}

	//set X boxes
	if (!inputNode->xBoxes.empty()) {//set set unnamed supply points points
		for (auto it = inputNode->xBoxes.begin(); it < inputNode->xBoxes.end(); ++it) {
			sokoMindBoard.at(it->first + (it->second * width)) = 'X';
		}
	}
	if (!inputNode->xBoxes.empty() && !FinalNode.xBoxes.empty()) {
		for (auto it = inputNode->xBoxes.begin(); it < inputNode->xBoxes.end(); ++it) {
			for (auto itFinal = FinalNode.xBoxes.begin(); itFinal < FinalNode.xBoxes.end(); ++itFinal) {
				if (*it == *itFinal) {
					sokoMindBoard.at(it->first + (it->second * width)) = 'Z';
				}
			}
		}

	}
	sokoMindBoard[((inputNode->robot.second * width) + inputNode->robot.first)] = 'R';//place last so supply points dont overtake
	return sokoMindBoard;
}

std::string SeanNode::CreateStringSokoMind(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode) {
	std::vector<char> sokoMindBoard;
	std::pair<int, int> x = { 0,0 };
	for (auto it = sokoMind.begin(); it != sokoMind.end(); ++it) {
		if (!*it) {
			sokoMindBoard.push_back('O');//wall
		}
		else {
			sokoMindBoard.push_back(32);//space
		}
	} // set robot

	if (!FinalNode.xBoxes.empty()) {//set set unnamed supply points points
		for (auto it = FinalNode.xBoxes.begin(); it < FinalNode.xBoxes.end(); ++it) {
			sokoMindBoard.at(it->first + (it->second * width)) = 'S';
		}
	}
	//set named supply points down
	if (!FinalNode.specialBoxes.empty()) {
		int count = 'a';
		for (auto it = FinalNode.specialBoxes.begin(); it != FinalNode.specialBoxes.end(); ++it) {
			if (*it != x) {
				sokoMindBoard.at(((it->second * width) + it->first)) = char(count);//set to correct character
			}
			count++;//start at a and count up once we place or deemed already got
		}
	}
	//set named boxes down
	if (!inputNode->specialBoxes.empty()) {
		int count = 'A';
		for (auto it = inputNode->specialBoxes.begin(); it != inputNode->specialBoxes.end(); ++it) {
			if (*it != x) { //print all pairs that are not zero zero
				sokoMindBoard.at(((it->second * width) + it->first)) = char(count);//set to correct character
			}
			count++;//start at a and count up once we place or deemed already got
		}
	}
	
	//set X boxes
	if (!inputNode->xBoxes.empty()) {//set set unnamed supply points points
		for (auto it = inputNode->xBoxes.begin(); it < inputNode->xBoxes.end(); ++it) {
			sokoMindBoard.at(it->first + (it->second * width)) = 'X';
		}
	}
	if (!inputNode->xBoxes.empty() && !FinalNode.xBoxes.empty()) {
		for (auto it = inputNode->xBoxes.begin(); it < inputNode->xBoxes.end(); ++it) {
			for (auto itFinal = FinalNode.xBoxes.begin(); itFinal < FinalNode.xBoxes.end(); ++itFinal) {
				if (*it == *itFinal) {
					sokoMindBoard.at(it->first + (it->second * width)) = 'Z';
				}
			}
		}

	}
	sokoMindBoard[((inputNode->robot.second * width) + inputNode->robot.first)] = 'R';//place last so supply points dont overtake
	std::string temp;
	int i = 0;
	for (auto it = sokoMindBoard.begin(); it != sokoMindBoard.end(); ++it) {
		if (i == width) {
			temp.push_back('\n');
			i = 0;
		}
		temp.push_back(*it);
		i++;
	}
	return temp;
}

void SeanNode::PrintWinnerBoard(SeanNode* inputNode, std::vector<bool> sokoMind, int width, int height, SeanNode FinalNode) {
	std::cout << "\n\n========================= winners board ======================" << std::endl;
	PrintBoard(inputNode, sokoMind, width, height, FinalNode);
	std::cout << "\n\n========================= winners board ======================" << std::endl;
}

void SeanNode::BoxCleared(SeanNode* inputNode, std::pair<int, int> boxLocation, std::pair<int, int> newBoxLocation, SeanNode FinalNode) {
	for (auto it = inputNode->specialBoxes.begin(); it != inputNode->specialBoxes.end(); ++it) {
		if (*it == boxLocation) {
			*it = newBoxLocation; //set box location to new area
			for (auto it2 = FinalNode.specialBoxes.begin(); it2 != FinalNode.specialBoxes.end(); ++it2) {
				if (*it == *it2) { //if there is a S for the X box to drop off
					//*it = { 0,0 }; //for now set to 0,0 so we keep proper indexing
					//*it2 = { 0,0 };
					if (WinCheck(inputNode, FinalNode)) {
						inputNode->win = true;
					}
					return; //return out if we win or once we erase
				}
			}
		}
	}

	for (auto it = inputNode->xBoxes.begin(); it != inputNode->xBoxes.end(); ++it) {
		if (*it == boxLocation) {
			*it = newBoxLocation;//set box location to new area
			for (auto it2 = FinalNode.xBoxes.begin(); it2 != FinalNode.xBoxes.end(); ++it2) {
				if (*it == *it2) { //if there is a S for the X box to drop off
					//*it = { 0,0 }; //for now set to 0,0 so we keep proper indexing
					//*it2 = { 0,0 };
					if (WinCheck(inputNode, FinalNode)) {
						inputNode->win = true;
					}
					return; //return out if we win or once we erase
				}
			}
		}
	}
}

bool SeanNode::WinCheck(SeanNode* InputNode, SeanNode FinalNode) {
	//if all == checker then we cleared all boxes
	for (auto itFinal = FinalNode.specialBoxes.begin(); itFinal < FinalNode.specialBoxes.end(); ++itFinal) {
		for (auto it = InputNode->specialBoxes.begin(); it < InputNode->specialBoxes.end(); ++it) {
			if (*it == *itFinal) {
				break;
			}
			else if (it == (InputNode->specialBoxes.end() - 1)) {
				return false;
			}
		}
	}
	for (auto itFinal = FinalNode.xBoxes.begin(); itFinal < FinalNode.xBoxes.end(); ++itFinal) {
		for (auto it = InputNode->xBoxes.begin(); it < InputNode->xBoxes.end(); ++it) {
			if (*it == *itFinal) {
				break;
			}
			else if (it == (InputNode->xBoxes.end() - 1)) {
				return false;
			}
		}
	}
	return true; //if it gets to here that means all are matches and we can return win condidtion
}

void SeanNode::InfoSheet(SeanNode* InputNode, int height, int width, std::vector<bool> sokoMind, SeanNode CompleteMapNode, std::chrono::time_point<std::chrono::high_resolution_clock> startTime, int NodesExpanded) {
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - startTime);
	std::cout << "MAKING SHEET INSERT NAME FOR SHEET - note will be in folder -" << std::endl;
	std::string fileName;
	std::getline(std::cin, fileName);
	fileName += ".txt";
	std::ofstream infoSheet(fileName); //create and open file
	int count = 1;
	while (infoSheet.is_open()) {
		if (InputNode->parent != 0) {
			std::string temp = InputNode->CreateStringSokoMind(InputNode, sokoMind, width, height, CompleteMapNode);
			infoSheet << '\n' << "Step: " << count << '\n';
			infoSheet << temp << "\n\n";
			InputNode = InputNode->parent;
			count++;
		}
		else {
			std::string temp = InputNode->CreateStringSokoMind(InputNode, sokoMind, width, height, CompleteMapNode);
			infoSheet << '\n' << "Step: " << count << '\n';;
			infoSheet << temp << "\n\n";
			infoSheet << "\n\n" << "Total Steps to Destination: " << count;
			auto duration_Seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
			int timerSeconds = duration_Seconds.count();
			infoSheet << "\n\n" << "Total Time in seconds: " << timerSeconds << '\n';
			infoSheet << "\n\n" << "Nodes Expanded: " << NodesExpanded << '\n';
			infoSheet.close();

		}
	}
	return;
}