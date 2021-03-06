#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "parqueue.h"
#include <array>
#include "task.h"
#include "counter.h"
#include <cstddef>
#include <thread>
#include "logger.h"

#include"ticket.h"
namespace accent{
class Simulator {
public:
	Simulator();
	~Simulator();
	void run();

protected:
	void triggerAticket();
	void triggerClose() noexcept;
	void SimulatorArrival()noexcept;
	void updateLogger();
	void setLogger();

private:
	using DataType = Ticket;
	using parQueueType = tempDS::parQueue<DataType>;
	static constexpr std::size_t COUNTERCOUNT=3;
	std::array<parQueueType,std::size(accent::Task::TaskTypes)>m_Queues;
	//std::array<accent::Counter<DataType>,COUNTERCOUNT> m_Counters;
	accent::Counter<DataType> m_Counters[COUNTERCOUNT];
	static std::size_t ticketsCounter;

	std::thread m_CustomerThread;
	std::array<std::thread,Simulator::COUNTERCOUNT> m_CounterThreads;
	std::thread m_CustomerCloseThread;
	accentlog::CLogger m_logger;
};

}

#endif /* SIMULATOR_H_ */
