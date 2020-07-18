#pragma once

#include "json.hpp"

using json = nlohmann::json;

namespace BTWE
{
    class Translations
    {
        public:
            json translations;
            Translations();

    };
}