#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <queue>
#include <stdexcept>
#include <memory>
#include <atomic>
#include <thread>

//TODO: not threadsafe
namespace cpp {
namespace utils {

template <typename T>
class ObjectPool
{
    public:
        ObjectPool(size_t chunkSize = kDefaultChunkSize)
            throw(std::invalid_argument, std::bad_alloc);
        std::shared_ptr<T> acquireObject();
        void releaseObject(std::shared_ptr<T> obj);

    project:
        std::queue<std::shared_ptr<T> > mFreeList;
        size_t mChunkSize;
        static const size_t kDefaultChunkSize = 10;
        void allocateChunk();

    private:
        ObjectPool(const ObjectPool<T>& src);
        ObjectPool<T>& operator=(const ObjectPool<T>&& rhs);
};

} // namespace utils
} // namespace cpp

#endif // _OBJECT_POOL_H_

/* vim set ts=4 sts=4 sw=4 tw=100 et */ 
