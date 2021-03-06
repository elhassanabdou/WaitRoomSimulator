#pragma once
#include <array>
#include<string>
namespace accent{
class Task{
public:
	using tasktypeArr = char;
	static constexpr std::array<tasktypeArr,3> TaskTypes = {'A','B','C'};
};
}
