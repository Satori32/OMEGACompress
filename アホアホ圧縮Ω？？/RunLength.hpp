#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <cstdint>
#include <tuple>

template<class T> using Pair = std::tuple<T, std::size_t>;
template<class T> using PType = std::vector<Pair<T>>;

template<class T>
PType<T> RunLengthEnc(const std::vector<std::uint8_t>& D) {
	T Ch(D.front());
	std::size_t N = 1;

	PType<T> R;

	for (std::size_t i = 1; i < D.size(); i++) {
		if (D[i] != Ch) {
			R.push_back({ Ch,N });

			Ch = D[i];
			N = 1;
		}else{
			N++;

		}
	}
	R.push_back({ Ch,N }); 
	
	return R;
}

template<class T>
 std::vector<std::uint8_t> RunLengthDec(PType<T>& In) {
	std::vector<std::uint8_t> R;
	for (auto& o : In) {
		for (std::size_t i = 0; i < std::get<1>(o); i++) {
			R.push_back(std::get<0>(o));
		}
	}

	return R;
}

std::vector<std::uint8_t> MakeVectorRL(std::size_t N, unsigned int S = 0) {
	std::vector<std::uint8_t> R;
	std::minstd_rand mr(S);
	std::uniform_int_distribution<std::uint16_t> ui(0, 3);

	for (std::size_t i = 0; i < N; i++) {
		R.push_back(ui(mr));
	}

	return R;
}

/** /
int main() {
	for (unsigned int i = 0; i < 128; i++) {
		auto D = MakeVectorRL(128,i);
		auto X = RunLengthEnc<std::uint8_t>(D);
		auto R = RunLengthDec<std::uint8_t>(X);

		if (D == R) {
			std::cout << "True" << std::endl;
		}
		else {
			std::cout << "False" << std::endl;
		}
	}

	return 0;
}
/**/