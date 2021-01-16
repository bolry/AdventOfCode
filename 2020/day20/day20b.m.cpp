#include <cstdint>

namespace
{
constexpr std::uint64_t rot90(std::uint64_t v)
{
   // https://stackoverflow.com/a/4140600/8854921
   // clang-format off
   v = (v & UINT64_C(0x0000'0000'0f0f'0f0f)) << 004 | (v & UINT64_C(0x0000'0000'f0f0'f0f0)) << 040 |
       (v & UINT64_C(0xf0f0'f0f0'0000'0000)) >> 004 | (v & UINT64_C(0x0f0f'0f0f'0000'0000)) >> 040;
   v = (v & UINT64_C(0x0000'3333'0000'3333)) << 002 | (v & UINT64_C(0x0000'cccc'0000'cccc)) << 020 |
       (v & UINT64_C(0xcccc'0000'cccc'0000)) >> 002 | (v & UINT64_C(0x3333'0000'3333'0000)) >> 020;
   v = (v & UINT64_C(0x0055'0055'0055'0055)) << 001 | (v & UINT64_C(0x00aa'00aa'00aa'00aa)) << 010 |
       (v & UINT64_C(0xaa00'aa00'aa00'aa00)) >> 001 | (v & UINT64_C(0x5500'5500'5500'5500)) >> 010;
   // clang-format on
   return v;
}
}  // namespace

int main()
{
   constexpr std::uint64_t v = UINT64_C(0x0100'0000'0000'0000);

   constexpr auto a = rot90(v);
   return a;
}
