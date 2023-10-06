#pragma once
#include "IResource.h"
#include <future>

namespace Multi
{
    class ThreadableResource
    {
    public:
        void movePromise(std::promise<IResource*>&& promise) { m_promise = move(promise); };

    protected:
        std::promise<IResource*> m_promise;
    };
}

