#include <cassert>
#include <cstdint>
#include <iostream>

namespace
{
using Int = std::int_fast64_t;

constexpr Int kDiv{20201227};
constexpr Int kSubjectNumber{7};

/*constexpr*/ Int transform(Int const subjectNumber, Int loopSize) noexcept
{
   Int val{1};
   for(; loopSize; --loopSize)
   {
      val *= subjectNumber;
      val %= kDiv;
   }
   return val;
}

/*constexpr*/ Int findLoopSize(Int publicKey) noexcept
{
   Int loopSize{};
   for(Int val{1}; val != publicKey; val *= kSubjectNumber, val %= kDiv)
      ++loopSize;
   return loopSize;
}

}  // namespace

int main()
{
   constexpr Int cardPublicKey{3248366};
   /*constexpr*/ Int const cardLoopSize = findLoopSize(cardPublicKey);
   std::cout << "Card loop size is " << cardLoopSize << std::endl;

   constexpr Int doorPublicKey{4738476};
   /*constexpr*/ Int const doorLoopSize = findLoopSize(doorPublicKey);
   std::cout << "Door loop size is " << doorLoopSize << '\n';

   /*constexpr*/ Int const calcCardPublicKey = transform(
      kSubjectNumber, cardLoopSize);
   assert(calcCardPublicKey == cardPublicKey);
   std::cout << "Card public key " << calcCardPublicKey << '\n';

   /*constexpr*/ Int const calcDoorPublicKey = transform(
      kSubjectNumber, doorLoopSize);
   assert(calcDoorPublicKey == doorPublicKey);
   std::cout << "Door public key " << calcDoorPublicKey << '\n';

   /*constexpr*/ Int const cardEncryptionKey = transform(
      calcDoorPublicKey, cardLoopSize);
   std::cout << "Public key as known to card: " << cardEncryptionKey << '\n';

   /*constexpr*/ Int const doorEncryptionKey = transform(
      calcCardPublicKey, doorLoopSize);
   std::cout << "Public key as known to door: " << doorEncryptionKey << '\n';

   assert(cardEncryptionKey == doorEncryptionKey);
}
