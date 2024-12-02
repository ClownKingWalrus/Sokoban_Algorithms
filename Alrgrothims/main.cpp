#include "tree.h"
#include "DFS.h"
int main() {
	//newTree.rootNode->PrintBoard(newTree.rootNode, newTree.sokoMind, newTree.width, newTree.height, newTree.finalNode);
	DFS DFSUTIL; //dont need to delete its on the stack
	Tree newTree = Tree("map7.txt");//todo test all directions to ensure robot has quad directional movement
	auto start = std::chrono::high_resolution_clock::now();
	DFSUTIL.DFSCheckOverhaul(newTree.rootNode, newTree.width, newTree.height, newTree.sokoMind, newTree.finalNode, newTree.CompleteMapNode, start);
	newTree.~Tree();

	return 0;
}