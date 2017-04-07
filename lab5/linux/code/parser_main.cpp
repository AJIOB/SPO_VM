//
// Created by alex on 02.04.17.
//

#include "model/ParserManager.h"
#include "exceptions/AllExceptions.h"
#include "view/headers/view.h"

int main(int argc, char ** argv) {
    //std::stringstream s;
    //s << "Hello! I'm parser. I work with " << argv[1] << " folder" << std::endl;
    //PrintLine(s.str());

    try {
        if (argc != 2)
        {
            throw BadCMDAgrsException(1);
        }

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
