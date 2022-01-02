template<class ...Fs>
struct overload : Fs ... {
    template<class ...Ts>
    overload(Ts &&...ts) : Fs{std::forward<Ts>(ts)}... {}

    using Fs::operator()...;
};

template<class ...Ts>
overload(Ts &&...) -> overload<std::remove_reference_t<Ts>...>;


struct Pair;
using Element = std::variant<int, std::unique_ptr<Pair>>;
struct Pair {
    Element x;
    Element y;
};

std::ostream &operator<<(std::ostream &os, const Pair &pair) {
    auto visitor = overload(
            [&os](int i) { os << i; },
            [&os](std::unique_ptr<Pair> const &p) { os << *p; });

    os << '[';
    std::visit(visitor, pair.x);
    os << ',';
    std::visit(visitor, pair.y);
    os << ']';
    return os;
}


int main() {
    Pair pair{1, 2};
    std::cout << pair << '\n';
}
