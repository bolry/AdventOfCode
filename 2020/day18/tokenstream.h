#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include <cstdint>
#include <iosfwd>

namespace pkg
{
constexpr char kNumber{'8'};
constexpr char kQuit{'q'};

using Result = std::intmax_t;

struct Token
{
   char kind;
   pkg::Result value;
};

class TokenStream
{
   std::istream& m_in;
   bool m_full{};
   Token m_buffer;

public:
   explicit TokenStream(std::istream&);
   Token get();
   void putback(Token);
};
}  // namespace pkg
#endif
