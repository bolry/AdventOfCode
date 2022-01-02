#include <istream>

enum class Reg : char {
    w = 'w', x = 'x', y = 'y', z = 'z',
};

struct Instruction {

    enum class Type {
        inp, add, mul, div, mod, eql,
    };
    Type type;
    Reg opA;
    std::variant<std::monostate, Reg, int> opB;

    friend std::istream &operator>>(std::istream &is, Instruction &instruction) {
        std::string inst;
        is >> instruction.type >> instruction.opA >> instruction.opB;
        return is;
    }
};

int main(int argc, char *argv[]) {
    assert(argc == 2 && "missing argument");
    std::ifstream ifs{argv[1]};
    assert(ifs && "unable to open file");
    Instruction instruction;
    while (ifs >> instruction);

}
