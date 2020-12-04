#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace
{
struct Record
{
   std::string birthYear;
   std::string issueYear;
   std::string expirationYear;
   std::string height;
   std::string hairColor;
   std::string eyeColor;
   friend std::istream& operator>>(std::istream& os, Record& record)
   {
      Record res;
      std::string line;
      std::string field;
      while(std::getline(os, line))
      {
         if(line.empty())
         {
            break;
         }
         std::istringstream iss(line);
         while(iss >> field)
         {
            using namespace std::string_view_literals;
            if(field.starts_with("byr:"sv))
               res.birthYear = std::move(field);
            else if(field.starts_with("iyr:"sv))
               res.issueYear = std::move(field);
            else if(field.starts_with("eyr:"sv))
               res.expirationYear = std::move(field);
            else if(field.starts_with("hgt:"sv))
               res.height = std::move(field);
            else if(field.starts_with("hcl:"sv))
               res.hairColor = std::move(field);
            else if(field.starts_with("ecl:"sv))
               res.eyeColor = std::move(field);
            else if(field.starts_with("pid:"sv))
               res.passportID = std::move(field);
            else if(field.starts_with("cid:"sv))
               res.countryID = std::move(field);
            else
               assert(false);
         }
      }
      record = std::move(res);
      return os;
   }
   std::string passportID;
   std::string countryID;
};
bool isValidPassport(Record const& record)
{
   return !record.birthYear.empty() && !record.issueYear.empty() &&
          !record.expirationYear.empty() && !record.height.empty() &&
          !record.hairColor.empty() && !record.eyeColor.empty() &&
          !record.passportID.empty();
}
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   auto nrValidPasswords = std::count_if(
      std::istream_iterator<Record>(in),
      std::istream_iterator<Record>(),
      isValidPassport);
   std::cout << "Found " << nrValidPasswords << " valid passwords\n"
             << std::flush;
   return EXIT_SUCCESS;
}
