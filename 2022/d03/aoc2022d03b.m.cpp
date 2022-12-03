int main()
{
   using std::string;
   std::ifstream ifs("../input.txt");
   assert(ifs);
   int sum{};
   for(std::array<string, 3> line; getline(ifs, line[0]) and
                                   getline(ifs, line[1]) and
                                   getline(ifs, line[2]);)
   {
      namespace r4s = std::ranges;
      r4s::for_each(line, r4s::sort);
      string comm01;
      r4s::set_intersection(line[0], line[1], back_inserter(comm01));
      string common;
      r4s::set_intersection(line[2], comm01, back_inserter(common));
      char badge = common.front();
      if(std::islower(static_cast<unsigned char>(badge)))
         sum += badge - 'a' + 1;
      else
         sum += badge - 'A' + 27;
   }
   std::cout << sum << '\n';
   return EXIT_SUCCESS;
}
