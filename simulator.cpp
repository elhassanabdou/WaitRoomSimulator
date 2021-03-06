#include "simulator.h"
#include "randgenerator.h"
#include <chrono>

namespace accent{

std::size_t Simulator::ticketsCounter =0;
Simulator::Simulator()
:m_logger("Simulator")
{
	//initialize the function
	for(int i =0;i<COUNTERCOUNT;++i){
		m_Counters[i].setSizeFunc(std::bind(&parQueueType::qSize, &m_Queues[i]));
		m_Counters[i].setFuncPop(std::bind(&parQueueType::pop, &m_Queues[i]));
		m_Counters[i]. setLogger(i);
	}
	setLogger();

}
void Simulator::setLogger(){
		std::string name("Simulator");
		m_logger = accentlog::CLogger(std::move(name));
	}
void Simulator::run(){
	m_CustomerThread = std::move(std::thread(&Simulator::SimulatorArrival,this));
	for(int i =0;i<COUNTERCOUNT;++i){
		m_CounterThreads[i]=std::move(std::thread(&accent::Counter<DataType>::popQueue,&m_Counters[i]));
	}
	m_CustomerCloseThread = std::move(std::thread(&Simulator::triggerClose,this));
}
Simulator::~Simulator(){
	m_CustomerThread.join();
	for( auto& t : m_CounterThreads)
		t.join();
}
void Simulator::SimulatorArrival()noexcept{
	while(true){
		const auto numClient= mathUtil::possGen(3);
		for(int i=0;i<numClient;++i)
			triggerAticket();
		updateLogger();
		std::this_thread::sleep_for(std::chrono::minutes(1));
	}
	
}
void Simulator::triggerAticket(){
	int taskNum = mathUtil::randomGen<int,int,int>(0,Simulator::COUNTERCOUNT-1);
	m_Queues[taskNum].push(accent::Ticket (Simulator::ticketsCounter,accent::Task::TaskTypes[taskNum]));
	++Simulator::ticketsCounter;
}
void Simulator:: triggerClose()noexcept{
	int counterToClose;
	while(true){
		std::this_thread::sleep_for(std::chrono::minutes(5));
		counterToClose = mathUtil::randomGen<int,int,int>(0,Simulator::COUNTERCOUNT-1);
		m_Counters[counterToClose].triggerCloseFlag();
	}
}
void Simulator::updateLogger(){
	m_logger<<"update";
	for(int i =0;i<COUNTERCOUNT;++i){
		m_logger<< std::to_string(m_Counters[i].servingCurrServingTime()*(m_Queues[i].qSize()+1));
	}
}
}


