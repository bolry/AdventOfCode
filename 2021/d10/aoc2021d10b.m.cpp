#include <ostream>

using fmt::print;

struct Chunk {
    std::string ck;

    friend std::istream &operator>>(std::istream &in, Chunk &chunk) {
        std::getline(in, chunk.ck);
        return in;
    }
};

bool isCorrupt(Chunk const &chunk) {
    std::stack<char, std::string> stack;
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
                if (lastCh != '(') return true;
                stack.pop();
                break;
            case ']':
                if (lastCh != '[') return true;
                stack.pop();
                break;
            case '}':
                if (lastCh != '{') return true;
                stack.pop();
                break;
            case '>':
                if (lastCh != '<') return true;
                stack.pop();
                break;
            default:
                assert(false);
        }
    }
    return false;
}

int calcScore(Chunk const &chunk) {
    std::stack<char, std::string> stack;
    for (auto ch: chunk.ck)
        switch (ch) {
            case '(':
            case '[':
            case '{':
            case '<':
                stack.push(ch);
                break;
            case ')':
            case ']':
            case '}':
            case '>':
                stack.pop();
                break;
            default:
                assert(false);
        };
    std::deque<char> remaining;
    while (!stack.empty())
        switch(stack.top()){
        case
    }
        return 0;
}

int main() {
    std::ifstream ifs{"../inputSmall.txt"};
    std::vector<Chunk> chunks;
    std::remove_copy_if(std::istream_iterator<Chunk>{ifs}, {},
                        std::back_inserter(chunks), isCorrupt);
    std::vector<int> scores;
    std::ranges::transform(chunks, std::back_inserter(scores), [](auto const &chunk) {
        return calcScore(chunk);
    });
    assert(scores.size() % 2 == 1);
    auto iter{std::next(scores.begin(), scores.size() / 2)};
    std::ranges::nth_element(scores, iter);
    print("Score {}\n", *iter);
}
