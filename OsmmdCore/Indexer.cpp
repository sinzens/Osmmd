/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "Indexer.h"
#include "StringConstants.h"

std::shared_ptr<Osmmd::IndexResult> Osmmd::Indexer::DuplicateKeyResult(const std::string& value)
{
    char buffer[100]{};
    sprintf_s(buffer, "%s [%s]", StringConstants::Error.COMMAND_DUPLICATE_KEY, value.c_str());

    return std::make_shared<IndexResult>(0, 0, buffer);
}
