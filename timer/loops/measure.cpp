#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>

using namespace std;

int main()
{
	random_device rd;
	mt19937 mt(rd());
	const int SIZE = 100'000'000;
	//const int SIZE = numeric_limits<int>::max(); 
	vector<int> v;
	uniform_int_distribution<int> dist(numeric_limits<int>::min(), numeric_limits<int>::max());
	for (int i = 0; i < SIZE; i++) 
		v.push_back(dist(mt));

	chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();
	chrono::high_resolution_clock::time_point end_time = chrono::high_resolution_clock::now();

	long long sum1, sum2, sum3,sum4, sum5;
	sum1 = sum2 = sum3 = sum4 = sum5 = 0;

	/* Measuremets */
	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < SIZE; i++) { sum1 += v[i]; }
	end_time = chrono::high_resolution_clock::now();
	auto duration1 = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
	cout << left <<setw(16) << sum1 << setw(32) << " C-style for-loop:"             << duration1.count() << " ms\n";

	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < v.size(); i++) { sum2 += v[i]; }
	end_time = chrono::high_resolution_clock::now();
	auto duration2 = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
	cout << left <<setw(16) << sum2 << setw(32) << " C-style for-loop (unsigned): " << duration2.count() << " ms\n";

	start_time = chrono::high_resolution_clock::now();
	for (int n : v) { sum3 += n; }
	end_time = chrono::high_resolution_clock::now();
	auto duration3 = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
	cout << left <<setw(16) << sum3 << setw(32) << " ranged for-loop "              << duration3.count() << " ms\n";

	start_time = chrono::high_resolution_clock::now();
	for_each(v.begin(), v.end(), [&sum4](int n) { sum4 += n; });
	end_time = chrono::high_resolution_clock::now();
	auto duration4 = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
	cout << left <<setw(16) << sum4 << setw(32) << " for_each() with a lambda"      << duration4.count() << " ms\n";

	start_time = chrono::high_resolution_clock::now();
	sum5 = accumulate(v.begin(), v.end(), static_cast<long long>(0));
	end_time = chrono::high_resolution_clock::now();
	auto duration5 = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
	cout << left <<setw(16) << sum5 << setw(32) << " std::accumulate()"             << duration5.count() << " ms\n";

	return 0;
}
