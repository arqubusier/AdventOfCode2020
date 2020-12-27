#include <bits/c++config.h>
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
using Confirmeds = std::map<std::string, std::string>;
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

void RemoveSuspects(Suspects &suspects, Confirmeds &confirmeds) {
  for (auto const confirmed : confirmeds) {
    for (auto allergen_it = suspects.begin(); allergen_it != suspects.end();) {
      allergen_it->second.erase(confirmed.second);
      if (allergen_it->second.size() == 1) {
        confirmeds.insert({allergen_it->first, *allergen_it->second.begin()});
        allergen_it = suspects.erase(allergen_it);
      } else {
        allergen_it++;
      }
    }
  }
}

SList GetAllergenFree(Foods foods, Confirmeds const &confirmeds) {
  SList res{};
  for (auto &food : foods) {
    for (auto confirmed : confirmeds) {
      food.first.erase(confirmed.second);
    }
  }
  for (auto food : foods) {
    res.insert(food.first.begin(), food.first.end());
  }
  return res;
}

int main() {
  Foods foods = ReadFoods();
  SList allergens = AllAllergens(foods);
  SList ingredients = AllIngredients(foods);
  Suspects suspects = InitialSuspects(foods, allergens, ingredients);
  Confirmeds confirmeds{};
  // Filter all allergens with one corresponding ingredient.
  for (auto it = suspects.begin(); it != suspects.end();) {
    if (it->second.size() == 1) {
      confirmeds.insert({it->first, *it->second.begin()});
      it = suspects.erase(it);
    } else {
      it++;
    }
  }
  std::size_t old_count = 0;
  do {
    old_count = confirmeds.size();
    RemoveSuspects(suspects, confirmeds);
  } while (old_count != confirmeds.size());

  SList allergen_free = GetAllergenFree(foods, confirmeds);

  std::size_t count = 0;
  for (auto food : foods) {
    for (auto ingredient : allergen_free) {
      count += food.first.count(ingredient);
    }
  }
  std::cout << count << std::endl;

  std::vector<std::pair<std::string, std::string>> sorted{confirmeds.size()};
  std::copy(confirmeds.begin(), confirmeds.end(), sorted.begin());
  std::sort(sorted.begin(), sorted.end(), [](auto lhs, auto rhs) { return lhs.first < rhs.first; });
  std::cout << sorted[0].second;
  sorted.erase(sorted.begin());
  for (auto e : sorted) {
    std::cout << "," << e.second;
  }
  std::cout << std::endl;
  return 0;
}
