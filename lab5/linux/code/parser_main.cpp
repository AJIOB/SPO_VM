//
// Created by alex on 02.04.17.
//

#include <iostream>
#include <sstream>
#include "model/ParserManager.h"
#include "exceptions/AllExceptions.h"
#include "view/headers/view.h"

int main(int argc, char ** argv) {
    if (argc != 2)
    {
        return 1;
    }

    std::stringstream s;
    s << "Hello! I'm parser. I work with " << argv[1] << " folder" << std::endl;
    PrintLine(s.str());

    try {
        ParserManager r(argv[1]);
        r.run();
    }
    catch (VA_Exception& e)
    {
        PrintError(e.what());
        PrintLine("Для выхода введите любой символ");
        Stream::Get();
        return 2;
    }
    catch (...)
    {
        PrintError("We have some error");
        Stream::Get();
        return 1;
    }

    return 0;
}
