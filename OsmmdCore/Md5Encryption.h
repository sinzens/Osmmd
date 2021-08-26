/*
* Created by Zeng Yinuo, 2021.08.26
*/

#pragma once

#include "IAsymmetricEncryption.h"

namespace Osmmd
{
    class OSMMD_CORE_API Md5Encryption : public IAsymmetricEncryption
    {
    public:
        std::string Encode(const std::string& bytes) const override;

    private:
        struct DynamicParam
        {
            uint32_t ua;
            uint32_t ub;
            uint32_t uc;
            uint32_t ud;

            uint32_t vaLast;
            uint32_t vbLast;
            uint32_t vcLast;
            uint32_t vdLast;
        };

        uint32_t CycleMoveLeft(uint32_t number, int bitsToMove) const;
        uint32_t FillData(const char* data, int length, char** output) const;
        
        void RoundF(char* data, DynamicParam& param) const;
        void RoundG(char* data, DynamicParam& param) const;
        void RoundH(char* data, DynamicParam& param) const;
        void RoundI(char* data, DynamicParam& param) const;

        void Rotation(char* data, DynamicParam& param) const;
    };
}
