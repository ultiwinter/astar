#include "MyGrid.hpp"
#include <utility>
#include <cassert>
#include <algorithm>
#include <sstream>



// TODO Define all member functions:
MyGrid::MyGrid(size_t rows, size_t cols, const Tile& initialTile) : Rows(rows), Cols(cols) {
	//Creating the Array
	Array = new Tile* [Rows];
	for (size_t i = 0; i < Rows; i++) {
		Array[i] = new Tile[Cols]; 
	}
	//Filling the Array Manually
	for (size_t i = 0; i < Rows; i++) {
		for (size_t j = 0; j < Cols; j++) {
			Array[i][j] = initialTile;
		}
	}
}

MyGrid::MyGrid(const MyGrid& other){
	Rows = other.Rows;
	Cols = other.Cols;
	Array = new Tile* [Rows];
	for (size_t i = 0; i < Rows; i++) {
		Array[i] = new Tile[Cols]; 
	}
	
	std::copy(other.Array, other.Array + Rows * Cols, Array); 

}

MyGrid::MyGrid(MyGrid&& other) noexcept{

	
	Rows = std::exchange(other.Rows, 0);
	
	Cols = std::exchange(other.Cols, 0);
	
	Array = std::move(other.Array);
	
	
	

}

MyGrid& MyGrid::operator=(MyGrid&& other) noexcept {
	
	
	Cols = std::exchange(other.Cols, 0);
	
	Rows = std::exchange(other.Rows, 0); //**
	
	Array = std::move(other.Array);
	
	

	return *this;
}
MyGrid& MyGrid::operator=(const MyGrid& other) {
	if (this == &other) {return *this;}
	// if (Array != nullptr) {
	// 	for (size_t i = 0; i < Rows; i++) {
	// 		delete[] Array[i];
	// 	}
	// 	delete[] Array;
	// }
	
	Rows = other.Rows;
	
	Cols = other.Cols;
	
	std::copy(other.Array, other.Array + Rows * Cols, Array);
	
	
	
	return *this;
}
MyGrid::~MyGrid() {
	if (Array == nullptr){

		for (size_t i = 0; i < Rows; i++) {
			delete[] Array[i];
		}
		delete[] Array;
	}
}

size_t MyGrid::rows() const {
	return Rows;
}
size_t MyGrid::cols() const {
	return Cols;
}
size_t MyGrid::size() const {
	return Rows * Cols;
}

bool MyGrid::validPosition(size_t row, size_t col) const noexcept {
		return row < Rows && col < Cols;
}

Tile& MyGrid::operator()(size_t row, size_t col) {

	if (!validPosition(row, col)) {
		throw std::out_of_range("invalid_grid_position");
	}
	else {
		return Array[row][col];
		
	}
}
const Tile& MyGrid::operator()(size_t row, size_t col) const {
	if (!MyGrid::validPosition(row, col)) {
		throw std::out_of_range("invalid_grid_position");
	}
	else {
		return Array[row][col];
	}
}

MyGrid MyGrid::read(std::istream & in) {
	std::string r;
	std::string c;
	//size_t r, c;
	getline(in, r);
	getline(in, c);
	int ri = stoi(r);
	size_t rs = (size_t)ri;
	int ci = stoi(c);
	size_t cs = (size_t)ci;
	MyGrid newgrid(rs, cs, Wall);
	for (size_t i = 0; i < rs; i++) {
		std::string line;
		getline(in, line);
		for (size_t j = 0; j < cs; j++) {
			newgrid(i, j) = tile_from_char(line[j]);
		}
	}
	return newgrid;
	}

std::ostream& operator<<(std::ostream& out, const MyGrid& grid) {
	out << grid.Rows << std::endl;
	out << grid.Cols << std::endl;
	for (size_t i = 0; i < grid.Rows; i++) {
		for (size_t j = 0; j < grid.Cols; j++) {
			out << char_from_tile(grid.Array[i][j]);
		}
		out << std::endl;
	}
	return out;
}

