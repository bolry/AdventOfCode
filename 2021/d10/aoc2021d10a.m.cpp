#include <ostream>

using fmt::print;

struct Chunk {
    std::string ck;

    friend std::istream &operator>>(std::istream &in, Chunk &chunk) {
        std::getline(in, chunk.ck);
        return in;
    }
};

char missingStr(Chunk const &chunk) {
    std::stack<int, std::vector<int>> stack;
    for (auto ch: chunk.ck) {
        auto lastCh{stack.empty() ? '\0' : stack.top()};
        switch (ch) {
            case '(':
            case '[':
            case '{':
            case '<':
                stack.push(ch);
                break;
            case ')':
                if (lastCh != '(') return ch;
                stack.pop();
                break;
            case ']':
                if (lastCh != '[') return ch;
                stack.pop();
                break;
            case '}':
                if (lastCh != '{') return ch;
                stack.pop();
                break;
            case '>':
                if (lastCh != '<') return ch;
                stack.pop();
                break;
            default:
                assert(false);
        }
    }
    return '\0';
}

int syntaxErrorScore(Chunk const &chunk) {
    switch (missingStr(chunk)) {
        case ')':
            return 3;
        case ']' :
            return 57;
        case '}':
            return 1197;
        case '>':
            return 25137;
        default:
            return 0;
    }
}

int main() {
    std::ifstream ifs{"../input.txt"};
    print("total syntax error score {}\n",
          std::accumulate(std::istream_iterator<Chunk>{ifs}, {}, 0,
                          [](auto a, auto const &b) { return a + syntaxErrorScore(b); }));
}
