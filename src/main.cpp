#include <vector>
#include <iostream>
#include "agent.hpp"

int main(void){
	maze_t* maze = new maze_t(20,20);
	maze->generate(4);
	agent_t robot(maze);
	robot.solve(algorithm::escalada);
	maze->print(std::cout);
}