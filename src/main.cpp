#include <vector>
#include <iostream>
#include "agent.hpp"

#include "list.hpp"

/*
anchura = 0,
	profundidad = 1,
	escalada = 2,
	primero_el_mejor = 3,
	coste_uniforme = 4,
	coste_uniforme_subestimacion = 5,
	coste_uniforme_dinamico = 6,
	a_estrella = 7

*/

int main(void){
	path_t mypath;
	mypath.push(point_t(1,1));
	mypath.push(point_t(2,1));
	mypath.push(point_t(4,2));
	path_t other_path = mypath;
	other_path.push(point_t(9,9));
	std::cout << mypath << std::endl;
	std::cout << other_path << std::endl;
	other_path.push(point_t(9,9));
	std::cout << mypath << std::endl;
	std::cout << other_path << std::endl << std::endl;

	list_t lista;
	lista.push_back(mypath);
	lista.push_back(other_path);
	std::cout << lista << std::endl;
	path_t hola = lista.pop_back();
	std::cout << lista << std::endl;

	std::cout << "El sobrante es " << hola << std::endl;
}
