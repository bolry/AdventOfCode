#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>

#include <boost/circular_buffer.hpp>

namespace
{
constexpr bool kTrace = false;

using Label = std::int_least32_t;

void doMove(boost::circular_buffer<Label>& circle)
{
   auto nextLabel = circle.front() - 1;
   auto b         = std::next(begin(circle));
   auto e         = std::next(b, 3);
   while(
      std::any_of(b, e, [nextLabel](auto val) { return val == nextLabel; }) ||
      nextLabel == 0)
      if(nextLabel != 0)
         --nextLabel;
      else
         nextLabel = ssize(circle);
   circle.rotate(e);
   auto iter = std::ranges::find(circle, nextLabel);
   std::rotate(std::next(iter), std::prev(end(circle), 3), end(circle));
}

}  // namespace

int main()
{
   auto gameSize = 1'000'000;
   boost::circular_buffer<Label> circle(gameSize);
   std::ranges::copy(
      //      std::initializer_list<Label>{3, 8, 9, 1, 2, 5, 4, 6, 7},
      std::initializer_list<Label>{5, 8, 9, 1, 7, 4, 2, 6, 3},
      std::back_inserter(circle));
   for(std::int_fast32_t i{ssize(circle) + 1}; i < gameSize + 1; ++i)
      circle.push_back(i);
   //   std::ranges::copy(circle, std::ostream_iterator<Label>(std::cout, " "));
   //   std::cout << '\n';
   for(std::int_fast32_t i{}; i < 10'000'000; ++i)
      doMove(circle);

   auto iter = std::ranges::find(circle, 1);
   circle.rotate(iter);
   circle.pop_front();
   //   std::ranges::copy(circle, std::ostream_iterator<Label>(std::cout, " "));
   //   std::cout << '\n';
   std::int_fast64_t a = circle.front();
   std::int_fast64_t b = *std::next(begin(circle));
   std::cout << a << " * " << b << " == " << a * b << std::endl;
   return 0;
}
