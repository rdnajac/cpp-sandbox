# Pointer to Implementation (PImpl)

Based on example from Code Signal practice question

## Problem

Given this header file:

```cpp
#ifndef INTEGER_CONTAINER_HPP_
#define INTEGER_CONTAINER_HPP_


/**
 * `IntegerContainer` interface.
 */
struct IntegerContainer {

  /**
   * Should add the specified integer `value` to the container
   * and return the number of integers in the container after the
   * addition.
   */
  virtual int Add(int value) {
    // Default implementation
    return 0;
  }

  /**
   * Should attempt to remove the specified integer `value` from
   * the container.
   * If the `value` is present in the container, remove it and
   * return `true`, otherwise, return `false`.
   */
  virtual bool Delete(int value) {
    // Default implementation
    return false;
  }

  virtual inline ~IntegerContainer() = 0;
};
IntegerContainer::~IntegerContainer() = default;

#endif  // INTEGER_CONTAINER_HPP_
```

### Implementation

```cpp
/* -------------------------- */
/* integer_container_impl.hpp */
#ifndef INTEGER_CONTAINER_IMPL_HPP_
#define INTEGER_CONTAINER_IMPL_HPP_

#include "integer_container.hpp"
#include <memory>

class IntegerContainerImpl : public IntegerContainer {
public:
    IntegerContainerImpl();
    ~IntegerContainerImpl() override;
    IntegerContainerImpl(const IntegerContainerImpl&) = delete;
    IntegerContainerImpl& operator=(const IntegerContainerImpl&) = delete;
    IntegerContainerImpl(IntegerContainerImpl&&);
    IntegerContainerImpl& operator=(IntegerContainerImpl&&);

    int Add(int value) override;
    bool Delete(int value) override;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

#endif // INTEGER_CONTAINER_IMPL_HPP_

/* -------------------------- */
/* integer_container_impl.cpp */
#include "integer_container_impl.hpp"
#include <vector>
#include <algorithm>

class IntegerContainerImpl::Impl {
public:
    int Add(int value) {
        container_.push_back(value);
        return container_.size();
    }

    bool Delete(int value) {
        auto it = std::find(container_.begin(), container_.end(), value);
        if (it != container_.end()) {
            container_.erase(it);
            return true;
        }
        return false;
    }

private:
    std::vector<int> container_;
};

IntegerContainerImpl::IntegerContainerImpl() : pImpl(std::make_unique<Impl>()) {}
IntegerContainerImpl::~IntegerContainerImpl() = default;
IntegerContainerImpl::IntegerContainerImpl(IntegerContainerImpl&&) = default;
IntegerContainerImpl& IntegerContainerImpl::operator=(IntegerContainerImpl&&) = default;

int IntegerContainerImpl::Add(int value) {
    return pImpl->Add(value);
}

bool IntegerContainerImpl::Delete(int value) {
    return pImpl->Delete(value);
}
```

### Alternative Implementation

Just define the functions like this:

```cpp
/* -------------------------- */
/* integer_container_impl.cpp */
#include "integer_container_impl.hpp"

int IntegerContainerImpl::Add(int value) {
    container_.push_back(value);
    return container_.size();
}

bool IntegerContainerImpl::Delete(int value) {
    auto it = std::find(container_.begin(), container_.end(), value);
    if (it != container_.end()) {
        container_.erase(it);
        return true;
    }
    return false;
}
```

## Level 2

Add support for calculating the median of the numbers stored in the container.

`std::optional<int> GetMedian()` — should return the median integer - the integer in the middle of the sequence after all integers stored in the container are sorted in ascending order. If the length of the sequence is even, the leftmost integer from the two middle integers should be returned. If the container is empty, this method should return std::nullopt.

```cpp
std::optional<int> IntegerContainerImpl::GetMedian() {
    if (pImpl->container_.empty()) {
        return std::nullopt;
    }

    std::vector<int> sorted = pImpl->container_;
    std::sort(sorted.begin(), sorted.end());

    if (sorted.size() % 2 == 0) {
        return sorted[sorted.size() / 2 - 1];
    }

    return sorted[sorted.size() / 2];
}
```
