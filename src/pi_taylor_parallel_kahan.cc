#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using my_float = float;

void pi_taylor_chunk(std::vector<my_float> &output, size_t thread_id, size_t start_step, size_t stop_step) {
	my_float result = 0.0;
	my_float c = 0.0; // A running compensation for lost low-order bits
	my_float sign = 1.0; // Alternating sign

	for (size_t n = start_step; n < stop_step; n++) {
		my_float input = sign*1. / (2. * n + 1.); // Current term in the series with alternating sign

		// Kahan summation: Adjust input by subtracting the lost low-order bits
		my_float y = input - c; // Subtract correction term
		my_float t = result + y; // Add adjusted input to the result

		// Update the correction term
		c = (t - result) - y; // (t - result) gives the difference, subtracting and recovers the lost part

		// Update the result
		result = t;

		// Flip the sign for the next term
		sign = -sign;
	}

	// Store the final result for this chunk
	output[thread_id] = result;
}

my_float reduction(const std::vector<my_float> &output) {
	my_float result = 0.0;
	my_float c = 0.0; // A running compensation for lost low-order bits
	for (size_t n = 0; n < output.size(); n++) {
		my_float input = output[n];

		// Kahan summation: Adjust input by subtracting the lost low-order bits
		my_float y = input - c; // Subtract correction term
		my_float t = result + y; // Add adjusted input to the result

		// Update the correction term
		c = (t - result) - y; // (t - result) gives the difference, subtracting and recovers the lost part

		// Update the result
		result = t;

	}
    return result;
}

std::pair<size_t, size_t> usage(int argc, const char *argv[]) {
	// read the number of steps from the command line
	if (argc != 3) {
		std::cerr << "Invalid syntax: pi_taylor <steps> <threads>" << std::endl;
		exit(1);
	}

	size_t steps = std::stoll(argv[1]);
	size_t threads = std::stoll(argv[2]);

	if (steps < threads) {
		std::cerr << "The number of steps should be larger than the number of threads" << std::endl;
		exit(1);
	}
	return std::make_pair(steps, threads);
}

int main(int argc, const char *argv[]) {


	auto ret_pair = usage(argc, argv);
	auto steps = ret_pair.first;
	auto threads = ret_pair.second;

	my_float pi;
	std::vector<my_float> output(threads, 0);
	std::vector<std::thread> threads_(threads);
	size_t slice = steps / threads;

	for (size_t i = 0; i < threads; i++) {
		size_t start_step = i * slice;
		size_t end_step = (i + 1) * slice;
		threads_[i] = std::thread(pi_taylor_chunk, std::ref(output), i, start_step, end_step);
	}
	for (size_t i = 0; i < threads; i++) {
		if (threads_[i].joinable()) {
			threads_[i].join();
		}
	}
    pi=reduction(output);
	pi = 4. * pi;

	std::cout << "For " << steps << ", pi value: " << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
			  << pi << std::endl;
}
