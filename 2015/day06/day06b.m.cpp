#include <array>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <unordered_map>

namespace
{
using Row  = std::array<std::uint_least16_t, 1'000>;
using Grid = std::array<Row, 1'000>;

struct Point
{
   std::uint_fast16_t x;
   std::uint_fast16_t y;

   friend std::istream& operator>>(std::istream& in, Point& point)
   {
      char comma;
      in >> point.x >> comma >> point.y;
      return in;
   }
};

class Command
{
protected:
   Grid& grid_;
   Point const upperLeft_;
   Point const lowerRight_;

public:
   virtual ~Command() = default;

protected:
   Command(Grid& grid, Point const& upperLeft, Point const& lowerRight)
      : grid_(grid)
      , upperLeft_(upperLeft)
      , lowerRight_(lowerRight)
   {
   }

public:
   Command(Command const&) = delete;
   Command& operator=(Command const&) = delete;
   virtual void execute() const       = 0;
};
class ToggleCommand : public Command
{
public:
   ToggleCommand(Grid& grid, Point const& upperLeft, Point const& lowerRight)
      : Command(grid, upperLeft, lowerRight)
   {
   }
   void execute() const override
   {
      for(auto row = upperLeft_.y; row <= lowerRight_.y; ++row)
      {
         auto& currentRow = grid_[row];
         for(auto col = upperLeft_.x; col <= lowerRight_.x; ++col)
         {
            currentRow[col] += 2;
         }
      }
   }
};
class TurnOffCommand : public Command
{
public:
   TurnOffCommand(Grid& grid, Point const& upperLeft, Point const& lowerRight)
      : Command(grid, upperLeft, lowerRight)
   {
   }
   void execute() const override
   {
      for(auto row = upperLeft_.y; row <= lowerRight_.y; ++row)
      {
         auto& currentRow = grid_[row];
         for(auto col = upperLeft_.x; col <= lowerRight_.x; ++col)
         {
            if(currentRow[col] != 0u)
            {
               --currentRow[col];
            }
         }
      }
   }
};
class TurnOnCommand : public Command
{
public:
   TurnOnCommand(Grid& grid, Point const& upperLeft, Point const& lowerRight)
      : Command(grid, upperLeft, lowerRight)
   {
   }
   void execute() const override
   {
      for(auto row = upperLeft_.y; row <= lowerRight_.y; ++row)
      {
         auto& currentRow = grid_[row];
         for(auto col = upperLeft_.x; col <= lowerRight_.x; ++col)
         {
            ++currentRow[col];
         }
      }
   }
};

template <typename IdentifierType, typename ProductCreator>
class Factory
{
   std::unordered_map<IdentifierType, ProductCreator> map_;

public:
   bool Register(IdentifierType const& id, ProductCreator creator)
   {
      return map_.emplace(id, creator).second;
   }
   bool Unregister(IdentifierType const& id)
   {
      return map_.erase(id) == 1;
   }
   template <class... A>
   auto CreateObject(IdentifierType const& id, A&&... a) const
   {
      if(auto i = map_.find(id); i != map_.end())
      {
         return (i->second)(std::forward<A>(a)...);
      }
      throw std::runtime_error(
         "Unknown id: `" + id + '\'');  // OR return decltype((i->second)())();
   }
};

auto countLitLights(Grid const& grid)
{
   return std::accumulate(
      cbegin(grid), cend(grid), uintmax_t{}, [](auto a, auto const& row) {
         return a + std::accumulate(cbegin(row), cend(row), uintmax_t{});
      });
}
}  // namespace

int main()
{
   Grid grid{};
   Factory<
      std::string,
      std::function<std::unique_ptr<Command>(Grid&, Point, Point)>>
      plant;
   plant.Register("toggle", [](Grid& g, Point ul, Point lr) {
      return std::make_unique<ToggleCommand>(g, ul, lr);
   });
   plant.Register("turn off", [](Grid& g, Point ul, Point lr) {
      return std::make_unique<TurnOffCommand>(g, ul, lr);
   });
   plant.Register("turn on", [](Grid& g, Point ul, Point lr) {
      return std::make_unique<TurnOnCommand>(g, ul, lr);
   });
   std::ifstream in("../input.txt");
   while(in)
   {
      std::string id;
      if(!(in >> id))
      {
         break;
      }
      if(id == "turn")
      {
         std::string onoff;
         in >> onoff;
         id += ' ' + onoff;
      }
      Point ul;
      std::string through;
      Point lr;
      in >> ul >> through >> lr;
      plant.CreateObject(id, grid, ul, lr)->execute();
   }
   std::cout << countLitLights(grid) << std::endl;
   return EXIT_SUCCESS;
}
