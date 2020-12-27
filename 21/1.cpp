#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using SList = std::set<std::string>;
using Foods = std::vector<std::pair<SList, SList>>;

Foods ReadFoods() {
  Foods res{};

  while (true) {
    SList ingredients{};
    std::string word;
    if (!(std::cin >> word)) {
      break;
    }
    do {
      if (word == "(contains") {
        break;
      }
      ingredients.insert(word);
    } while (std::cin >> word);
    SList allergens{};
    while (std::cin >> word) {
      char delim = word.back();
      word.pop_back();
      allergens.insert(word);
      if (delim == ')') {
        break;
      }
    }

    res.push_back({ingredients, allergens});
  }
  return res;
}

SList AllAllergens(Foods &foods) {
  SList res{};
  for (auto p : foods) {
    // Set union
    res.insert(p.second.begin(), p.second.end());
  }

  return res;
}

SList AllIngredients(Foods &foods) {
  SList res{};
  for (auto p : foods) {
    // Set union
    res.insert(p.first.begin(), p.first.end());
  }

  return res;
}

SList Intersection(SList const &first, SList const &second) {
  SList res{};

  for (auto e : first) {
    if (second.count(e) == 1) {
      res.insert(e);
    }
  }
  return res;
}

using Suspects = std::map<std::string, SList>;
Suspects InitialSuspects(Foods const &foods, SList const &allergens, SList const &ingredients) {
  Suspects res{};
  for (auto allergen : allergens) {
    res.insert({allergen, ingredients});
    for (auto food : foods) {
      if (food.second.count(allergen) == 1) {
        res[allergen] = Intersection(res[allergen], food.first);
      }
    }
  }

  return res;
}

bool RemoveSuspects(Suspects &suspects, ) {
  for (auto single : suspects) {
    if (single.second.size() > 1) {
      continue;
    }
    for (auto
  }
}

int main() {
  Foods foods = ReadFoods();
  SList allergens = AllAllergens(foods);
  SList ingredients = AllIngredients(foods);
  Suspects suspects = InitialSuspects(foods, allergens, ingredients);
  while (RemoveSuspects(suspects)) {
  }
  return 0;
}
