#include "headers/SaveFileEditor.hpp"

namespace BTWE{

    const char* const SaveFileEditor::HEADER[]   = {"v1.0", "v1.1", "v1.2", "v1.3", "v1.3.1", "Kiosk", "v1.3.3", "v1.3.4", "v1.4", "v1.5", "v1.5*", "v1.6", "v1.6*", "v1.6**", "v1.6***"};
    const int         SaveFileEditor::FILESIZE[] = {896976, 897160, 897112, 907824, 907824,   916576,  1020648,  1020648,  1027208,1027208,1027248, 1027216,1027216, 1027216 , 1027216};
    const int         SaveFileEditor::VERSION[]  = {0x24e2, 0x24ee, 0x2588, 0x29c0, 0x2a46,   0x2f8e,  0x3ef8,   0x3ef9,   0x471a, 0x471b, 0x471b,  0x471e, 0x0f423d,0x0f423e, 0x0f423f};

    SaveFileEditor::SaveFileEditor(std::string fileName) : saveFile(fileName)
    {
        std::string out = ReadString(342160 + 0 * 0x80, 16);
        int x = 0;
    }

    std::string SaveFileEditor::ReadString(int offset, int len)
    {
		std::string v = "";

		for(int i=0; i<len; i++)
        {
			v += saveFile.readString(offset,4);
			offset+=8;
		}

        //string cleanup
        v.erase(std::find(v.begin(), v.end(), '0'), v.end());

		return v;
    }

    std::string SaveFileEditor::ReadString64(int offset, int arrayIndex)
    {
        if(arrayIndex > -1)
            offset += 0x80 * arrayIndex;

        return ReadString(offset, 16);
    }
}

