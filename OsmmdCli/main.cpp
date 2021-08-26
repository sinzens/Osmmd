/*
* Created by Zeng Yinuo, 2021.08.23
*/

#include "Cli.h"

int main(int argc, char* argv[])
{
    return Osmmd::Cli::Init(argc, argv).Run();
}