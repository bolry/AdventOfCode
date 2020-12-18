#include <calc1.h>
#include <cassert>

#include <tokenstream.h>

namespace pkg
{
Calc1::Calc1(std::istream& ar_in) : m_ts(ar_in) {}

Token Calc1::eval()
{
   Token t = m_ts.get();
   if(t.kind == kQuit)
      return t;
   m_ts.putback(t);
   t.kind  = kNumber;
   t.value = expression();
   return t;
}
Result Calc1::expression()
{
   Result left = primary();
   for(Token t = m_ts.get();; t = m_ts.get())
   {
      switch(t.kind)
      {
      case '+':
         left += primary();
         break;
      case '*':
         left *= primary();
         break;
      default:
         m_ts.putback(t);
         return left;
      }
   }
}
Result Calc1::primary()
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
