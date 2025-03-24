===You Must Download As Formatting Is Messed Up===

To use this program there is a few things to know

First to actually make your map you must use this format 
Rules 1: O's not 0 are your walls
Rule 2: Your Walls must form a a closed Box
Rule 3: Boxes are Captial Letters so A-Z exluding X and S (You can only have one letter each so (A a), (B b) and so on but NOT ((A a)(A a)) on a single map) this breaks the mapper
Rule 4: Supply points are lowercase letters so a-z exluding X and S
Rule 5: Have a supply Point For each box for intance you can see below captial A and captial B have a lower case a and b for them to go to
Rule 6: X are Boxes but are nondescript so they can go into any S supply point so there can be multiple of these just make sure to have a S to every X
Rule 7: your Maps must start in the txt file with no spaces
Rule 8: store your maps inside of Algorithims_Sokoban\Algorithims_Sokoban directory or the same level as main.cpp 

HOW TO ACTUALLY RUN THESE ALGORITHIM
inside of main.cpp you will only need to change 2 lines
	//==============================================================MAP NAME INSIDE OF HERE=======================================================
	std::string mapName = "mapSmallTest.txt";
	//==============================================================MAP NAME INSIDE OF HERE=======================================================
 std::string mapName = "yourmapName.txt" <=== just add your files name
 
 the second lines:
 	//==============================================================UNCOMMENT THE ONE YOU WANT TO USE=======================================================
	//BFSUTIL.BFSCheckOverhaul(newTree.rootNode, newTree.width, newTree.height, newTree.sokoMind, newTree.finalNode, newTree.CompleteMapNode, start, mapName);
	//DFSUTIL.DFSCheckOverhaul(newTree.rootNode, newTree.width, newTree.height, newTree.sokoMind, newTree.finalNode, newTree.CompleteMapNode, start, mapName);
	ASTARUTIL.ASTAROVERHAUL(newTree.rootNode, newTree.width, newTree.height, newTree.sokoMind, newTree.finalNode, newTree.CompleteMapNode, start, mapName);
	//KINGSDOPAMINEUTIL.KingsDopamineOverhaul(newTree.rootNode, newTree.width, newTree.height, newTree.sokoMind, newTree.finalNode, newTree.CompleteMapNode, start, mapName);
	//==============================================================UNCOMMENT THE ONE YOU WANT TO USE=======================================================
 
just remove the // on which algorithim you want to use for example you can see ASTARUTIL does not have the // just BE SURE to only have one uncommented at a time
I hope you enjoy your time with these algorithms as this only uses embedded libraries there is no work around or sus libraries enjoy :)

notes:
this program will free up afterwords since its both in microsft visual studios and because i free the memory up after
this program can heap crash your computer the second example map with AStar running cost 15Gigabytes of space on my ram just to solve
The fastest algorothim avaible is Kings Dopamine(my custom algorithim(a deviation off Astar, which is a deviation off of Dijkstra's)) the second map took AStar 8 minutes while it took KingsDopamine 1.~ seconds for my computer
Your processor Will heavily affect how long it actually takes to solve my single thread speed is ~5.17 GHZ so expect your speeds to be slower than mine

Example Maps:

OOOOOOOO
O  R   O
O  A  XO
O  B  bO
O      O
O      O
Oa    SO
OOOOOOOO

Example Maps:

OOOOOOO
Oa   bO
O AXB O
O XRX O
OSCXDSO
OcS SdO
OOOOOOO

Example Maps:

OOOOOOOOOO
OOOOOOOSSO
OOOOO  abO
OOOOO XSSO
OOOOOO  OO
OR     OOO
OO A X X O
OO BXO O O
OO   O   O
OOOOOOOOOO

Example Maps:
