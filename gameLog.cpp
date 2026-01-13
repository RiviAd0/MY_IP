#include <iostream>  //std::cin, std::cout
#include <vector>  //позволяет использовать std::vector
#include <string>  //для хранения чисел, введенных пользователем, и для возвращаемых значений std::string
#include <ctime>  //для генератора случайных чисел std::time
#include <fstream>  //для работы с файлами std::ofstream (game_log.txt для логирования)
#include <algorithm>  //для перемешивания цифр std::random_shuffle
#include <cstdlib>  //для генератора случайных чисел std::srand


#include "funct.h"

//логика игры против компьютера
void playGameAgainstComputer(int length, std::ofstream& logFile) {
    int attempts = 0;
    std::vector<std::string> history;
    bool guessed = false;

    std::string secret = generateSecretNumber(length);
    std::cout << "\nКомпьютер сгенерировал число.\nПопробуйте угадать!\n";

    while (!guessed) {
        std::string guess;
        std::cout << "\nВведите ваш вариант: ";
        std::cin >> guess;

        if (!validateGuess(guess, length)) {
            std::cout << "Некорректный ввод. Попробуйте еще раз.\n";
            continue;
        }

        attempts++;
        auto result = getBullsAndCows(secret, guess);
        std::cout << "Быки: " << result.first << ", Коровы: " << result.second << "\n";

        // Логирование
        std::string logEntry = "Попытка " + std::to_string(attempts) + ": " + guess +
            " | Быки: " + std::to_string(result.first) +
            ", Коровы: " + std::to_string(result.second);
        logFile << logEntry << std::endl;
        history.push_back(logEntry);

        if (result.first == length) {
            std::cout << "\nПоздравляем! Вы угадали число " << secret << " за " << attempts << " попыток.\n";
            logFile << "Победа за " << attempts << " попыток.\n";
            guessed = true;
        }
    }
}



void playGameTwoPlayers(int length, std::ofstream& logFile) {
    std::string player1Secret, player2Secret;
    int attemptsPlayer1 = 0, attemptsPlayer2 = 0;

    // Ввод загадываемых чисел обоими игроками
    std::cout << "\nИгрок 1, введите число длины " << length << ": ";
    std::cin >> player1Secret;
    while (!validateGuess(player1Secret, length)) {
        std::cout << "Некорректный ввод. Попробуйте еще раз: ";
        std::cin >> player1Secret;
    }

    std::cout << "\n ||\n ||\n ||\n\nНе дайте другому игроку подглядеть ваше число!\n";
    std::cout << "\n ||       /\\_/\\\n";
    std::cout << " ||      ( > < )\n";
    std::cout << " ||       /   \\\n";


    std::cout << "\nИгрок 2, введите число длины " << length << ": ";
    std::cin >> player2Secret;
    while (!validateGuess(player2Secret, length)) {
        std::cout << "Некорректный ввод. Попробуйте еще раз: ";
        std::cin >> player2Secret;
    }

    std::cout << "\n ||\n ||\n ||\n\nНе дайте другому игроку подглядеть ваше число!\n";
    std::cout << "\n ||       /\\_/\\\n";
    std::cout << " ||      ( > < )\n";
    std::cout << " ||       /   \\\n";

    bool player1Guessed = false, player2Guessed = false;
    int winnerAttemptCount = -1; // -1 означает, что победитель еще не определен

    while (!(player1Guessed && player2Guessed)) {
        // Ход игрока 2 - отгадывает число игрока 1
        if (!player2Guessed) {
            std::string guess;
            std::cout << "\n==============ход игрока 2==============";
            std::cout << "\nИгрок 2, введите ваш вариант отгадки для числа игрока 1: ";
            std::cin >> guess;
            if (!validateGuess(guess, length)) {
                std::cout << "Некорректный ввод. Попробуйте еще раз.\n";
                continue;
            }
            attemptsPlayer2++;
            auto result = getBullsAndCows(player1Secret, guess);
            std::cout << "Быки: " << result.first << ", Коровы: " << result.second << "\n";

            // Логирование
            logFile << "Игрок 2 попытка " << attemptsPlayer2 << ": " << guess
                << " | Быки: " << result.first
                << ", Коровы: " << result.second << "\n";

            if (result.first == length) {
                std::cout << "Игрок 2 угадал число игрока 1 за " << attemptsPlayer2 << " попыток.\n";
                player2Guessed = true;
                // Проверка на победу
                if (winnerAttemptCount == -1 || attemptsPlayer2 < winnerAttemptCount) {
                    winnerAttemptCount = attemptsPlayer2;
                }
            }
        }

        // Ход игрока 1 - отгадывает число игрока 2
        if (!player1Guessed) {
            std::string guess;
            std::cout << "\n==============ход игрока 1==============";
            std::cout << "\nИгрок 1, введите ваш вариант отгадки для числа игрока 2: ";
            std::cin >> guess;
            if (!validateGuess(guess, length)) {
                std::cout << "Некорректный ввод. Попробуйте еще раз.\n";
                continue;
            }
            attemptsPlayer1++;
            auto result = getBullsAndCows(player2Secret, guess);
            std::cout << "Быки: " << result.first << ", Коровы: " << result.second << "\n";

            // Логирование
            logFile << "Игрок 1 попытка " << attemptsPlayer1 << ": " << guess
                << " | Быки: " << result.first
                << ", Коровы: " << result.second << "\n";

            if (result.first == length) {
                std::cout << "Игрок 1 угадал число игрока 2 за " << attemptsPlayer1 << " попыток.\n";
                player1Guessed = true;
                // Проверка на победу
                if (winnerAttemptCount == -1 || attemptsPlayer1 < winnerAttemptCount) {
                    winnerAttemptCount = attemptsPlayer1;
                }
            }
        }

        // Проверка условий завершения
        if (player1Guessed && player2Guessed) {
            //оба угадали
            if (attemptsPlayer1 == attemptsPlayer2) {
                std::cout << "\nНичья!\n";
                logFile << "Игра завершилась ничьей.\n";
                break;
            }
            else if (attemptsPlayer1 < attemptsPlayer2) {
                std::cout << "Победил Игрок 1!\n";
                logFile << "Победитель: Игрок 1\n";
                break;
            }
            else {
                std::cout << "Победил Игрок 2!\n";
                logFile << "Победитель: Игрок 2\n";
                break;
            }
        }
        else if (player1Guessed && !player2Guessed) {
            // Игрок 1 уже угадал, а игрок 2 еще нет
            std::cout << "\nПобедил Игрок 1!\n";
            logFile << "Игра окончена: победил Игрок 1.\n";
            break;
        }
        else if (player2Guessed && !player1Guessed) {
            // Игрок 2 уже угадал, а игрок 1 еще нет
            std::cout << "\nПобедил Игрок 2!\n";
            logFile << "Игра окончена: победил Игрок 2.\n";
            break;
        }
    }
}