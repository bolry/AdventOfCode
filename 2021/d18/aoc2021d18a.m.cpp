using fmt::print;
using fmt::format;
using namespace std;
using namespace literals;

auto findExplosionStart(string_view str) {
    int depth{};
    for (string_view::size_type i{}, e{str.size()}; i < e; ++i) {
        if (str[i] == '[') ++depth;
        else if (str[i] == ']') --depth;
        if (depth == 5) return i;
    }
    return string_view::npos;
}

void replaceRight(string &str, string::size_type pos, int y) {
    smatch numMatch;
    static regex const numRe{R"(\d+)"};
    if (regex_search(next(str.cbegin(), pos), str.cend(), numMatch, numRe))
        str.replace(pos + numMatch.position(), numMatch.length(), to_string(stoi(numMatch.str()) + y));
    // else print("No right match\n");
}

void replaceLeft(string &str, string::size_type pos, int x) {
    smatch numMatch;
    static regex const numRe{R"(.*(\d+))"};
    if (regex_search(str.cbegin(), next(str.cbegin(), pos), numMatch, numRe)) {
        assert(numMatch.size() == 2);
        str.replace(numMatch.position(1), numMatch.length(1), to_string(stoi(numMatch.str(1)) + x));
    } // else print("No left match\n");
}

bool explode(string &str) {
    auto pos = findExplosionStart(str);
    if (pos == string::npos) return false;
    int x, y;
    char comma;
    std::istringstream iss{str.substr(pos + 1)};
    iss >> x >> comma >> y;
    assert(iss);
    std::streamoff eatenChars{iss.tellg()};
    str.replace(pos, eatenChars + 2, 1, '0');
    replaceRight(str, pos + 1, y);
    replaceLeft(str, pos, x);
    return true;
}

bool split(string &str) {
    smatch numMatch;
    static regex const digitsRe{R"(\d{2,})"};
    if (!regex_search(str, numMatch, digitsRe)) return false;
    int num{stoi(numMatch.str())};
    // print("{} pos {} len {}\n", num, numMatch.position(), numMatch.length());
    auto spl = div(num, 2);
    int x = spl.quot; // round down
    int y = spl.quot + spl.rem; // round up
    str.replace(numMatch.position(), numMatch.length(), format("[{},{}]", x, y));
    return true;
}

void reduce(string &str) {
    for (;;) {
        while (explode(str));
        if (!split(str)) break;
    }
}

string add(string const &a, string const &b) {
    if(b.size() == 5)
        raise(SIGABRT);
    if (a.empty()) return b;
    return format("[{},{}]", a, b);
}

void magnitude(string &str) {
    smatch match;
    static regex const re{R"(\[(\d+),(\d+)\])"};
    while (regex_search(str, match, re)) {
        int x{stoi(match.str(1))};
        int y{stoi(match.str(2))};
        str.replace(match.position(), match.length(), to_string(3 * x + 2 * y));
    }
}

int main() {
    ifstream ifs{"../inputSmall.txt"};
    assert(ifs && "can't open file");
    auto sum = accumulate(istream_iterator<string>{ifs}, {}, ""s, [](auto const &a, auto const &b) {
        print("  {}\n+ {}\n", a, b);
        auto s = add(a, b);
        reduce(s);
        print("= {}\n\n", s);
        return s;
    });
    ifs.close();
    print("final `{}'\n", sum);
    print("magnitude of number `{}`", sum);
    magnitude(sum);
    print(" is {}\n", sum);
}