#include "headers/File.hpp"
#include <dirent.h> 

namespace BTWE
{
    File::File(std::string fileName)
    {
        
        file = fopen(fileName.c_str(), "r+b");

        /*Implement correct handler*/
        if(!file) {
            std::exit(0);
        }

        /*Get Size*/
        fseek(file, 0, SEEK_END); 
        fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

    }

    u_int8_t File::readU8 (int i)
    {
        u_int8_t v = 0;

        fseek(file, i, SEEK_SET);
        fread(&v,sizeof(u_int8_t),1,file);

        return (u_int8_t)v;
    }

    u_int16_t File::readU16(int i)
    {
        u_int16_t v = 0;

        fseek(file, i, SEEK_SET);
        fread(&v,sizeof(u_int16_t),1,file);

        return v;
    }

    u_int32_t File::readU32(int i)
    {
        u_int32_t v = 0;

        fseek(file, i, SEEK_SET);
        fread(&v,sizeof(v),1,file);

        return v;
    }

     int8_t File::readS8 (int i)
    {
        int8_t v = 0;

        fseek(file, i, SEEK_SET);
        fread(&v,sizeof(u_int8_t),1,file);

        return (u_int8_t)v;
    }

    int16_t File::readS16(int i)
    {
        int16_t v = 0;

        fseek(file, i, SEEK_SET);
        fread(&v,sizeof(u_int16_t),1,file);

        return v;
    }

    int32_t File::readS32(int i)
    {
        int32_t v = 0;

        fseek(file, i, SEEK_SET);
        fread(&v,sizeof(v),1,file);

        return v;
    }

    
    float File::readF32(int i)
    {
        float v = 0;

        fseek(file, i, SEEK_SET);
        fread(&v,sizeof(u_int32_t),1,file);

        return v;
    }

    std::string File::readString(int i, int j)
    {
        std::string v = "";

        for (int d = 0; d < j && i + d < fileSize; d++){
            char c;
            fseek(file, i+d, SEEK_SET);
            fread(&c,sizeof(c),1,file);
            v += c;
        }

        return v;
    } 
}

