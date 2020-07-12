#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace BTWE
{
    class File
    {
        private:
            FILE        *file;

        public:
            std::string fileName;
            int         fileSize;


            /* Methods */
            File(std::string fileName);

            u_int8_t  readU8 (int i);
            u_int16_t readU16(int i);
            u_int32_t readU32(int i);

            int8_t    readS8 (int i);
            int16_t   readS16(int i);
            int32_t   readS32(int i);

            float     readF32(int i);

            std::string readString(int i, int j);
    };
}