#include <stdexcept>
#include "Tile.hpp"

Tile tile_from_char(const char &c) {
    switch (c) {
        case '#':
            return Wall;
        case '.':
            return Floor;
        case '*':
            return Path;
        default:
            throw std::runtime_error("Invalid tile character.");
    }
}

char char_from_tile(const Tile &t) {
    switch (t) {
        case Wall:
            return '#';
        case Floor:
            return '.';
        case Path:
            return '*';
        default:
            throw std::runtime_error("Invalid character tile.");
    }
}
