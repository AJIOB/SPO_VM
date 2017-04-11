//
// Created by Alex on 07.04.2017.
//

#include <string>
#include "FindFuncs.h"

int ::FindFuncs::onlyFolders(const dirent *d)
{
    //non-zero return => selected

    if (!d)
    {
        return 0;
    }

    if (d->d_type != DT_DIR)
    {
        return 0;
    }

    if (d->d_name == std::string(".") || (d->d_name == std::string("..")))
    {
        return 0;
    }

    return 1;
}

int ::FindFuncs::onlyTextFiles(const dirent *d)
{
    //non-zero return => selected
    if (!d)
    {
        return 0;
    }

    std::string fName = d->d_name;
    std::string requiredExtension[] = {".txt", ".TXT"};
    if (fName.size() < requiredExtension[0].size())
    {
        return 0;
    }

    auto fExtension = fName.substr(fName.size() - requiredExtension[0].size(), requiredExtension[0].size());

    bool isTXT = (fExtension == requiredExtension[0]) || (fExtension == requiredExtension[1]);

    if ((d->d_type != DT_DIR) && (isTXT))
    {
        return 1;
    }

    return 0;
}
