#ifndef BUFFER_INTERFACE_HPP
#define BUFFER_INTERFACE_HPP

class Buffer {
    public:
        Buffer() = default;
        virtual ~Buffer() = default;
        virtual void updateSoftly() = 0;
        virtual void updateHardly() = 0;
        virtual void free() = 0;
};

#endif