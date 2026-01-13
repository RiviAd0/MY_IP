#include <iostream>  //std::cin, std::cout
#include <vector>  //позволяет использовать std::vector
#include <string>  //для хранения чисел, введенных пользователем, и для возвращаемых значений std::string
#include <ctime>  //для генератора случайных чисел std::time
#include <fstream>  //для работы с файлами std::ofstream (game_log.txt для логирования)
#include <algorithm>  //для перемешивания цифр std::random_shuffle
#include <cstdlib>  //для генератора случайных чисел std::srand

#include "funct.h"

std::string getFileName() {
    std::string filename;
    std::cout << "Введите имя файла для логов с .txt: ";
    std::getline(std::cin, filename);
    return filename;
}

int main() {
    setlocale(LC_ALL, "ru");

    /*
    std::ofstream logFile("game_log+*.txt");
    if (!logFile.is_open()) {
        std::cerr << "Не удалось открыть файл.\n";
        return 1;
    }
    */
    std::string filename;
    std::ofstream logFile("game_log.txt");
    if (!logFile.is_open()) {
        std::cerr << "Не удалось открыть файл.\n";

        // Пока не откроется успешно
        while (true) {
            filename = getFileName();
            logFile.open(filename);
            if (logFile.is_open()) {
                break; // успешно открылся
            }
            else {
                std::cerr << "Не удалось открыть файл " << filename << ". Попробуйте снова.\n";
            }
        }
    }


    std::string title = "ИГРА \"БЫКИ И КОРОВЫ\"";
    int width = 40; //ширина рамки
    //верхняя рамка
    std::cout << std::string(width, '=') << "\n";
    //вычисление отступа для центрирования заголовка
    int padding = (width - title.size()) / 2;
    //заголовок по центру
    std::cout << std::string(padding, ' ') << title << std::string(width - padding - title.size(), ' ') << "\n";
    //нижняя рамка 
    std::cout << std::string(width, '=');
    

    int mode;
    do {
        std::string menu = "МЕНЮ ВЫБОРА";

        //верхняя рамка
        std::cout << "\n\n" << std::string(width, '=') << "\n";
        //вычисление отступа для центрирования меню
        int padding2 = (width - menu.size()) / 2;
        //меню по центру
        std::cout << std::string(padding2, ' ') << menu << std::string(width - padding2 - menu.size(), ' ') << "\n";

        std::cout << " 1. Начать игру против компьютера\n";
        std::cout << " 2. Начать игру на двух игроков\n";
        std::cout << " 3. Открыть правила игры\n";
        std::cout << " 0. Выход из игры\n";

        //нижняя рамка
        std::cout << std::string(width, '=') << "\n";

        while (true) {
            std::cout << "\nВведите номер вашего выбора: ";
            if (std::cin >> mode) {  //успешный ввод
                break;
            }
            else {
                std::cin.clear();  //очистка при ошибке
                while (std::cin.get() != '\n');  //игнорируем до следующего символа новой строки
                std::cout << "Ошибка! Пожалуйста, введите число.\n";
            }
        }

        switch (mode) {
        case 1: {
            int length = 4;
            char playAgain;

            std::cout << "\n";
            std::string gameRk = "ИГРА ПРОТИВ КОМПЬЮТЕРА";
            //верхняя рамка
            std::cout << std::string(width, '=') << "\n";
            //вычисление отступа для центрирования заголовка
            int padding = (width - gameRk.size()) / 2;
            //заголовок по центру
            std::cout << std::string(padding, ' ') << gameRk << std::string(width - padding - gameRk.size(), ' ') << "\n";
            //нижняя рамка 
            std::cout << std::string(width, '=');
            std::cout << "\n";

            do {
                playGameAgainstComputer(length, logFile);
                std::cout << "Хотите сыграть еще раз? (y/n): ";
                std::cin >> playAgain;

                while (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N') {
                    std::cout << "Некорректный ввод. Пожалуйста, введите 'y' для повторной игры или 'n' для выхода: ";
                    std::cin >> playAgain;
                }

                if (playAgain == 'n' || playAgain == 'N') {
                    break;
                }
            } while (true);
        }
              break;
        case 2: {
            int length = 4;
            char playAgain;

            std::string gameR2 = "ИГРА НА ДВУХ ИГРОКОВ";
            std::cout << "\n";
            //верхняя рамка
            std::cout << std::string(width, '=') << "\n";
            //вычисление отступа для центрирования заголовка
            int padding = (width - gameR2.size()) / 2;
            //заголовок по центру
            std::cout << std::string(padding, ' ') << gameR2 << std::string(width - padding - gameR2.size(), ' ') << "\n";
            //нижняя рамка 
            std::cout << std::string(width, '=');
            std::cout << "\n";

            do {
                playGameTwoPlayers(length, logFile);
                std::cout << "Хотите сыграть еще раз? (y/n): ";
                std::cin >> playAgain;

                while (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N') {
                    std::cout << "Некорректный ввод. Пожалуйста, введите 'y' для повторной игры или 'n' для выхода: ";
                    std::cin >> playAgain;
                }

                if (playAgain == 'n' || playAgain == 'N') {
                    break;
                }
            } while (true);
        }
              break;
        case 3: GameRules();
            break;
        case 0: {
            logFile.close();
            std::cout << "Игра завершена. Лог сохранен в game_log.txt.\n";
        }
            break;
        default: std::cout << "Некорректный выбор.\n";
            break;
        }
    } while (mode != 0);

    return 0;
}
