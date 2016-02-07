#pragma once

#include <deque>
#include <cmath>
#include <algorithm>

#include "maze.hpp"
#include "point.hpp"
#include "list.hpp"

enum algorithm{
	breadth = 0,
	depth = 1,
	hill_climbing = 2,
	bfs = 3,
	ucs = 4,
	coste_uniforme_subestimacion = 5,
	coste_uniforme_dinamico = 6,
	a_estrella = 7
};

typedef std::deque<point_t> trayectoria_t;

class agent_t
{
private:
	maze_t& maze_;
	point_t start_;
	point_t end_;
public:
	agent_t(maze_t& maze);
	void solve(unsigned mode);

	//Busquedas sin informacion
	void breadth(void);
	void push_back_childs(list_t& paths, path_t path);

	void depth(void);
	void push_front_childs(list_t& paths, path_t path);

	//Búsquedas usando una función heurística (por proximidad al objetivo)

	double h(path_t& path);
	double g(path_t& path);
	double f(path_t& path);
	/*
	void sort_by_heuristic(std::deque<trayectoria_t>& trayectorias);
	void sort_by_acumulated_cost(std::deque<trayectoria_t>& trayectorias);
	void sort_by_acumulated_total_estimated_cost(std::deque<trayectoria_t>& trayectorias);
	void imprime(std::deque<trayectoria_t> lista_trayectorias);
	*/
	void hill_climbing(void);
	void append_sorted_front(list_t& paths, path_t path);

	void bfs(void);
	void append_and_sort_by_h(list_t& paths, path_t path);

	void ucs(void);
	void append_and_sort_by_g(list_t& paths, path_t path);
	/*
	void coste_uniforme_subestimacion(void);
	void anadir_descendientes_y_ordenar_segun_coste_total_estimado(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria);

	void coste_uniforme_dinamico(void);
	void eliminar_trayectoria_de_abierta_e_introducir_en_cerrada_eliminando_similares_de_mayor_coste(std::deque<trayectoria_t>& trayectorias_abiertas, std::deque<trayectoria_t>& trayectorias_cerradas, trayectoria_t& ramificaciones);
	void ramificar_y_anadir_abierta(std::deque<trayectoria_t>& trayectorias_abiertas, trayectoria_t& ramificaciones);
	void eliminar_trayectorias_equivalentes(std::deque<trayectoria_t>& trayectorias_abiertas, std::deque<trayectoria_t>& trayectorias_cerradas);
	void insertar_buscando_similares_y_eliminando_la_de_mayor_coste(std::deque<trayectoria_t>& lista_tra, trayectoria_t trayectoria);

	void a_estrella(void);
	// void eliminar_trayectoria_de_abierta_e_introducir_en_cerrada_eliminando_similares_de_mayor_coste(std::deque<trayectoria_t>& trayectorias_abiertas, std::deque<trayectoria_t>& trayectorias_cerradas, trayectoria_t& ramificaciones);
	// void ramificar_y_anadir_abierta(std::deque<trayectoria_t>& trayectorias_abiertas, trayectoria_t& ramificaciones);
	// void eliminar_trayectorias_equivalentes(std::deque<trayectoria_t>& trayectorias_abiertas, std::deque<trayectoria_t>& trayectorias_cerradas);
	// void insertar_buscando_similares_y_eliminando_la_de_mayor_coste(std::deque<trayectoria_t>& lista_tra, trayectoria_t trayectoria);
	*/
};