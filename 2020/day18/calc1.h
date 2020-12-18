#ifndef CALC1_H
#define CALC1_H

#include <iosfwd>

#include <tokenstream.h>

namespace pkg
{
class Calc1
{
   TokenStream m_ts;

public:
   explicit Calc1(std::istream&);
   Token eval();

private:
   Result expression();
   Result primary();
};
}  // namespace pkg
#endif
