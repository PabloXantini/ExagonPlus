#ifndef PLATFORM_INSTANCE_HPP
#define PLATFORM_INSTANCE_HPP

#include "Platform.hpp"
#include "../desktopGLFW/DesktopGLFW.hpp"

class Platform{
    private:
        IPlatform* pImpl;
    public:
        Platform();
        ~Platform();
        bool init();
        bool setup();
};

#endif