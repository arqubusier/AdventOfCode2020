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
    edges[1] = bot;
    edges[2] = left;
    edges[3] = right;
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

void AddTile(Grid &grid, Tile tile) {
  if (grid.empty()) {
    grid.push_back(Tiles{tile});
  }

  int y_size = grid.size();
  for (int y = 0; y < y_size; y++) {
    int x_size = grid[y].size();
    for (int x = 0; x < x_size; x++) {
      Tile const &candidate = grid[y][x];
      for (int i1 = 0; i1 < candidate.edges.size(); i1++) {
        for (int i2 = 0; i2 < tile.edges.size(); i2++) {
          bool reverse_match =
              std::mismatch(candidate.edges.begin(), candidate.edges.end(), tile.edges.rbegin()).first ==
              candidate.edges.end();
          if (candidate.edges[i1] == tile.edges[i2]) {
            // find coordinates for new tile
            int x_fit;
            int y_fit;
            if (i1 < 2) {
              x_fit = x;
              y_fit = y - 1 + 2 * i1;
            } else {
              y_fit = y;
              x_fit = x - 1 + 2 * (i1 - 2);
            }
            int rotate = i2 * 2;
            // find rotation for new tile
            if (i2 >= 2) {
              rotate += 1;
            }
          }
        }
      }
    }
  }
}

int main() {
  Tiles tiles;
  Grid grid;
  do {
    tiles.emplace_back(std::cin);
    std::string blank;
    std::getline(std::cin, blank);
  } while (std::cin);

  std::vector<u64> corners_id{};
  //  std::size_t side = static_cast<std::size_t>(std::sqrt(tiles.size()));
  for (auto tile1 : tiles) {
    int matches = 0;
    Tiles matched_tiles{};
    for (auto tile2 : tiles) {
      if (tile1 == tile2) {
        continue;
      }
      for (auto edge1 : tile1.edges) {
        for (auto edge2 : tile2.edges) {
          bool reverse_match = std::mismatch(edge1.begin(), edge1.end(), edge2.rbegin()).first == edge1.end();
          if ((edge1 == edge2) || reverse_match) {
            matched_tiles.push_back(tile2);
            matches++;
          }
        }
      }
    }
    if (matches == 2) {
      tile1.Print();
      for (auto tile : matched_tiles) {
        tile.Print();
      }
      std::cout << "------------------------" << std::endl;
      corners_id.push_back(tile1.id);
    }
  }

  u64 product = std::accumulate(corners_id.begin(), corners_id.end(), u64{1}, std::multiplies<u64>{});
  std::cout << product << std::endl;

  return 0;
}
