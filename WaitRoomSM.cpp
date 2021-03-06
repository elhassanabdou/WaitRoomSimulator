#include <iostream>
#include "simulator.h"
using namespace std;

int main(int argc, char **argv) {
	accent::Simulator simulator_;
	simulator_.run();
	//The code will never stop becasue the simulator destructor waiting for join
	return 0;
}
