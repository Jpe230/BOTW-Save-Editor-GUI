#pragma once

#include "File.hpp"
#include <string>
#include <map> 


namespace BTWE
{
    class SaveFileEditor
    {
        private:
            File saveFile;

            std::map<std::string, u_int64_t> offsets;
            std::map<std::string, u_int64_t> headers;

            std::map<u_int64_t, std::string> hashes;

            static const char* const VERSION [];
            static const         int HEADER  [];
            static const         int FILESIZE[];

            static const int SIZEARR;
            

            std::string ReadString   (int offset, int len = 8);
            std::string ReadString64 (int offset, int arrayIndex = -1);
            std::string ReadString256(int offset);
            std::string LoadItemName (int offset);

            bool        CheckValidity();
            
            void        GetOffsets(int index);
            void        InitHashes();

            void        LoadSaveFile();
            
            
        public:
            SaveFileEditor(std::string fileName);
            SaveFileEditor();

    };
}