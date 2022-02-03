#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

int Calculate(std::string& str, std::vector<std::pair<int, int>>& cards) {
    int sum{0};
    for (auto c : str) {
        if (cards[c - 'A'].second > 0) {
            sum += cards[c - 'A'].first;
            --cards[c - 'A'].second;
        } else {
            return 0;
        }
    }
    return sum;
}

int Calculate(std::vector<std::string>& strings, std::vector<std::pair<int, int>> cards, int mask) {
    int sum{0};
    if (mask == 0) {
        return 0;
    }
    for (size_t i = 0; i < strings.size(); ++i) {
        if ((1 << i) & mask) {
            if (auto v = Calculate(strings[i], cards)) {
                sum += v;
            } else {
                return 0;
            }
        }
    }
    return sum;
}

int Solve(std::vector<std::string>& strings, std::vector<std::pair<uint8_t, int>>& _cards) {
    for (auto& str : strings) {
        std::transform(str.begin(), str.end(), str.begin(), [](uint8_t c) -> uint8_t { return toupper(c); });
    }
    std::vector<std::pair<int, int>> cards{26, {0, 0}};
    for (auto& card : _cards) {
        cards[toupper(card.first - 'A')].first = card.second;
        ++cards[toupper(card.first) - 'A'].second;
    }
    int max{0};
    for (int i = 0; i < std::pow(strings.size(), 2); ++i) {
        auto tmp = Calculate(strings, cards, i);
        if (tmp > max) {
            max = tmp;
        }
    }

    return max;
}

int main() {
    std::vector<std::string> strings{std::string{"abc"}, std::string{"cat"}};
    std::vector<std::pair<uint8_t, int>> cards{{'A', 3}, {'A', 3}, {'B', 4}, {'T', 5}, {'C', 4}};
    Solve(strings, cards);
    std::cout << Solve(strings, cards) << "\n";
}
