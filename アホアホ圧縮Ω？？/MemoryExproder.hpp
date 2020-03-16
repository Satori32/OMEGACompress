#pragma once



#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>

//Memory Exproder Enc/Dec.

std::vector<std::uint8_t> MemoryExproderEnc(const std::vector<std::uint8_t>& D) {
	std::vector<std::uint8_t> R;
	for (auto& o: D) {
		for (std::size_t i = 0; i < std::numeric_limits<std::vector<std::uint8_t>::value_type>::digits; i++) {
			R.push_back((o & (1 << i)) ? 1 : 0);
		}
	}
	return R;
}
std::vector<std::uint8_t> MemoryExproderDec(const std::vector<std::uint8_t>& D) {
	std::vector<std::uint8_t> R;
	std::size_t L = std::numeric_limits<std::vector<std::uint8_t>::value_type>::digits;
	std::size_t i = 0;
	std::vector<std::uint8_t>::value_type N = 0;
	for (auto& o : D) {
		N |= (o << i);
		i++;
		if (i == L) {
			R.push_back(N);
			N = 0;
		}
		i %= L;
	}
	return R;
}

std::vector<std::uint8_t> MakeVector(std::size_t N) {
	std::vector<std::uint8_t> R;
	for (std::size_t i = 0; i < N; i++) {
		R.push_back(i);
	}

	return R;
}

/** /
int main() {
	auto D = MakeVector(128);
	auto X = MemoryExproderEnc(D);
	auto Y = MemoryExproderDec(X);

	if (D == Y) {
		std::cout << "True" << std::endl;
	}
	else {
		std::cout << "False" << std::endl;
	}

	return 0;
}
/**/