/*
* Created by Zeng Yinuo, 2021.08.26
*/

#include "Md5Encryption.h"
#include "Math.h"

static constexpr int KA = 0x67452301;
static constexpr int KB = 0xefcdab89;
static constexpr int KC = 0x98badcfe;
static constexpr int KD = 0x10325476;

static constexpr int BIT_OF_BYTE = 8;
static constexpr int BIT_OF_GROUP = 512;
static constexpr int SRC_DATA_LENGTH = 64;
static constexpr int MD5_LENGTH = 32;

#define DEF_F(X, Y, Z) ((((X) & (Y)) | ((~X) & (Z))))
#define DEF_G(X, Y, Z) (((X) & (Z)) | ((Y) & (~Z)))
#define DEF_H(X, Y, Z) ((X) ^ (Y) ^ (Z))
#define DEF_I(X, Y, Z) ((Y) ^ ((X) | (~Z)))

std::string Osmmd::Md5Encryption::Encode(const std::string& bytes) const
{
    DynamicParam param{};

    param.ua = KA;
    param.ub = KB;
    param.uc = KC;
    param.ud = KD;

    param.vaLast = KA;
    param.vbLast = KB;
    param.vcLast = KC;
    param.vdLast = KD;

    std::string result;

    const char* data = bytes.c_str();
    char* output = nullptr;

    int totalType = this->FillData(data, bytes.size(), &output);
    char* dataBitOfGroup = output;

    for (int i = 0; i < totalType / (BIT_OF_GROUP / BIT_OF_BYTE); i++)
    {
        char* dataBitOfGroup = output;
        dataBitOfGroup += i * (BIT_OF_GROUP / BIT_OF_BYTE);
        this->Rotation(dataBitOfGroup, param);
    }

    if (output != nullptr)
    {
        delete[] output;
        output = nullptr;
    }

    result.append(GetHex(param.ua));
    result.append(GetHex(param.ub));
    result.append(GetHex(param.uc));
    result.append(GetHex(param.ud));

    return result;
}

uint32_t Osmmd::Md5Encryption::CycleMoveLeft(uint32_t number, int bitsToMove) const
{
    uint32_t number1 = number, number2 = number;

    if (bitsToMove <= 0)
    {
        return number;
    }

    return (number1 << bitsToMove) | (number2 >> (MD5_LENGTH - bitsToMove));
}

uint32_t Osmmd::Md5Encryption::FillData(const char* data, int length, char** output) const
{
    int bitNumber = length * BIT_OF_BYTE;
    int groupNumber = bitNumber / BIT_OF_GROUP;
    int modBitNumber = bitNumber % BIT_OF_GROUP;

    int bitNeedFill = 0;

    if (modBitNumber > (BIT_OF_GROUP - SRC_DATA_LENGTH))
    {
        bitNeedFill = BIT_OF_GROUP - modBitNumber;
        bitNeedFill += BIT_OF_GROUP - SRC_DATA_LENGTH;
    } else
    {
        bitNeedFill = BIT_OF_GROUP - SRC_DATA_LENGTH - modBitNumber;
    }

    int allBits = bitNumber + bitNeedFill;
    int outputLength = allBits / BIT_OF_BYTE + SRC_DATA_LENGTH / BIT_OF_BYTE;

    if (bitNeedFill > 0)
    {
        (*output) = new char[outputLength];
        memset(*output, 0, outputLength);
        memcpy(*output, data, length);

        unsigned char* temp = reinterpret_cast<unsigned char*>(*output);
        temp += length;
        (*temp) = 0x80;

        unsigned long long* origin = reinterpret_cast<unsigned long long*>((*output) + ((allBits / BIT_OF_BYTE)));
        (*origin) = static_cast<unsigned long long>(length) * BIT_OF_BYTE;
    }

    return outputLength;
}

void Osmmd::Md5Encryption::RoundF(char* data, DynamicParam& param) const
{
    uint32_t* M = reinterpret_cast<uint32_t*>(data);
    int s[] = { 7, 12, 17, 22 };
}

void Osmmd::Md5Encryption::RoundG(char* data, DynamicParam& param) const
{
}

void Osmmd::Md5Encryption::RoundH(char* data, DynamicParam& param) const
{
}

void Osmmd::Md5Encryption::RoundI(char* data, DynamicParam& param) const
{
}

void Osmmd::Md5Encryption::Rotation(char* data, DynamicParam& param) const
{
    if (data == nullptr)
    {
        return;
    }

    this->RoundF(data, param);
    this->RoundG(data, param);
    this->RoundH(data, param);
    this->RoundI(data, param);

    param.ua += param.vaLast;
    param.ub += param.vbLast;
    param.uc += param.vcLast;
    param.ud += param.vdLast;

    param.vaLast = param.ua;
    param.vbLast = param.ub;
    param.vcLast = param.uc;
    param.vdLast = param.ud;
}
