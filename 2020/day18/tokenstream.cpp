#include <tokenstream.h>
#include <cassert>
#include <istream>

namespace pkg
{
TokenStream::TokenStream(std::istream& ar_in) : m_in(ar_in) {}

Token TokenStream::get()
{
   if(m_full)
   {
      m_full = false;
      return m_buffer;
   }
   char ch;
   if(m_in >> ch)
   {
      switch(ch)
      {
      case '(':
      case ')':
      case '+':
      case '*':
         return Token{ch};
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      {
         m_in.putback(ch);
         Result val;
         m_in >> val;
         return Token{kNumber, val};
      }
      default:
         assert(false);
      }
   }
   else
   {
      return Token{kQuit};
   }
}
void TokenStream::putback(Token a_t)
{
   assert(!m_full);
   m_buffer = a_t;
   m_full   = true;
}

}  // namespace pkg
