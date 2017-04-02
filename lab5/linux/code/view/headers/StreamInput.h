#ifndef STREAM_INPUT
#define STREAM_INPUT

#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <conio.h>
#endif

#include "StreamOutput.h"
#include "../../exceptions/AllExceptions.h"

namespace Stream {
    void Clear();

    template<typename InputType>
    InputType Input();

    template<typename InputType>
    void Input(InputType &elem);

    char Get();

    char GetOnlyYN(const std::string &infoText);

#ifdef _WIN32
    std::string Getpass(const char *prompt, bool show_asterisk = true);
#endif

    template<typename InputType>
    InputType InputInRange(const std::string &shownText, const InputType &min, const InputType &max);

#define AJIOB_END_OF_LINE '\n'

//cpp part 1. inline

    inline void Clear() {
        std::cin.clear();

        std::streambuf *tmp = std::cin.rdbuf();

        while (tmp->in_avail() != 0) {
            //переход на следующий символ
            tmp->sbumpc();
        }
    }

    template<typename InputType>
    InputType Input() {
        InputType toReturn;

        while (true) {
            if (std::cin >> toReturn) {
                Clear();
                break;
            }
            PrintLine("Ошибка ввода. Пожалуйста, повторите ввод");
            Clear();
        }
        return toReturn;
    }

    template<typename InputType>
    void Input(InputType &elem) {
        elem = Input<InputType>();
    }

//for std::string
    template<>
    inline std::string Input() {
        std::string buffer;

        while (true) {
            char tmp = std::cin.get();

            if (tmp == AJIOB_END_OF_LINE) {
                break;
            }

            buffer.push_back(tmp);
        }

        return buffer;
    }
//end for std::string


    inline char Get() {
        /*
        char toReturn = std::cin.get();
        Clear();
        return toReturn;*/

        return Input<char>();
    }

    template<typename InputType>
    InputType InputInRange(const std::string &shownText, const InputType &min, const InputType &max) {
        if (min > max) {
            throw RangeException();
        }

        InputType buffer;
        while (true) {
            PrintLine(shownText);
            buffer = Input<InputType>();
            if ((buffer >= min) && (buffer <= max)) {
                break;
            }

            std::cout << "Извините, такого элемента нету. Пожалуйста, введите элемент из промежутка от " << min
                      << " до " << max << std::endl;
            PauseConsole();
            ClearConsole();
        }

        return buffer;
    }
}
#undef AJIOB_END_OF_LINE

#endif
