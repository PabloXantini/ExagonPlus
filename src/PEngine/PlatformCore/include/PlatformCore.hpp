#ifndef PLATFORM_CORE_HPP
#define PLATFORM_CORE_HPP

#include "IPlatform.hpp"
#include "../DesktopGLFW/Instance.hpp"

#include <iostream>

class PlatformCore {
    private:
        IPlatform* pImplementation;
    public:
        PlatformCore() = default;
        ~PlatformCore() = default;
        bool init(std::string platform_name);
};

#endif