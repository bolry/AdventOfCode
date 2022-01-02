namespace rs = std::ranges;

int main() {
    std::ifstream ifs{"../inputSmall.txt"};
    assert(ifs && "cant open file");
    std::string imgEnhAlgo;
    std::getline(ifs, imgEnhAlgo);
    assert(imgEnhAlgo.size() == 512);
    rs::for_each(imgEnhAlgo, [](char &ch) { ch = ch == '#' ? '\1' : '\0'; });

    using Row = std::map<int, bool>;
    using Image = std::map<int, Row>;

}
