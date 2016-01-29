#include <vector>
#include <iostream>
#include "agent.hpp"

#include "list.hpp"

/*
	breadth = 0,
	profundidad = 1,
	escalada = 2,
	primero_el_mejor = 3,
	coste_uniforme = 4,
	coste_uniforme_subestimacion = 5,
	coste_uniforme_dinamico = 6,
	a_estrella = 7

*/

int main(void){
	maze_t* maze = new maze_t(20,20);
	agent_t robot(maze);
	std::cout << "Siguiendo la estrategia: depth" << std::endl;
	maze->generate(4);
	robot.solve(algorithm::depth);
	maze->print(std::cout);
}
