#ifndef CALC2_H
#define CALC2_H

#include <iosfwd>

#include <tokenstream.h>

namespace pkg
{
class Calc2
{
   TokenStream m_ts;

public:
   explicit Calc2(std::istream&);
   Token eval();

private:
   Result expression();
   Result term();
   Result primary();
};
}  // namespace pkg
#endif
