#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include <cstddef>

/**
 * `GenericContainer` interface.
 */
template <typename T> class GenericContainer {
public:
    /**
     * Should add the specified value to the container
     * and return the number of items in the container after the addition.
     */
    virtual size_t Add(T value) = 0;

    /**
     * Should attempt to remove the specified value from the container.
     * If the value is present in the container, remove it and
     * return true; otherwise, return false.
     */
    virtual bool Delete(T value) = 0;

    virtual ~GenericContainer() = default;
};

#endif // CONTAINER_HPP_
