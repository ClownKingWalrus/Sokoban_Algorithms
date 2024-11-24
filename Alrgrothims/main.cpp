#include "tree.h"
#include "nodeSokoMind.h"
#include "DFS.h"
#include <chrono>
int main() {
	DFS DFSUTIL; //dont need to delete its on the stack
	NodeSokoMind* test = new NodeSokoMind(); //needs to delete its a pointer
	test->ReadPuzzelFirstTime("sokomindtest.txt"); // a place holder for trees root
	Tree newTree = Tree(test);
	auto start = std::chrono::high_resolution_clock::now();
	DFSUTIL.DFSCheck(newTree.rootNode);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	//winner message
	if (DFSUTIL.completed) {
		std::cout << "\n\nWINNER Nodes Exanded" << std::endl;
		std::cout << test->NodesExpanded(newTree.rootNode) << std::endl;
		std::cout << "Time Spent milliseconds: " << float(duration.count() / 1000) <<std::endl;
	}
	else {
		std::cout << "\n\nno possible solutions after: " << std::endl;
		std::cout << test->NodesExpanded(newTree.rootNode) << std::endl;
		std::cout << "Time Spent milliseconds: " << float(duration.count() / 1000) << std::endl;
	}
	newTree.~Tree();

	return 0;
}