#include <calc2.h>
#include <cassert>

#include <tokenstream.h>

namespace pkg
{
Calc2::Calc2(std::istream& ar_in) : m_ts(ar_in) {}

Token Calc2::eval()
{
   Token t = m_ts.get();
   if(t.kind == kQuit)
      return t;
   m_ts.putback(t);
   t.kind  = kNumber;
   t.value = expression();
   return t;
}
Result Calc2::expression()
{
   Result left = term();
   for(Token t = m_ts.get();; t = m_ts.get())
   {
      switch(t.kind)
      {
      case '*':
         left *= term();
         break;
      default:
         m_ts.putback(t);
         return left;
      }
   }
}
Result Calc2::term()
{
   Result left = primary();
   for(Token t = m_ts.get();; t = m_ts.get())
   {
      switch(t.kind)
      {
      case '+':
         left += primary();
         break;
      default:
         m_ts.putback(t);
         return left;
      }
   }
}

Result Calc2::primary()
{
   Token t = m_ts.get();
   switch(t.kind)
   {
   case '(':
   {
      Result d = expression();
      t        = m_ts.get();
      assert(t.kind == ')');
      return d;
   }
   case kNumber:
      return t.value;
   default:
      assert(false);
   }
}
}  // namespace pkg
