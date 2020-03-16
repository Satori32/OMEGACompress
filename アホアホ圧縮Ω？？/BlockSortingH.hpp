#pragma once

#if !defined(BSH)
#define BSH

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <random>

//https://ja.wikipedia.org/wiki/ブロックソート
//High order Poor BlockSorting...

template<class T>
std::tuple<bool, std::vector<T>, std::size_t> BlockSortingHEnc(std::vector<T>& D) {

	std::vector<std::vector<T>> V;

	for (std::size_t i = 0; i < D.size(); i++) {
		V.push_back(D);
		std::rotate ( D.begin(), D.end() - 1, D.end());
	}

	std::stable_sort(V.begin(), V.end());

	auto it = std::find(V.begin(), V.end(), D);
	std::vector<T> R;
	for (auto& o : V) {
		R.push_back(o.back());
	}
	return { it != V.end(),R,std::distance(V.begin(),it) };

}

template<class T>
std::vector<T> BlockSortingHDec(std::vector<T>& In, std::size_t P) {
	std::vector<std::vector<T>> V(In.size());

	for (auto& o : V) {
		o.resize(In.size());
	}
	for (std::size_t i = 0; i < V.size(); i++) {
		for (std::size_t j = 0; j < In.size(); j++) {
			V[j].back() = In[j];
		}
		for (std::size_t j = 0; j < V.size(); j++) {
			std::rotate(V[j].begin(), V[j].end() - 1, V[j].end());
		}
		std::stable_sort(V.begin(), V.end());
	}

	return V[P];
}
std::vector<char> MakeCacao() {
	return {'c','a','c','a','o'};
}

std::vector<std::size_t> MakeVectorBSH(std::size_t N) {
	std::random_device rd;
	std::minstd_rand mr;
	std::uniform_int_distribution<std::size_t> ui(0, N);
	std::vector<std::size_t> R;
	for (std::size_t i = 0; i < N; i++) {
		R.push_back(ui(mr));
	}
	return R;
}
/** /
int main() {
	auto V = MakeVector(1024);
	//auto V = MakeCacao();

	auto [b, D, P] = BlockSortingHEnc(V);
	if (!b) { return -1; }

	auto R = BlockSortingHDec(D, P);

	if (V == R) {
		std::cout << "True" << std::endl;
	}
	else {
		std::cout << "False" << std::endl;
	}

	return 0;
}

/**/
#endif