#ifndef PLATFORM_INTERFACE_HPP
#define PLATFORM_INTERFACE_HPP

#include <iostream>

class IPlatform{
    protected:
        /* data */
    public:
        IPlatform() = default;
        virtual ~IPlatform() = default;
        virtual bool configure() = 0;
};

#endif