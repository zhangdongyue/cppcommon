#include "object_pool.h"

namespace cpp {
namespace utils {

template <typename T>
const size_t ObjectPool<T>::kDefaultChunkSize;

template <typename T>
ObjectPool<T>::ObjectPool(size_t chunkSize)
    throw(std::invalid_argument, std::bad_alloc)
{
    if (chunkSize == 0) {
        throw std::invalid_argument("chunk size must be positive");
    }

    mChunkSize = chunkSize;
    allocateChunk();
}

template <typename T>
void ObjectPool<T>::allocateChunk()
{
    for (size_t i = 0; i< mChunkSize; ++i) {
        mFreeList.push(std::make_shared<T>());
    }
}

template <typename T>
std::shared_ptr<T> ObjectPool<T>::acquireObject()
{
    if (mFreeList.empty()) {
        allocateChunk();
    }

    auto obj = mFreeList.front();
    mFreeList.pop();
    return obj;
}

template <typename T>
void ObjectPool<T>::releaseObject(std::shared_ptr<T> obj)
{
    mFreeList.push(obj);
}

} // namespace utils
} // namespace cpp

/* vim set ts=4 sts=4 sw=4 tw=100 et */ 
