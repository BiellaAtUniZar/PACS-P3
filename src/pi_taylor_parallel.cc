#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using my_float = long double;

void pi_taylor_chunk(std::vector<my_float> &output,
					 size_t thread_id,
					 size_t start_step,
					 size_t stop_step) {
	my_float result = 0;
	float sign = 1.;
	for (size_t n = start_step; n < stop_step; n++) {
		result += sign / (2. * n + 1.);
		sign = -sign;
	}
	output[thread_id] = result;
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

	my_float pi = 0;

	std::vector<my_float> output(threads, 0);
	std::vector<std::thread> threads_(threads);
	size_t slice = steps / threads;
	for (size_t i = 0; i < threads; i++) {
		size_t start_step = i * slice;
		ssize_t end_step = (i == threads - 1) ? steps : (i + 1) * slice;
		threads_[i] = std::thread(pi_taylor_chunk, std::ref(output), i, start_step, end_step);
	}
	for (size_t i = 0; i < threads; i++) {
		if (threads_[i].joinable()) {
			threads_[i].join();
			pi += output[i];
		}
	}

	pi = 4 * pi;
	std::cout << "For " << steps
			  << ", pi value: " << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
			  << pi << std::endl;
}
