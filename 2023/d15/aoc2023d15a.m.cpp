// https://adventofcode.com/2023/day/15

namespace {
    template<typename T>
    using InIter = std::istream_iterator<T>;
    namespace r4s = std::ranges;

    struct Hash {
        std::string str;

        friend std::istream& operator>>(std::istream& in, Hash& h) {
            h.str.clear();
            for (;;)
                switch (auto ch = in.get()) {
                    default:
                        h.str.push_back(static_cast<char>(ch));
                        break;
                    case ',':
                        [[unlikely]] case '\n':
                        [[unlikely]] case std::ios::traits_type::eof(): goto done;
                }
        done:
            if (in.eof() && !h.str.empty()) in.clear();
            return in;
        }
    };

    unsigned getHash(std::string_view str) {
        unsigned value{};
        for (unsigned char const c: str) {
            value += c;
            value *= 17u;
            value %= 256u;
        }
        std::cout << str << " becomes " << value << '\n';
        return value;
    }
}

int main([[maybe_unused]] int argc, char* argv[]) {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    auto sum = std::accumulate(InIter<Hash>{ifs}, {}, unsigned{}, [](auto acc, Hash const& h) {
        return acc + getHash(h.str);
    });


    std::cout << "Result is " << sum << '\n';

    return EXIT_SUCCESS;
}
