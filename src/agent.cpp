#include "agent.hpp"

agent_t::agent_t(maze_t& maze):
maze_(maze)
{
	start_.x() = 1;
	start_.y() = 1;
	end_.x() = maze.x()-2;
	end_.y() = maze.y()-2;
}

void agent_t::solve(unsigned mode)
{
	switch(mode){
		case algorithm::breadth: breadth(); break;
		case algorithm::depth: depth(); break;
		case algorithm::hill_climbing: hill_climbing(); break;
		case algorithm::bfs: bfs(); break;
		case algorithm::ucs: ucs(); break;
		//case algorithm::coste_uniforme_subestimacion: coste_uniforme_subestimacion(); break;
		//case algorithm::coste_uniforme_dinamico: coste_uniforme_dinamico(); break;
		//case algorithm::a_estrella: a_estrella(); break;
	}
}

void agent_t::breadth(void)
{
	list_t paths;
	path_t initial_path;
	initial_path.push(start_);
	paths.push_back(initial_path);

	while(!paths.empty() && (paths.front().last() != end_ )){
		auto path = paths.pop_front();
		push_back_childs(paths, path);
	}
	for(unsigned i = 0; i < paths.front().size(); i++){
		maze_.at(paths.front()[i]) = tile_t::path;
	}
}

void agent_t::push_back_childs(list_t& paths, path_t path)
{
	for(int i = dir_t::n; i <= dir_t::w; i+=2){
		point_t last = path.last();
		dir_t direction = static_cast<dir_t>(i);
		last = last + direction; //End of initialization, in last we have the looking node

		if(maze_.at(last) != tile_t::obstacle){
			if(!path.is(last)){
				maze_.at(last) = tile_t::marked;
				path_t dummy = path;
				dummy.push(last);
				paths.push_back(dummy); //BFS: Append at the end of the list
			}
		}
	}
}

void agent_t::depth(void)
{
	list_t paths;
	path_t initial_path;
	initial_path.push(start_);
	paths.push_back(initial_path);

	while(!paths.empty() && (paths.front().last() != end_ )){
		auto path = paths.pop_front();
		push_front_childs(paths, path);
	}
	for(unsigned i = 0; i < paths.front().size(); i++){
		maze_.at(paths.front()[i]) = tile_t::path;
	}
}

void agent_t::push_front_childs(list_t& paths, path_t path)
{
	for(int i = dir_t::n; i <= dir_t::w; i+=2){
		point_t last = path.last();
		dir_t direction = static_cast<dir_t>(i);
		last = last + direction; //End of initialization, in last we have the looking node

		if(maze_.at(last) != tile_t::obstacle){
			if(!path.is(last)){
				maze_.at(last) = tile_t::marked;
				path_t dummy = path;
				dummy.push(last);
				paths.push_front(dummy); //DFS: Append at the front of the list
			}
		}
	}
}

double agent_t::h(path_t& path)
{
	return (sqrt(((path.last().x()-end_.x())*(path.last().x()-end_.x()) + (path.last().y()-end_.y())*(path.last().y()-end_.y()))));
}

double agent_t::g(path_t& path)
{
	return path.acumulated_cost();
}

double agent_t::f(path_t& path)
{
	return g(path)+h(path);
}

void agent_t::hill_climbing(void)
{
	list_t paths;
	path_t initial_path;
	initial_path.push(start_);
	paths.push_back(initial_path);

	while(!paths.empty() && (paths.front().last() != end_ )){
		auto path = paths.pop_front();
		append_sorted_front(paths, path);
	}
	for(unsigned i = 0; i < paths.front().size(); i++){
		maze_.at(paths.front()[i]) = tile_t::path;
	}
}

void agent_t::append_sorted_front(list_t& paths, path_t path)
{
	list_t new_paths;
	for(int i = dir_t::n; i <= dir_t::w; i+=2){
		point_t last = path.last();
		dir_t direction = static_cast<dir_t>(i);
		last = last + direction; //End of initialization, in last we have the looking node

		if(maze_.at(last) != tile_t::obstacle){
			if(!path.is(last)){
				maze_.at(last) = tile_t::marked;
				path_t dummy = path;
				dummy.push(last);
				new_paths.push_back(dummy); //We add the new paths to a temporaly list
			}
		}
	}
	for(unsigned i = 0; i < new_paths.size(); i++){
		new_paths[i].cost()+=h(new_paths[i]); //We update the cost to the h(x) value of each path
	}
	new_paths.sort(); //We sort the list
	while(!new_paths.empty()){ //We append the new items of the list to the main list
		paths.push_front(new_paths.pop_back());
	}
}

void agent_t::bfs(void)
{
	list_t paths;
	path_t initial_path;
	initial_path.push(start_);
	paths.push_back(initial_path);

	while(!paths.empty() && (paths.front().last() != end_ )){
		auto path = paths.pop_front();
		append_and_sort_by_h(paths, path);
	}
	for(unsigned i = 0; i < paths.front().size(); i++){
		maze_.at(paths.front()[i]) = tile_t::path;
	}
}

void agent_t::append_and_sort_by_h(list_t& paths, path_t path)
{
	for(int i = dir_t::n; i <= dir_t::w; i+=2){
		point_t last = path.last();
		dir_t direction = static_cast<dir_t>(i);
		last = last + direction; //End of initialization, in last we have the looking node

		if(maze_.at(last) != tile_t::obstacle){
			if(!path.is(last)){
				maze_.at(last) = tile_t::marked;
				path_t dummy = path;
				dummy.push(last);
				paths.push_back(dummy); //BFS: Append at the end of the list
			}
		}
	}
	for(unsigned i = 0; i < paths.size(); i++){
		paths[i].cost()+=h(paths[i]); //We update the cost to the h(x) value of each path
	}
	paths.sort(); //We sort the list
}

void agent_t::ucs(void)
{
	list_t paths;
	path_t initial_path;
	initial_path.push(start_);
	paths.push_back(initial_path);

	while(!paths.empty() && (paths.front().last() != end_ )){
		auto path = paths.pop_front();
		append_and_sort_by_g(paths, path);
	}
	for(unsigned i = 0; i < paths.front().size(); i++){
		maze_.at(paths.front()[i]) = tile_t::path;
	}
}

void agent_t::append_and_sort_by_g(list_t& paths, path_t path)
{
	for(int i = dir_t::n; i <= dir_t::w; i+=2){
		point_t last = path.last();
		dir_t direction = static_cast<dir_t>(i);
		last = last + direction; //End of initialization, in last we have the looking node

		if(maze_.at(last) != tile_t::obstacle){
			if(!path.is(last)){
				maze_.at(last) = tile_t::marked;
				path_t dummy = path;
				dummy.push(last);
				paths.push_back(dummy); //BFS: Append at the end of the list
			}
		}
	}
	for(unsigned i = 0; i < paths.size(); i++){
		paths[i].cost()+=g(paths[i]); //We update the cost to the h(x) value of each path
	}
	paths.sort(); //We sort the list
}

/*

void agent_t::coste_uniforme(void)
{
	std::deque<trayectoria_t> lista_trayectorias;
	trayectoria_t trayectoria_inicial;
	trayectoria_inicial.push_back(start_);
	maze_.at(1,1) = tile_t::marked;
	lista_trayectorias.push_back(trayectoria_inicial);

	//While lista not empty and not in final node
	while(!lista_trayectorias.empty() && !(lista_trayectorias.front().back().x() == end_.x() && lista_trayectorias.front().back().y() == end_.y())){
		auto trayectoria = lista_trayectorias.front();
		lista_trayectorias.pop_front();
		anadir_descendientes_y_ordenar_segun_coste_acumulado(lista_trayectorias, trayectoria);
	}
	for(unsigned i = 0; i < lista_trayectorias.front().size(); i++){
		maze_.at(lista_trayectorias.front()[i].x(), lista_trayectorias.front()[i].y()) = tile_t::path;
	}
}

void agent_t::anadir_descendientes_y_ordenar_segun_coste_acumulado(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria)
{
	unsigned nx, ny;
	for(int i = dir_t::n; i <= dir_t::w; i+=2){
		nx = trayectoria.back().x();
		ny = trayectoria.back().y();
		common::coord(nx, ny, i);
		if(maze_.at(nx, ny) == tile_t::empty){
			maze_.at(nx, ny) = tile_t::marked;
			trayectoria_t dummy = trayectoria;
			dummy.push_back(point_t(nx, ny));
			lista_trayectorias.push_front(dummy); //lo ponemos al final
		}
	}
	sort_by_acumulated_cost(lista_trayectorias);
}

void agent_t::coste_uniforme_subestimacion(void)
{
	std::deque<trayectoria_t> lista_trayectorias;
	trayectoria_t trayectoria_inicial;
	trayectoria_inicial.push_back(start_);
	maze_.at(1,1) = tile_t::marked;
	lista_trayectorias.push_back(trayectoria_inicial);

	//While lista not empty and not in final node
	while(!lista_trayectorias.empty() && !(lista_trayectorias.front().back().x() == end_.x() && lista_trayectorias.front().back().y() == end_.y())){
		auto trayectoria = lista_trayectorias.front();
		lista_trayectorias.pop_front();
		anadir_descendientes_y_ordenar_segun_coste_total_estimado(lista_trayectorias, trayectoria);
	}
	for(unsigned i = 0; i < lista_trayectorias.front().size(); i++){
		maze_.at(lista_trayectorias.front()[i].x(), lista_trayectorias.front()[i].y()) = tile_t::path;
	}
}

void agent_t::anadir_descendientes_y_ordenar_segun_coste_total_estimado(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria)
{
	unsigned nx, ny;
	for(int i = dir_t::n; i <= dir_t::w; i+=2){
		nx = trayectoria.back().x();
		ny = trayectoria.back().y();
		common::coord(nx, ny, i);
		if(maze_.at(nx, ny) == tile_t::empty){
			maze_.at(nx, ny) = tile_t::marked;
			trayectoria_t dummy = trayectoria;
			dummy.push_back(point_t(nx, ny));
			lista_trayectorias.push_front(dummy); //lo ponemos al final
		}
	}
	sort_by_acumulated_total_estimated_cost(lista_trayectorias);
}

void agent_t::coste_uniforme_dinamico(void)
{
	std::deque<trayectoria_t> trayectorias_abiertas;
	std::deque<trayectoria_t> trayectorias_cerradas;
	trayectoria_t eliminada;
	trayectoria_t trayectoria_inicial;
	trayectoria_inicial.push_back(start_);
	maze_.at(1,1) = tile_t::marked;
	trayectorias_abiertas.push_back(trayectoria_inicial);

	//While lista not empty and not in final node
	while(!trayectorias_abiertas.empty() && !(trayectorias_abiertas.front().back().x() == end_.x() && trayectorias_abiertas.front().back().y() == end_.y())){
		eliminar_trayectoria_de_abierta_e_introducir_en_cerrada_eliminando_similares_de_mayor_coste(trayectorias_abiertas, trayectorias_cerradas, eliminada);
		ramificar_y_anadir_abierta(trayectorias_abiertas, eliminada);
		sort_by_acumulated_cost(trayectorias_abiertas);
		eliminar_trayectorias_equivalentes(trayectorias_abiertas, trayectorias_cerradas);
	}
	if(!trayectorias_abiertas.empty())
		for(unsigned i = 0; i < trayectorias_abiertas.front().size(); i++){
			maze_.at(trayectorias_abiertas.front()[i].x(), trayectorias_abiertas.front()[i].y()) = tile_t::path;
		}
}

void agent_t::eliminar_trayectoria_de_abierta_e_introducir_en_cerrada_eliminando_similares_de_mayor_coste(std::deque<trayectoria_t>& trayectorias_abiertas, std::deque<trayectoria_t>& trayectorias_cerradas, trayectoria_t& eliminada)
{
	auto trayectoria = trayectorias_abiertas.front();
	eliminada = trayectorias_abiertas.front();
	trayectorias_abiertas.pop_front();
	insertar_buscando_similares_y_eliminando_la_de_mayor_coste(trayectorias_cerradas, trayectoria);
}

void agent_t::ramificar_y_anadir_abierta(std::deque<trayectoria_t>& trayectorias_abiertas, trayectoria_t& eliminada)
{
	unsigned nx, ny;
	for(int i = dir_t::n; i <= dir_t::w; i+=2){
		nx = eliminada.back().x();
		ny = eliminada.back().y();
		common::coord(nx, ny, i);
		if(maze_.at(nx, ny) == tile_t::empty){
			maze_.at(nx, ny) = tile_t::marked;
			trayectoria_t dummy = eliminada;
			dummy.push_back(point_t(nx, ny));
			trayectorias_abiertas.push_front(dummy); //lo ponemos al final
		}
	}
}

void agent_t::eliminar_trayectorias_equivalentes(std::deque<trayectoria_t>& trayectorias_abiertas, std::deque<trayectoria_t>& trayectorias_cerradas)
{
	//Si dos o más trayectorias de ABIERTA acaban en un nodo común, borrar las mismas excepto la que posee mínimo coste entre ellas
	trayectoria_t eliminada;
	for(unsigned i = 0; i < trayectorias_abiertas.size(); i++){
		for(unsigned j = 0; j < trayectorias_abiertas.size(); j++)
		{
			if(i != j){
				if(trayectorias_abiertas[i].back() == trayectorias_abiertas[j].back()){
					if(trayectorias_abiertas[i].size() < trayectorias_abiertas[j].size()){
						eliminada = trayectorias_abiertas[i]; //La trayectoria eliminada, se inserta en lla lista cerrda
						trayectorias_abiertas.erase(trayectorias_abiertas.begin()+j);
						if(j < i)
							i--;
						j--;
					}
					else{
						eliminada = trayectorias_abiertas[j]; //La trayectoria eliminada, se inserta en lla lista cerrda
						trayectorias_abiertas.erase(trayectorias_abiertas.begin()+i);
						i--;
						break;
					}
					insertar_buscando_similares_y_eliminando_la_de_mayor_coste(trayectorias_cerradas, eliminada);
				}
			}
		}
	}
}

void agent_t::insertar_buscando_similares_y_eliminando_la_de_mayor_coste(std::deque<trayectoria_t>& lista_tra, trayectoria_t trayectoria)
{
	for(unsigned i = 0; i < lista_tra.size(); i++){
		if(lista_tra[i].back() == trayectoria.back()){
			if(lista_tra[i].size() < trayectoria.size()) //El coste del que está en la lista es menor
				return;
			else{ //El coste de la que estamos añadiendo es menor
				lista_tra.erase(lista_tra.begin()+i);
				lista_tra.push_back(trayectoria);
			}
		}
	}
}

void agent_t::a_estrella(void)
{
	std::deque<trayectoria_t> trayectorias_abiertas;
	std::deque<trayectoria_t> trayectorias_cerradas;
	trayectoria_t eliminada;
	trayectoria_t trayectoria_inicial;
	trayectoria_inicial.push_back(start_);
	maze_.at(1,1) = tile_t::marked;
	trayectorias_abiertas.push_back(trayectoria_inicial);

	//While lista not empty and not in final node
	while(!trayectorias_abiertas.empty() && !(trayectorias_abiertas.front().back().x() == end_.x() && trayectorias_abiertas.front().back().y() == end_.y())){
		eliminar_trayectoria_de_abierta_e_introducir_en_cerrada_eliminando_similares_de_mayor_coste(trayectorias_abiertas, trayectorias_cerradas, eliminada);
		ramificar_y_anadir_abierta(trayectorias_abiertas, eliminada);
		sort_by_acumulated_total_estimated_cost(trayectorias_abiertas);
		eliminar_trayectorias_equivalentes(trayectorias_abiertas, trayectorias_cerradas);
	}
	if(!trayectorias_abiertas.empty())
		for(unsigned i = 0; i < trayectorias_abiertas.front().size(); i++){
			maze_.at(trayectorias_abiertas.front()[i].x(), trayectorias_abiertas.front()[i].y()) = tile_t::path;
		}
}*/