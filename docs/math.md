# Math in C++

## They're just for loops

### Summation

$$
\sum_{i=0}^{N} 2x_i
$$

```cpp
for (int i = 0; i < N; i++) {
    sum += 2 * x[i];
}
```

### Product

$$
\prod_{i=1}^{N} x_i
$$

```cpp
for (int i = 1; i <= N; i++) {
    product *= x[i];
}
```

## Standard Deviation

The formula for standard deviation (σ) is given by:

$$
\sigma = \sqrt{\frac{1}{N} \sum_{i=1}^{N} (x_i - \mu)^2}
$$

where _mu_ is the mean of the elements, $x_i$ represents each element,
and $N$ is the total number of elements.

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

int main() {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    double sum = std::accumulate(data.begin(), data.end(), 0.0);  // make sure we use 0.0 for double
    double average = sum / data.size();
    double sq_sum = std::accumulate(data.begin(), data.end(), 0.0, [average](double acc, double x) {
        double diff = x - average;
        return acc + diff * diff;
    });
    double stdev = std::sqrt(sq_sum / data.size());

    // Standard scaling using for_each
    std::for_each(data.begin(), data.end(), [average, stdev](double &val) {
        val = (val - average) / stdev;
    });

    // Output the scaled vector
    for (const auto &val : data) {
        std::cout << val << " ";
    }
    std::cout << '\n'; // Expected output: {-1.41421, -0.707107, 0, 0.707107, 1.41421}

    return 0;
}
```

# Weighted Mean

```cpp
#include <iostream>
#include <vector>
#include <numeric>  // For std::accumulate

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};
    std::vector<int> weights = {1, 3, 2, 1, 1};

    int weighted_sum = std::accumulate(data.begin(), data.end(), 0, [&weights, i = 0](int sum, int val) mutable {
        return sum + val * weights[i++];
    });

    // Calculate the sum of weights using std::accumulate
    double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);

    // Calculate the weighted average be dividing the weighted sum by the total weight
    double weighted_avg = weighted_sum / sum_of_weights;

    std::cout << "Weighted Average: " << weighted_avg << '\n'; // Expected output: 2.75
    return 0;
}
```
