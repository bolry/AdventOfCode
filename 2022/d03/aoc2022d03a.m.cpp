int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);
   int sum{};
   for(std::string line; std::getline(ifs, line);)
   {
      auto const sz = line.size() / 2u;
      std::span<char> left(line.data(), sz);
      std::span<char> right(line.data() + sz, sz);
      std::ranges::sort(left);
      std::ranges::sort(right);
      char commonItem;
      std::ranges::set_intersection(left, right, &commonItem);

      if(std::islower(static_cast<unsigned char>(commonItem)))
         sum += commonItem - 'a' + 1;
      else
         sum += commonItem - 'A' + 27;
   }
   std::cout << sum << '\n';
   return EXIT_SUCCESS;
}
