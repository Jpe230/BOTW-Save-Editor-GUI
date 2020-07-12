#pragma once

#include "File.hpp"
#include <string>
#include <map> 

namespace BTWE
{
    class SaveFileEditor
    {
        private:
            static const char* const HEADER  [];
            static const int VERSION [];
            static const int FILESIZE[];
            

            std::string ReadString   (int offset, int len = 8);
            std::string ReadString64 (int offset, int arrayIndex = -1);
            std::string ReadString256(int offset);
            std::string LoadItemName (int offset);
            
            void        GetOffset();
            
            
        public:
            File saveFile;
            std::map<std::string, int> offsets;
            std::map<std::string, int> headers;
            SaveFileEditor(std::string fileName);

    };
}