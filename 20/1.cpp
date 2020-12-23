#include "../common.h"

std::size_t const kEdgeLength = 10;
using Edge = std::array<char, kEdgeLength>;

struct Tile {
  void AssignLeftRight(std::size_t i, std::string line) {
    left[i] = line[0];
    right[i] = line[kEdgeLength - 1];
  }

  Tile(Tile const &) = default;
  Tile(Tile &&) = default;

  Tile(std::istream &in) {
    std::string discard;
    in >> discard >> this->id;
    std::getline(in, discard);

    std::string line;
    std::getline(in, line);
    std::copy(line.begin(), line.end(), top.begin());
    AssignLeftRight(0, line);
    for (std::size_t i = 1; i < kEdgeLength - 1; ++i) {
      std::getline(in, line);
      AssignLeftRight(i, line);
    }
    std::getline(in, line);
    std::copy(line.begin(), line.end(), bot.begin());
    AssignLeftRight(kEdgeLength - 1, line);
  }

  void FlipV() {
    std::swap(top, bot);
    std::reverse(left.begin(), left.end());
    std::reverse(right.begin(), right.end());
  }

  void FlipH() {
    std::swap(left, right);
    std::reverse(top.begin(), top.end());
    std::reverse(bot.begin(), bot.end());
  }

  void RotateCW() {
    Tile org{*this};
    top = org.left;
    right = org.top;
    bot = org.right;
    left = org.bot;
  }

  bool operator<(Tile const &rhs) { return this->id < rhs.id; }

  Edge top;
  Edge left;
  Edge right;
  Edge bot;
  int id;
};

using Tiles = std::vector<Tile>;
using Grid = std::vector<Tiles>;

bool FitsTopLeft(Grid &grid, int x, int y) {
  Tile const &current = grid[y][x];
  return ((x <= 0) || (current.right == grid[y][x - 1].left)) && ((y <= 0) || (current.bot == grid[y - 1][x].top));
}

bool FitsRightBottom(Grid &grid, int x, int y) {
  Tile const &current = grid[y][x];
  int y_size = grid.size();
  int x_size = grid[0].size();
  return ((x >= x_size - 1) || (current.right == grid[y][x + 1].left)) &&
         ((y < y_size - 1) || (current.bot == grid[y + 1][x].top));
}

bool Valid(Grid &grid) {
  int y_size = grid.size();
  int x_size = grid[0].size();
  for (int x = 0; x < x_size; x++) {
    for (int y = 0; y < y_size; y++) {
      if (!FitsTopLeft(grid, x, y)) {
        return false;
      }
    }
  }
  return true;
}

/*
  Only need to flip in one direction
  flipping two directions creates duplicates.
 */
bool ModifyInPlace(Grid &grid, int x, int y) {
  int y_size = grid.size();
  int x_size = grid[0].size();
  if (y >= y_size) {
    return Valid(grid);
  }
  int x_prim = (x + 1) % x_size;
  int y_prim = y + 1;
  Tile &current = grid[y][x];

  for (int i = 0; i < 4; i++) {
    if (ModifyInPlace(grid, x_prim, y_prim)) {
      return true;
    }
    current.RotateCW();
  }
  current.FlipH();
  for (int i = 0; i < 4; i++) {
    if (ModifyInPlace(grid, x_prim, y_prim)) {
      return true;
    }
    current.RotateCW();
  }

  return false;
}

int main() {
  Tiles tiles;
  Grid grid;
  do {
    tiles.emplace_back(std::cin);
    std::string blank;
    std::getline(std::cin, blank);
  } while (std::cin);

  // TODO: grid
  do {
    ModifyInPlace(grid, 0, 0);
  } while (std::next_permutation(grid.begin(), grid.end()));

  return 0;
}
