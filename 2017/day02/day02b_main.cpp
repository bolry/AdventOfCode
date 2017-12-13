#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main() {
    auto checksum = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream str(line);
        std::vector<int> nums;
        std::copy(std::istream_iterator<int>(str), std::istream_iterator<int>(), std::back_inserter(nums));
        std::sort(begin(nums), end(nums));
        auto const last = nums.size();
        for (auto i = last - last; i != last; ++i) {
            for (auto j = i + 1U; j != last; ++j) {
                if (nums[j] % nums[i] == 0) {
                    checksum += nums[j] / nums[i];
                    goto double_loop_escape;
                }
            }
        }
        double_loop_escape:;
    }
    std::cout << "The checksum is " << checksum << '\n';
}