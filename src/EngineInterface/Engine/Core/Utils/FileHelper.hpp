
#include "Core/Base.hpp"


namespace Ellipse {

namespace Utils {

inline String getFile(String path) {
    String fileName = "";
    u64_t lastDirectoryIndex = 0;
    for(u64_t i=0;i<path.size();i++) {
     if(path[i] == '/') {
      lastDirectoryIndex = i + 1;
     }
    }

    fileName = path.substr(lastDirectoryIndex, (path.size() - lastDirectoryIndex));
    
    return fileName;
}

inline String getExt(String file) {
    String ext = "";
    u64_t firstExt = 0;
    for(u64_t i=0;i<file.size();i++) {
     if(file[i] == '.') {
      firstExt = i + 1;
      break;
     }
    }

    ext = file.substr(firstExt, (file.size() - firstExt));
    
    return ext;
}

inline String getFileName(String path) {
    String fileName = "";
    fileName = getFile(path);
    
    String ext = "";
    u64_t firstExt = 0;
    for(u64_t i=0;i<fileName.size();i++) {
     if(fileName[i] == '.') {
      firstExt = i;
      break;
     }
    }

    fileName = fileName.substr(0, firstExt);
    
    return fileName;
}

}    // namespace Utils

}    // namespace Ellipse

