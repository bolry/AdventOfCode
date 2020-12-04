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
using namespace std::string_view_literals;

struct Record
{
   std::string birthYear;
   std::string issueYear;
   std::string expirationYear;
   std::string height;
   std::string hairColor;
   std::string eyeColor;
   std::string passportID;
   std::string countryID;
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
      if(!os && record != Record{})
      {
         os.clear();
      }
      return os;
   }
   friend bool operator==(const Record& lhs, const Record& rhs)
   {
      return lhs.birthYear == rhs.birthYear && lhs.issueYear == rhs.issueYear &&
             lhs.expirationYear == rhs.expirationYear &&
             lhs.height == rhs.height && lhs.hairColor == rhs.hairColor &&
             lhs.eyeColor == rhs.eyeColor && lhs.passportID == rhs.passportID &&
             lhs.countryID == rhs.countryID;
   }
   friend bool operator!=(const Record& lhs, const Record& rhs)
   {
      return !(rhs == lhs);
   }
};
bool isValidPassport(Record const& record)
{
   return !record.birthYear.empty() && !record.issueYear.empty() &&
          !record.expirationYear.empty() && !record.height.empty() &&
          !record.hairColor.empty() && !record.eyeColor.empty() &&
          !record.passportID.empty();
}
bool hasValidBirthYear(Record const& r)
{
   std::istringstream iss(r.birthYear.substr(4));
   int year{};
   iss >> year;
   return 1920 <= year && year <= 2002;
}
bool hadValidIssueYear(Record const& r)
{
   std::istringstream iss(r.issueYear.substr(4));
   int year{};
   iss >> year;
   return 2010 <= year && year <= 2020;
}
bool hasValidExpirationYear(Record const& r)
{
   std::istringstream iss(r.expirationYear.substr(4));
   int year{};
   iss >> year;
   return 2020 <= year && year <= 2030;
}
bool hasValidHeight(Record const& r)
{
   std::istringstream iss(r.height.substr(4));
   int height{};
   std::string type;
   iss >> height >> type;
   if(type == "cm"sv && 150 <= height && height <= 193)
      return true;
   if(type == "in"sv && 59 <= height && height <= 76)
      return true;
   return false;
}
bool hasValidHairColor(Record const& r)
{
   auto const& h = r.hairColor;
   return h.length() == 11 && h[4] == '#' &&
          h.find_first_not_of("0123456789abcdef", 5) == std::string::npos;
}
bool hasValidEyeColor(Record const& r)
{
   std::array<std::string_view, 7> constexpr okColor{
      "amb"sv, "blu"sv, "brn"sv, "gry"sv, "grn"sv, "hzl"sv, "oth"sv};
   return std::ranges::find(okColor, r.eyeColor.substr(4)) != cend(okColor);
}
bool hasValidPassportID(Record const& r)
{
   auto const& p = r.passportID;
   return p.length() == 13 &&
          p.find_first_not_of("0123456789", 4) == std::string::npos;
}
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   auto nrValidPasswords = std::count_if(
      std::istream_iterator<Record>(in),
      std::istream_iterator<Record>(),
      [](auto const& r) {
         return isValidPassport(r) && hasValidBirthYear(r) &&
                hasValidExpirationYear(r) && hasValidEyeColor(r) &&
                hasValidHairColor(r) && hasValidHeight(r) &&
                hasValidPassportID(r) && hadValidIssueYear(r);
      });
   std::cout << "Found " << nrValidPasswords << " valid passwords\n"
             << std::flush;
   return EXIT_SUCCESS;
}
