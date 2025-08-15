#ifndef CONTEXT_GL_MANAGER_HPP
#define CONTEXT_GL_MANAGER_HPP

#include <vector>

class ContextManager {
    private:
        unsigned int shared_context_ptr = 0;
        unsigned int context_ptr = 0;
        //<Context ID | Shared ID>
        std::pair<unsigned int, unsigned int> currentContextID = {0, 0};
    public:
        ContextManager() = default;
        ~ContextManager() = default;
        const unsigned int getCurrentContextID() const {
            return this->currentContextID.first;
        }
        const unsigned int getCurrentSharedContextID() const {
            return this->currentContextID.second;
        }
        const unsigned int getLastContext() const {
            return this->context_ptr;
        }
        const unsigned int getLastSharedContext() const {
            return this->shared_context_ptr;
        }
        void registerNewContext(){
            this->context_ptr++;
        }
        void registerNewSharedContext(){
            this->shared_context_ptr++;
        }
        void setCurrentContext(unsigned int ID, unsigned int ShareID){
            this->currentContextID = {ID, ShareID};
        }
};

#endif