#pragma once

#include <deque>
#include <cmath>
#include <algorithm>

#include "maze.hpp"
#include "point.hpp"


enum algorithm{
	anchura = 0,
	profundidad = 1,
	escalada = 2,
	primero_el_mejor = 3
};

typedef std::deque<point_t> trayectoria_t;

class agent_t
{
private:
	maze_t* maze_;
	point_t start_;
	point_t end_;
public:
	agent_t(maze_t* maze);
	void solve(unsigned mode);

	//Busquedas sin informacion
	void anchura(void);
	void anadir_descendientes_al_final(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria);

	void profundidad(void);
	void anadir_descendientes_al_principio(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria);

	//Búsquedas usando una función heurística (por proximidad al objetivo)
	long double h(point_t origen);
	void sort(std::deque<trayectoria_t>& trayectorias);
	void imprime(std::deque<trayectoria_t> lista_trayectorias);

	void escalada(void);
	void anadir_descendientes_al_principio_ordenados(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria);

	void primero_el_mejor(void);
	void anadir_descendientes_y_ordenar(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria);
};