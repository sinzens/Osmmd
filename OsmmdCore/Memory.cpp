/*
* Created by Zeng Yinuo, 2021.08.23
* Edited by Zeng Yinuo, 2021.09.08
*/

#include "Memory.h"

Bytes Osmmd::ReadAllBytesFromFile(std::ifstream& reader)
{
    std::filebuf* buffer = reader.rdbuf();

    long long size = buffer->pubseekoff(0, std::ios::end, std::ios::in);
    buffer->pubseekpos(0, std::ios::in);

    char* data = new char[size];
    buffer->sgetn(data, size);

    reader.close();

    Bytes bytes(data, data + size);

    delete[] data;
    
    return bytes;
}

void Osmmd::WriteAllBytesToFile(std::ofstream& writer, const Bytes& bytes)
{
    writer.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    writer.close();
}
