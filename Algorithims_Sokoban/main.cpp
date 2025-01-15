#include "tree.h"
#include "DFS.h"
#include "BFS.h"
#include "ASTAR.h"
#include "KingsDopamine.h"

int main() {
	DFS DFSUTIL;
	BFS BFSUTIL;
	ASTAR ASTARUTIL;
	KINGSDOPAMINE KINGSDOPAMINEUTIL;

	//==============================================================MAP NAME INSIDE OF HERE=======================================================
	std::string mapName = "mapSmall3.txt";
	//==============================================================MAP NAME INSIDE OF HERE=======================================================

	Tree newTree = Tree(mapName);
	auto start = std::chrono::high_resolution_clock::now();
	//==============================================================UNCOMMENT THE ONE YOU WANT TO USE=======================================================

	//BFSUTIL.BFSCheckOverhaul(newTree.rootNode, newTree.width, newTree.height, newTree.sokoMind, newTree.finalNode, newTree.CompleteMapNode, start, mapName);
	DFSUTIL.DFSCheckOverhaul(newTree.rootNode, newTree.width, newTree.height, newTree.sokoMind, newTree.finalNode, newTree.CompleteMapNode, start, mapName);
	//ASTARUTIL.ASTAROVERHAUL(newTree.rootNode, newTree.width, newTree.height, newTree.sokoMind, newTree.finalNode, newTree.CompleteMapNode, start, mapName);
	//KINGSDOPAMINEUTIL.KingsDopamineOverhaul(newTree.rootNode, newTree.width, newTree.height, newTree.sokoMind, newTree.finalNode, newTree.CompleteMapNode, start, mapName);
	 
	//==============================================================UNCOMMENT THE ONE YOU WANT TO USE=======================================================
	
	
	
	//do not remove this deletes the nodes on your heap
	newTree.~Tree();
	return 0;
}