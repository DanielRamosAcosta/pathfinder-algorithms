#include <vector>
#include <iostream>
#include "agent.hpp"

#include "list.hpp"

/*
	breadth = 0,
	depth = 1,
	escalada = 2,
	primero_el_mejor = 3,
	coste_uniforme = 4,
	coste_uniforme_subestimacion = 5,
	coste_uniforme_dinamico = 6,
	a_estrella = 7

*/

int main(void){
	maze_t maze(40,40);
	agent_t robot(maze);
	std::cout << "Using strategy: hill_climbing" << std::endl;
	//unsigned seed = common::random();
	unsigned seed = 749982606;
	std::cout << "Using seed: " << seed << std::endl;
	maze.generate(seed);
	robot.solve(algorithm::hill_climbing);
	std::cout << maze << std::endl;
}
