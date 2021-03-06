#include<random>
#include <type_traits>

#ifndef RANDGENERATOR_H_
#define RANDGENERATOR_H_
namespace mathUtil{
template<typename T,typename ...Args>
T randomGen(Args... p){
	std::random_device rd;
	std::mt19937 generator(rd());

	if constexpr (std::is_integral<T>::value){
		std::uniform_int_distribution<int> dist(p...);
		return dist(generator);
	}


	else{
		std::uniform_real_distribution<float> dist(p...);
		return dist(generator);
	}


}
template<typename ...Args>
int possGen(Args... p){
	std::random_device rd;
	std::mt19937 generator(rd());
	std::poisson_distribution<> dist(p...);
	return dist(generator);
}

}

#endif /* RANDGENERATOR_H_ */
