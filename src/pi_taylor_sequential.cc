#include <iomanip>
#include <iostream>
#include <limits>
#include <cmath>
#include <chrono>
#include <array>

using namespace std;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

// Allow to change the floating point type
using my_float = long double;

/**
 * Computes Pi value using Taylor's approximation from 0 to `steps`
 *
 *
 * @param steps The amount of steps to compute
 * @return The Taylor approximation of Pi from 0 to n, with n=`steps`
 */
my_float pi_taylor(size_t steps) {
	my_float result = 0;
	int sign=1.;
	for (size_t n = 0; n < steps; n++) {
		result += sign/(2.*n+1.);
		sign=-sign;
	}
	return 4 * result;
}

int main(int argc, const char *argv[]) {

	// read the number of steps from the command line
	if (argc < 2) {
		std::cerr << "Invalid syntax: pi_taylor <steps>" << std::endl;
		std::cerr << "If <steps> is 0 then tests with {16, 128, 1024, 1048576, 4294967295} steps will be executed"
				  << std::endl;
		exit(1);
	}
	size_t steps = std::stoll(argv[1]);
	string EXEC_MODE;

	if(steps == 0) {
		std::array<size_t, 5> stepsArr = {16, 128, 1024, 1048576, 4294967295};
		std::array<double, 5> timesArr;
		for (size_t t = 0; t < stepsArr.size(); t++) {
			auto t1 = high_resolution_clock::now();
			pi_taylor(stepsArr[t]);
			auto t2 = high_resolution_clock::now();
			duration<double, std::milli> ms_double = t2 - t1;
			timesArr[t] = ms_double.count();
			
			std::cout << stepsArr[t] << "steps: " << timesArr[t] << "\t\t"
					  << timesArr[t]/stepsArr[t] << " ms every step" << endl;
		}
	}
	else {

		auto t1 = high_resolution_clock::now();
		auto pi = pi_taylor(steps);
		auto t2 = high_resolution_clock::now();
		duration<double, std::milli> ms_double = t2 - t1;
		//Time in ms: ms_double.count();
		std::cout << "For " << steps << ", pi value: "
			<< std::setprecision(std::numeric_limits<my_float>::digits10 + 1)
			<< pi << std::endl;
	}
}
