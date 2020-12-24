#include <cmath>
#include <iomanip>
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
    std::copy(org.left.rbegin(), org.left.rend(), top.begin());
    right = org.top;
    std::copy(org.right.rbegin(), org.right.rend(), bot.begin());
    left = org.bot;
  }

  void Print() const {
    for (int row = 0; PrintRow(row); row++) {
      std::cout << std::endl;
    }
  }

  bool PrintRow(std::size_t row) const {
    if (row >= top.size()) return false;

    if (row == 0) {
      for (char e : top) {
        std::cout << e;
      }
    } else if (row == top.size() - 1) {
      for (char e : bot) {
        std::cout << e;
      }
    } else {
      std::cout << left[row];
      int fill = top.size() - 2;
      if (row == 1) {
        std::cout << std::setw(fill) << id;
      } else {
        std::cout << std::string(fill, ' ');
      }
      std::cout << right[row];
    }
    return true;
  }

  bool operator<(Tile const &rhs) const { return this->id < rhs.id; }

  Edge top;
  Edge left;
  Edge right;
  Edge bot;
  int id;
};

using Tiles = std::vector<Tile>;
using Grid = std::vector<Tiles>;

void PrintGrid(Grid const &grid) {
  int y_size = grid.size();
  int x_size = grid[0].size();
  for (int y = 0; y < y_size; y++) {
    bool row_done = false;
    for (int row = 0; !row_done; row++) {
      for (int x = 0; x < x_size; x++) {
        row_done = !grid[y][x].PrintRow(row);
        std::cout << ' ';
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

bool FitsTopLeft(Grid const &grid, int x, int y) {
  Tile const &current = grid[y][x];
  return ((x <= 0) || (current.left == grid[y][x - 1].right)) && ((y <= 0) || (current.top == grid[y - 1][x].bot));
}

bool FitsRightBottom(Grid const &grid, int x, int y) {
  Tile const &current = grid[y][x];
  int y_size = grid.size();
  int x_size = grid[0].size();
  return ((x >= x_size - 1) || (current.right == grid[y][x + 1].left)) &&
         ((y < y_size - 1) || (current.bot == grid[y + 1][x].top));
}

bool Valid(Grid const &grid) {
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

int count = 0;
/*
  Only need to flip in one direction
  flipping two directions creates duplicates.
 */
bool ModifyInPlace(Grid &grid, int n) {
  int y_size = grid.size();
  int x_size = grid[0].size();
  int x = n % x_size;
  int y = n / y_size;
  if (y >= y_size) {
    return Valid(grid);
  }
  Tile &current = grid[y][x];

  for (int i = 0; i < 4; i++) {
    if (ModifyInPlace(grid, n + 1)) {
      return true;
    }
    current.RotateCW();
  }
  current.FlipH();
  for (int i = 0; i < 4; i++) {
    if (ModifyInPlace(grid, n + 1)) {
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

  std::size_t side = static_cast<std::size_t>(std::sqrt(tiles.size()));
  auto start = tiles.begin();
  auto end = start + side;
  for (std::size_t row = 0; row < side; row++) {
    grid.emplace_back(start, end);
    start = end;
    end = start + side;
  }

  do {
    if (ModifyInPlace(grid, 0)) {
      PrintGrid(grid);
      std::cout << Valid(grid) << std::endl;
      break;
    }
    PrintGrid(grid);
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
  } while (std::next_permutation(grid.begin(), grid.end()));

  return 0;
}
