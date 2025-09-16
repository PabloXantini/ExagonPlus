#ifndef PLATFORM_INTERFACE_HPP
#define PLATFORM_INTERFACE_HPP

#include <iostream>

class IPlatform {
    public:
        IPlatform() = default;
        virtual ~IPlatform() = default;
        virtual void setupGraphicsAPI(std::string& api_name, unsigned int major_version, unsigned int minor_version) = 0;

};

#endif