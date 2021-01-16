#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using namespace std::string_view_literals;

namespace
{
using Ingredient = std::string;
using Allergen   = std::string;
struct Food
{
   std::set<Ingredient> ingredients;
   std::set<Allergen> allergens;
   void clear() noexcept
   {
      ingredients.clear();
      allergens.clear();
   }
   friend std::istream& operator>>(std::istream& in, Food& food)
   {
      std::string line;
      if(std::getline(in, line))
      {
         food.clear();
         std::istringstream iss(line);
         auto& item = line;
         while(iss >> item && !item.starts_with('('))
            food.ingredients.insert(item);
         assert(item == "(contains"sv);
         while(iss >> item)
            food.allergens.insert((item.pop_back(), item));
      }
      return in;
   }
};
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   std::vector<Food> foods(std::istream_iterator<Food>{in}, {});
   return EXIT_SUCCESS;
}
