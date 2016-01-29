#include "agent.hpp"

agent_t::agent_t(maze_t* maze):
maze_(maze)
{
	start_.x() = 1;
	start_.y() = 1;
	end_.x() = maze->x()-2;
	end_.y() = maze->y()-2;
}

void agent_t::solve(unsigned mode)
{
	switch(mode){
		case algorithm::breadth: breadth(); break;
		case algorithm::depth: depth(); break;
		case algorithm::escalada: escalada(); break;
		case algorithm::primero_el_mejor: primero_el_mejor(); break;
		case algorithm::coste_uniforme: coste_uniforme(); break;
		case algorithm::coste_uniforme_subestimacion: coste_uniforme_subestimacion(); break;
		case algorithm::coste_uniforme_dinamico: coste_uniforme_dinamico(); break;
		case algorithm::a_estrella: a_estrella(); break;
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
		maze_->at(paths.front()[i]) = tile::path;
	}
}

void agent_t::push_back_childs(list_t& paths, path_t path)
{
	for(int i = dir::n; i <= dir::w; i+=2){
		point_t last = path.last();
		dir direction = static_cast<dir>(i);

		last = last + direction;
		if(maze_->at(last) != tile::obstacle){
			if(!path.is(last)){
				maze_->at(last) = tile::marked;
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
		maze_->at(paths.front()[i]) = tile::path;
	}
}

void agent_t::push_front_childs(list_t& paths, path_t path)
{
	for(int i = dir::n; i <= dir::w; i+=2){
		point_t last = path.last();
		dir direction = static_cast<dir>(i);

		last = last + direction;
		if(maze_->at(last) != tile::obstacle){
			if(!path.is(last)){
				maze_->at(last) = tile::marked;
				path_t dummy = path;
				dummy.push(last);
				paths.push_front(dummy); //DFS: Append at the front of the list
			}
		}
	}
}

double agent_t::h(point_t origen)
{
	return (sqrt(((origen.x()-end_.x())*(origen.x()-end_.x()) + (origen.y()-end_.y())*(origen.y()-end_.y()))));
}

void agent_t::sort_by_heuristic(std::deque<trayectoria_t>& trayectorias)
{
	for(std::size_t i = 0; i < trayectorias.size(); i++){
		std::size_t min = i;
		for(std::size_t j = i + 1; j < trayectorias.size(); j++)
			if(h(trayectorias[j].back()) < h(trayectorias[min].back()))
				min = j;
		std::swap(trayectorias[i], trayectorias[min]);
	}
}

void agent_t::sort_by_acumulated_cost(std::deque<trayectoria_t>& trayectorias)
{
	for(std::size_t i = 0; i < trayectorias.size(); i++){
		std::size_t min = i;
		for(std::size_t j = i + 1; j < trayectorias.size(); j++)
			if(trayectorias[j].size() < trayectorias[min].size())
				min = j;
		std::swap(trayectorias[i], trayectorias[min]);
	}
}

void agent_t::sort_by_acumulated_total_estimated_cost(std::deque<trayectoria_t>& trayectorias)
{
	for(std::size_t i = 0; i < trayectorias.size(); i++){
		std::size_t min = i;
		for(std::size_t j = i + 1; j < trayectorias.size(); j++)
			if((trayectorias[j].size() + h(trayectorias[j].back())) < (trayectorias[min].size() + h(trayectorias[min].back())))
				min = j;
		std::swap(trayectorias[i], trayectorias[min]);
	}
}

void agent_t::escalada(void)
{
	std::deque<trayectoria_t> lista_trayectorias;
	trayectoria_t trayectoria_inicial;
	trayectoria_inicial.push_back(start_);
	maze_->at(1,1) = tile::marked;
	lista_trayectorias.push_back(trayectoria_inicial);

	//While lista not empty and not in final node
	while(!lista_trayectorias.empty() && !(lista_trayectorias.front().back().x() == end_.x() && lista_trayectorias.front().back().y() == end_.y())){
		auto trayectoria = lista_trayectorias.front();
		lista_trayectorias.pop_front();
		anadir_descendientes_al_principio_ordenados(lista_trayectorias, trayectoria);
	}
	for(unsigned i = 0; i < lista_trayectorias.front().size(); i++){
		maze_->at(lista_trayectorias.front()[i].x(), lista_trayectorias.front()[i].y()) = tile::path;
	}
}

void agent_t::anadir_descendientes_al_principio_ordenados(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria)
{
	unsigned nx, ny;
	std::deque<trayectoria_t> lista_desordenada;
	for(int i = dir::n; i <= dir::w; i+=2){
		nx = trayectoria.back().x();
		ny = trayectoria.back().y();
		common::coord(nx, ny, i);
		if(maze_->at(nx, ny) == tile::empty){
			maze_->at(nx, ny) = tile::marked;
			trayectoria_t dummy = trayectoria;
			dummy.push_back(point_t(nx, ny));
			lista_desordenada.push_front(dummy); //lo ponemos al final
		}
	}
	sort_by_heuristic(lista_desordenada);
	while(!lista_desordenada.empty()){
		auto last = lista_desordenada.back();
		lista_desordenada.pop_back();
		lista_trayectorias.push_front(last);
	}
}

void agent_t::primero_el_mejor(void)
{
	std::deque<trayectoria_t> lista_trayectorias;
	trayectoria_t trayectoria_inicial;
	trayectoria_inicial.push_back(start_);
	maze_->at(1,1) = tile::marked;
	lista_trayectorias.push_back(trayectoria_inicial);

	//While lista not empty and not in final node
	while(!lista_trayectorias.empty() && !(lista_trayectorias.front().back().x() == end_.x() && lista_trayectorias.front().back().y() == end_.y())){
		auto trayectoria = lista_trayectorias.front();
		lista_trayectorias.pop_front();
		anadir_descendientes_y_ordenar(lista_trayectorias, trayectoria);
	}
	for(unsigned i = 0; i < lista_trayectorias.front().size(); i++){
		maze_->at(lista_trayectorias.front()[i].x(), lista_trayectorias.front()[i].y()) = tile::path;
	}
}

void agent_t::anadir_descendientes_y_ordenar(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria)
{
	unsigned nx, ny;
	for(int i = dir::n; i <= dir::w; i+=2){
		nx = trayectoria.back().x();
		ny = trayectoria.back().y();
		common::coord(nx, ny, i);
		if(maze_->at(nx, ny) == tile::empty){
			maze_->at(nx, ny) = tile::marked;
			trayectoria_t dummy = trayectoria;
			dummy.push_back(point_t(nx, ny));
			lista_trayectorias.push_front(dummy); //lo ponemos al final
		}
	}
	sort_by_heuristic(lista_trayectorias);
}

void agent_t::coste_uniforme(void)
{
	std::deque<trayectoria_t> lista_trayectorias;
	trayectoria_t trayectoria_inicial;
	trayectoria_inicial.push_back(start_);
	maze_->at(1,1) = tile::marked;
	lista_trayectorias.push_back(trayectoria_inicial);

	//While lista not empty and not in final node
	while(!lista_trayectorias.empty() && !(lista_trayectorias.front().back().x() == end_.x() && lista_trayectorias.front().back().y() == end_.y())){
		auto trayectoria = lista_trayectorias.front();
		lista_trayectorias.pop_front();
		anadir_descendientes_y_ordenar_segun_coste_acumulado(lista_trayectorias, trayectoria);
	}
	for(unsigned i = 0; i < lista_trayectorias.front().size(); i++){
		maze_->at(lista_trayectorias.front()[i].x(), lista_trayectorias.front()[i].y()) = tile::path;
	}
}

void agent_t::anadir_descendientes_y_ordenar_segun_coste_acumulado(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria)
{
	unsigned nx, ny;
	for(int i = dir::n; i <= dir::w; i+=2){
		nx = trayectoria.back().x();
		ny = trayectoria.back().y();
		common::coord(nx, ny, i);
		if(maze_->at(nx, ny) == tile::empty){
			maze_->at(nx, ny) = tile::marked;
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
	maze_->at(1,1) = tile::marked;
	lista_trayectorias.push_back(trayectoria_inicial);

	//While lista not empty and not in final node
	while(!lista_trayectorias.empty() && !(lista_trayectorias.front().back().x() == end_.x() && lista_trayectorias.front().back().y() == end_.y())){
		auto trayectoria = lista_trayectorias.front();
		lista_trayectorias.pop_front();
		anadir_descendientes_y_ordenar_segun_coste_total_estimado(lista_trayectorias, trayectoria);
	}
	for(unsigned i = 0; i < lista_trayectorias.front().size(); i++){
		maze_->at(lista_trayectorias.front()[i].x(), lista_trayectorias.front()[i].y()) = tile::path;
	}
}

void agent_t::anadir_descendientes_y_ordenar_segun_coste_total_estimado(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria)
{
	unsigned nx, ny;
	for(int i = dir::n; i <= dir::w; i+=2){
		nx = trayectoria.back().x();
		ny = trayectoria.back().y();
		common::coord(nx, ny, i);
		if(maze_->at(nx, ny) == tile::empty){
			maze_->at(nx, ny) = tile::marked;
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
	maze_->at(1,1) = tile::marked;
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
			maze_->at(trayectorias_abiertas.front()[i].x(), trayectorias_abiertas.front()[i].y()) = tile::path;
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
	for(int i = dir::n; i <= dir::w; i+=2){
		nx = eliminada.back().x();
		ny = eliminada.back().y();
		common::coord(nx, ny, i);
		if(maze_->at(nx, ny) == tile::empty){
			maze_->at(nx, ny) = tile::marked;
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
	maze_->at(1,1) = tile::marked;
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
			maze_->at(trayectorias_abiertas.front()[i].x(), trayectorias_abiertas.front()[i].y()) = tile::path;
		}
}