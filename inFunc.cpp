#include <iostream>  //std::cin, std::cout
#include <vector>  //позвол€ет использовать std::vector
#include <string>  //дл€ хранени€ чисел, введенных пользователем, и дл€ возвращаемых значений std::string
#include <ctime>  //дл€ генератора случайных чисел std::time
#include <fstream>  //дл€ работы с файлами std::ofstream (game_log.txt дл€ логировани€)
#include <algorithm>  //дл€ перемешивани€ цифр std::random_shuffle
#include <cstdlib>  //дл€ генератора случайных чисел std::srand

#include "funct.h"

//генератор случайного числа дл€ игры против компьютера
std::string generateSecretNumber(int length) {
    std::vector<char> digits = { '0','1','2','3','4','5','6','7','8','9' };
    std::string secret;
    std::srand(std::time(nullptr));
    std::random_shuffle(digits.begin(), digits.end());

    for (int i = 0; i < length; ++i) {
        secret += digits[i];
    }
    return secret;
}

//подсчитывает количество быков и коров
std::pair<int, int> getBullsAndCows(const std::string& secret, const std::string& guess) {
    int bulls = 0, cows = 0;
    std::vector<bool> secret_used(secret.size(), false);
    std::vector<bool> guess_used(guess.size(), false);

    //подсчет быков
    for (int i = 0; i < secret.size(); ++i) {
        if (secret[i] == guess[i]) {
            bulls++;
            secret_used[i] = true;
            guess_used[i] = true;
        }
    }

    //подсчет коров
    for (int i = 0; i < secret.size(); ++i) {
        if (guess_used[i]) continue;
        for (int j = 0; j < secret.size(); ++j) {
            if (secret_used[j]) continue;
            if (guess[i] == secret[j]) {
                cows++;
                secret_used[j] = true;
                break;
            }
        }
    }
    return { bulls, cows };
}

//провер€ет, что введенна€ строка содержит только цифры и длина совпадает
bool validateGuess(const std::string& guess, int length) {
    if (guess.length() != length)
        return false;
    for (char c : guess) {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}