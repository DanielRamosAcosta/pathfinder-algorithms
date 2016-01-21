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
		case algorithm::anchura: anchura(); break;
		case algorithm::profundidad: profundidad(); break;
		case algorithm::escalada: escalada(); break;
		case algorithm::primero_el_mejor: primero_el_mejor(); break;
	}
}

void agent_t::anchura(void)
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
		anadir_descendientes_al_final(lista_trayectorias, trayectoria);
	}
	for(unsigned i = 0; i < lista_trayectorias.front().size(); i++){
		maze_->at(lista_trayectorias.front()[i].x(), lista_trayectorias.front()[i].y()) = tile::path;
	}
}

void agent_t::anadir_descendientes_al_final(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria)
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
			lista_trayectorias.push_back(dummy); //lo ponemos al principio
		}
	}
}

void agent_t::profundidad(void)
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
		anadir_descendientes_al_principio(lista_trayectorias, trayectoria);
	}
	for(unsigned i = 0; i < lista_trayectorias.front().size(); i++){
		maze_->at(lista_trayectorias.front()[i].x(), lista_trayectorias.front()[i].y()) = tile::path;
	}
}

void agent_t::anadir_descendientes_al_principio(std::deque<trayectoria_t>& lista_trayectorias, trayectoria_t trayectoria)
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
}

long double agent_t::h(point_t origen)
{
	return (sqrt(((origen.x()-end_.x())*(origen.x()-end_.x()) + (origen.y()-end_.y())*(origen.y()-end_.y()))));
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

void agent_t::sort(std::deque<trayectoria_t>& trayectorias)
{
	for(std::size_t i = 0; i < trayectorias.size(); i++){
		std::size_t min = i;
		for(std::size_t j = i + 1; j < trayectorias.size(); j++)
			if(h(trayectorias[j].back()) < h(trayectorias[min].back()))
				min = j;
		std::swap(trayectorias[i], trayectorias[min]);
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
	sort(lista_desordenada);
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
		maze_->print(std::cout);
		sleep(2);
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
	sort(lista_trayectorias);
}