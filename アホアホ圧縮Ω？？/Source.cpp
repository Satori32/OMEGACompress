#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

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
		}
		else {
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

std::vector<std::uint8_t> MemoryExproderEnc(const std::vector<std::uint8_t>& D) {
	std::vector<std::uint8_t> R;
	for (auto& o : D) {
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

template<class T>
std::tuple<bool, std::vector<T>, std::size_t> BlockSortingHEnc(std::vector<T>& D) {

	std::vector<std::vector<T>> V;

	for (std::size_t i = 0; i < D.size(); i++) {
		V.push_back(D);
		std::rotate(D.begin(), D.end() - 1, D.end());
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

std::vector<std::uint8_t> MakeVector(std::size_t N) {
	std::vector<std::uint8_t> R;
	for (std::size_t i = 0; i < N; i++) {
		R.push_back(i);
	}

	return R;
}


int main() {
	auto D = MakeVector(1024*3);
	auto X0 = MemoryExproderEnc(D);
	auto [b,Y0,P] = BlockSortingHEnc(X0);
	if (!b) { return 0; }
	auto R = RunLengthEnc<std::uint8_t>(Y0);
	std::cout <<D.size()<<"->"<< R.size() << std::endl;
	auto Z = RunLengthDec(R);
	auto Y1 = BlockSortingHDec(Z, P);
	auto X1 = MemoryExproderDec(Y1);

	if (D == X1) {
		std::cout << "True" << std::endl;
	}
	else {
		std::cout << "False" << std::endl;
	}

	return 0;
}