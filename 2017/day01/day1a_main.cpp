#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>

int main(int argc, char*argv[])
{
try
{
	std::cout.exceptions(std::ios_base::badbit|std::ios_base::failbit|std::ios_base::eofbit);
	std::string indata;
	if(argc == 1)
	{
		std::cout << "Type your in data: ";
		std::cin >> indata;
		std::cout << '\n';
	}
	else if(argc == 2)
	{
		std::ifstream ifs;
		ifs.exceptions(std::ios_base::badbit|std::ios_base::failbit);
		ifs.open(argv[argc-1]);
		ifs >> indata;
	}

	auto const len = indata.size();
	auto const offset = 1;
	indata += indata.substr(0, offset);
	auto const beg = begin(indata);
	auto const sum = std::inner_product(beg, beg + len, beg + offset, 0,
		std::plus<int>(),
		[](char a, char b){
			return static_cast<int>(a - '0') * static_cast<int>(a == b);
		}
	); 
	std::cout << "Sum of data `" << indata.substr(0, len) << "'\n"
	          << "is " << sum << '\n';
	return EXIT_SUCCESS;
}
catch(std::bad_alloc const&)
{
	std::fputs("Sorry no more memory\n", stderr);
}
catch(std::exception const& x)
{
	std::cerr << "Got a exception: `" << x.what() << "'\n"
	<< "(Maybe you forgot to give correct filename?)\n";
}
catch(...)
{
	std::fputs("Unexpected exceptions happened\n", stderr);
}
return EXIT_FAILURE;
}
