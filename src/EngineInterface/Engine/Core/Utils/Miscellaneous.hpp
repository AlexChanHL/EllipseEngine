#pragma once

#include "Math/Random/Random.hpp"


namespace Ellipse {

namespace Utils {

inline String generateRandomString(u64_t length) {
    String rand = "";
    for(u64_t i=0;i<length;i++) {
     rand.push_back(char(Ellipse::EllipseMath::randIntDist(97, 122)));
    }

    return rand;
}

} // namespace Utils

} // namespace Ellipse

