#include <cassert>

#include <boost/multi_array.hpp>

int main()
{
   using array_type = boost::multi_array<double, 3>;
   using index      = array_type::index;

   array_type A(boost::extents[3][4][2]);
   double values{};
   for(index i = 0; i != 3; ++i)
      for(index j = 0; j != 4; ++j)
         for(index k = 0; k != 2; ++k)
            A[i][j][k] = values++;
   double verify{};
   for(index i = 0; i != 3; ++i)
      for(index j = 0; j != 4; ++j)
         for(index k = 0; k != 2; ++k)
            assert(A[i][j][k] == verify), ++verify;
   return EXIT_SUCCESS;
}
