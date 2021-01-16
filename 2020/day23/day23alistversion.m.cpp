#include <algorithm>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>

namespace
{
constexpr bool trace = true;

void makeMove(int mv, std::list<std::int_fast32_t>& circle)
{
   trace&& std::cout << "-- move " << mv << " --\ncups: ";
   if(trace)
      std::ranges::copy(
         circle, std::ostream_iterator<std::int_fast32_t>(std::cout, " "));
   // remove three cups
   std::list<std::int_fast32_t> takeout;
   auto b = std::next(cbegin(circle), 1);
   auto e = std::next(b, 3);
   takeout.splice(takeout.begin(), circle, b, e);
   trace&& std::cout << "\npickup: ";
   if(trace)
      std::ranges::copy(
         takeout, std::ostream_iterator<std::int_fast32_t>(std::cout, ", "));
   // find designation cup
   auto label{circle.front() - 1};
   for(;;)
   {
      auto iter = std::find(cbegin(circle), cend(circle), label);
      if(iter == cend(circle))
      {
         --label;
         auto [minIt, maxIt] = std::ranges::minmax_element(circle);
         if(label < *minIt)
            label = *maxIt;
      }
      else
      {
         trace&& std::cout << "\ndestination: " << label << "\n\n";
         circle.splice(std::next(iter), takeout);
         break;
      }
   }
   // and that's a rotate
   std::ranges::rotate(circle, std::next(begin(circle)));
}
}  // namespace

int main()
{
   static_assert(
      std::int_fast64_t{1'000'000} * 1'000'000 ==
      std::int_fast64_t{1'000'000'000'000});

   std::ifstream in("../input2.txt");
   std::list<std::int_fast32_t> v;
   std::ranges::generate_n(
      std::back_inserter(v), 9, [n = 0]() mutable { return ++n; });
   assert(v.back() == 9);
   std::transform(
      std::istreambuf_iterator<char>{in}, {}, v.begin(), [](char c) {
         return c - '0';
      });
   for(int i = 0; i < 100; ++i)
      makeMove(i + 1, v);
   // move label '1' first
   std::ranges::rotate(v, std::ranges::find(v, 1));
   if(trace) std::copy(
      std::next(cbegin(v)), cend(v), std::ostream_iterator<int>(std::cout, ""));
   trace && std::cout << '\n';
   auto a = *std::next(cbegin(v), 1);
   auto b = *std::next(cbegin(v), 2);
   std::cout << a << " * " << b << " = "
             << std::int_fast64_t{a} * std::int_fast64_t{b} << std::endl;
   return 0;
}
