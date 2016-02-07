#include <vector>
#include <iostream>
#include "agent.hpp"

#include "list.hpp"

/*
	breadth = 0,
	depth = 1,
	hill_climbing = 2,
	bfs = 3,
	ucs = 4,
	coste_uniforme_subestimacion = 5,
	coste_uniforme_dinamico = 6,
	a_estrella = 7

*/

int main(void){
	maze_t maze(40,40);
	agent_t robot(maze);
	std::cout << "Using strategy: breadth" << std::endl;
	unsigned seed = common::random();
	//unsigned seed = 742982606;
	std::cout << "Using seed: " << seed << std::endl;
	maze.generate(seed);
	robot.solve(algorithm::breadth);
	std::cout << maze << std::endl;
}
