#include <cmath>
#include <functional>
#include <iomanip>
#include <numeric>
#include <optional>
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
  Tile &operator=(Tile &&) = default;
  Tile &operator=(Tile const &) = default;

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

    edges[0] = top;
    edges[1] = right;
    edges[2] = bot;
    edges[3] = left;
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
    std::copy(org.edges[3].rbegin(), org.edges[3].rend(), edges[0].begin());
    edges[1] = org.edges[0];
    std::copy(org.edges[1].rbegin(), org.edges[1].rend(), edges[2].begin());
    edges[3] = org.edges[2];
  }

  void RotateCW(int n) {
    for (int i = 0; i < n; i++) {
      RotateCW();
    }
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
  bool operator==(Tile const &rhs) const { return this->id == rhs.id; }

  std::array<Edge, 4> edges;
  Edge top;
  Edge bot;
  Edge left;
  Edge right;
  int id;
};

using Tiles = std::vector<Tile>;
using Grid = std::vector<Tiles>;

void PrintGrid(Grid const &grid) {
  int y_size = grid.size();
  for (int y = 0; y < y_size; y++) {
    bool row_done = false;
    for (int row = 0; !row_done; row++) {
      int x_size = grid[y].size();
      for (int x = 0; x < x_size; x++) {
        row_done = !grid[y][x].PrintRow(row);
        std::cout << ' ';
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

Tile FindTopLeftCorner(Tiles &tiles) {
  for (std::size_t i = 0; i < tiles.size(); i++) {
    auto tile1 = tiles[i];
    bool found = true;
    for (auto tile2 : tiles) {
      if (tile1 == tile2) {
        continue;
      }
      std::array<int, 2> top_left{0, 3};
      for (int i1 : top_left) {
        auto edge1 = tile1.edges[i1];
        for (int i2 = 0; i2 < 4; i2++) {
          auto edge2 = tile2.edges[i2];
          bool reverse_match = std::mismatch(edge1.begin(), edge1.end(), edge2.rbegin()).first == edge1.end();
          if ((edge1 == edge2) || reverse_match) {
            found = false;
            break;
          }
        }
        if (!found) break;
      }
    }

    if (found) {
      tiles.erase(tiles.begin() + i);
      return tile1;
    }
  }
  std::cout << "no top left corner found" << std::endl;
  std::abort();
  return tiles[0];
}

void BuildTopRow(Grid &grid, Tiles &tiles, std::size_t side) {
  for (std::size_t x = 0; x < side - 1; x++) {
    auto edge1 = grid[0][x].edges[1];
    bool next = false;
    for (std::size_t i = 0; i < tiles.size(); i++) {
      auto tile = tiles[i];
      for (int i2 = 0; i2 < 4; i2++) {
        auto edge2 = tile.edges[i2];
        bool reverse_match = std::mismatch(edge1.begin(), edge1.end(), edge2.rbegin()).first == edge1.end();
        if ((edge1 == edge2) || reverse_match) {
          int rotate = 3 - i2;
          tile.RotateCW(rotate);
          if (reverse_match) {
            tile.FlipV();
          }
          tiles.erase(tiles.begin() + i);
          grid[0][x + 1] = tile;
          next = true;
          break;
        }
      }
      if (next) break;
    }
  }
}

void BuildCol(Grid &grid, Tiles &tiles, std::size_t x) {
  std::size_t side = grid[0].size();
  for (std::size_t y = 0; y < side - 1; y++) {
    auto edge1 = grid[y][x].edges[2];
    bool next = false;
    for (std::size_t i = 0; i < tiles.size(); i++) {
      auto tile = tiles[i];
      for (int i2 = 0; i2 < 4; i2++) {
        auto edge2 = tile.edges[i2];
        bool reverse_match = std::mismatch(edge1.begin(), edge1.end(), edge2.rbegin()).first == edge1.end();
        if ((edge1 == edge2) || reverse_match) {
          int rotate = (4 - i2) % 4;
          tile.RotateCW(rotate);
          if (reverse_match) {
            tile.FlipH();
          }
          tiles.erase(tiles.begin() + i);
          grid[y + 1][x] = tile;
          next = true;
          break;
        }
      }
      if (next) break;
    }
  }
}

int main() {
  Tiles tiles;
  do {
    tiles.emplace_back(std::cin);
    std::string blank;
    std::getline(std::cin, blank);
  } while (std::cin);

  std::size_t side = static_cast<std::size_t>(std::sqrt(tiles.size()));
  Tile top_left = FindTopLeftCorner(tiles);
  top_left.Print();

  Grid grid(side, Tiles(side, top_left));
  BuildTopRow(grid, tiles, side);
  for (std::size_t x = 0; x < side; x++) {
    BuildCol(grid, tiles, x);
  }

  return 0;
}
