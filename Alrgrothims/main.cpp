#include "tree.h"
#include "DFS.h"
int main() {
	DFS DFSUTIL; //dont need to delete its on the stack

	//put your map name in here
	std::string mapName = "mapLarge1.txt";
	//put your map name in here

	Tree newTree = Tree(mapName);
	auto start = std::chrono::high_resolution_clock::now();
	DFSUTIL.DFSCheckOverhaul(newTree.rootNode, newTree.width, newTree.height, newTree.sokoMind, newTree.finalNode, newTree.CompleteMapNode, start, mapName);
	newTree.~Tree();

	return 0;
}