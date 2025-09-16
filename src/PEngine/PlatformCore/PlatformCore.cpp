#include "PlatformCore.hpp"

bool PlatformCore::init(std::string platform_name){
    if(platform_name=="desktop"){
        pImplementation = new CoreDesktopGLFW();
    }      
}