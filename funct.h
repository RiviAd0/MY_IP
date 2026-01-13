#pragma once
#ifndef FUNCT_H
#define FUNCT_H
#include <string>  //для хранения чисел, введенных пользователем, и для возвращаемых значений std::string
#include <fstream>  //для работы с файлами std::ofstream (game_log.txt для логирования)

//логика игры против компьютера
void playGameAgainstComputer(int length, std::ofstream& logFile);

//логика игры двух игроков
void playGameTwoPlayers(int length, std::ofstream& logFile);


//генератор случайного числа для игры против компьютера
std::string generateSecretNumber(int length);

//подсчитывает количество быков и коров
std::pair<int, int> getBullsAndCows(const std::string& secret, const std::string& guess);

//проверяет, что введенная строка содержит только цифры и длина совпадает
bool validateGuess(const std::string& guess, int length);

//вывод правил игры
void GameRules();

#endif