#ifndef CONTAINER_IMPLEMENTATION_HPP_
#define CONTAINER_IMPLEMENTATION_HPP_

#include "container.hpp"
#include <algorithm>
#include <vector>

template <typename T> class GenericContainerImpl : public GenericContainer<T> {
public:
    // Adds an item to the container and returns the new size.
    size_t Add(T value) override;

    // Deletes an item from the container, returns true if successful.
    bool Delete(T value) override;

    ~GenericContainerImpl() override = default;

private:
    std::vector<T> container_; // Underlying container to store items.
};

#endif // CONTAINER_IMPLEMENTATION_HPP_
