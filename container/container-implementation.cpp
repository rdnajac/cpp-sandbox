#include "container-implementation.hpp"

// Adds an item to the container and returns the new size.
template <typename T>
size_t GenericContainerImpl<T>::Add(T value) {
    container_.push_back(value);
    return container_.size();
}

// Deletes an item from the container, returns true if successful.
template <typename T>
bool GenericContainerImpl<T>::Delete(T value) {
    auto it = std::find(container_.begin(), container_.end(), value);
    if (it != container_.end()) {
        container_.erase(it);
        return true;
    }
    return false;
}

// Explicit instantiation (optional, if you want to define specific types)
template class GenericContainerImpl<int>;
template class GenericContainerImpl<float>;
template class GenericContainerImpl<double>;
