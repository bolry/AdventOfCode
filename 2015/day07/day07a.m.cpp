#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <vector>

using namespace std::literals;

namespace
{
struct Row
{
   std::string left;
   std::string right;
   operator std::pair<std::string, std::string>() const
   {
      return {right, left};
   }
   friend std::istream& operator>>(std::istream& in, Row& row)
   {
      std::string line;
      if(std::getline(in, line))
      {
         constexpr auto arrow = " -> "sv;
         auto const pos       = line.find(arrow);
         row.left             = line.substr(0, pos);
         row.right            = line.substr(pos + size(arrow));
      }
      return in;
   }
};
#if 0
struct Connect
{
   std::string row;
   friend std::istream& operator>>(std::istream& in, Connect& connect)
   {
      std::getline(in, connect.row);
      return in;
   }
};
struct Gate
{
   virtual ~Gate()   = 0;
   Gate()            = default;
   Gate(Gate const&) = delete;
   Gate& operator=(Gate const&) = delete;
};
Gate::~Gate() = default;
struct Sig2 : Gate
{
};
struct Signal2 : Gate
{
};
struct And2 : Gate
{
};
struct Lshift2 : Gate
{
};
struct Not2 : Gate
{
};
struct Or2 : Gate
{
};
struct Rshift2 : Gate
{
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
#endif

}  // namespace

int main()
{
   std::ifstream in("../input2.txt");
   std::unordered_map<std::string, std::string> wiring;
   transform(      std::istream_iterator<Row>{in}, std::istream_iterator<Row>{});
   std::cout << std::endl;
   return EXIT_SUCCESS;
}
