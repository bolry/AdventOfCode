#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/md5.h>

int main()
{
   CryptoPP::Weak::MD5 hash;
   using namespace std::literals;
   auto const& msgStart = "ckczppom"s;
   std::string digest;
   digest.resize(hash.DigestSize());
   std::string klartext;
   CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(klartext));
   for(std::uintmax_t i = 0; i < UINTMAX_MAX; ++i)
   {
      std::string msg(msgStart + std::to_string(i));
      digest.clear();
      CryptoPP::StringSource(
         msg,
         true,
         new CryptoPP::HashFilter(
            hash, new CryptoPP::StringSink(digest), false, 3));
      klartext.clear();
      CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));
      if(klartext.starts_with("00000"sv))
      {
         std::cout << "Message: " << msg << '\n';
         std::cout << "Digest: " << klartext << '\n';
         break;
      }
   }
   std::cout << std::endl;
   return EXIT_SUCCESS;
}
