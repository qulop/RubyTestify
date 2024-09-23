#include "Emoji.hpp"

#include <random>
#include <vector>


namespace Testify {
    size_t getRandomIndex(size_t max) {
        static std::mt19937 twister{ std::random_device{}() };

        return twister() % max;
    }

    std::string selectRandom(const std::vector<std::string>& variants) {
        size_t index = getRandomIndex(variants.size());

        return variants.at(index);
    }


    std::string getSuccessEmoji() {
        static const std::vector<std::string> variants = {
                "(≧◡≦)",
                "(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧",
                "(＾▽＾)",
                "(ﾉ^_^)ﾉ"
        };

        return selectRandom(variants);
    }

    std::string getFailureEmoji() {
        static const std::vector<std::string> variants = {
                "(╯︵╰,)",
                "(ಥ﹏ಥ)",
                "(ノಠ益ಠ)ノ",
                "(╬ಠ益ಠ)"
        };

        return selectRandom(variants);
    }
}