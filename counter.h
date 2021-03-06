#ifndef COUNTER_H_
#define COUNTER_H_
#include <memory>
#include<utility>
#include <functional>
#include <thread>
#include "randgenerator.h"
#include<atomic>
#include<iostream>
#include<sstream>
#include"logger.h"
namespace accent{

template<typename D, typename ...Args>
class Counter {
public:
	Counter()
	: m_toClose(false)
	{	
		m_ServeTime.store(0);
	}
	void setLogger(int num){
		std::string name("Counter");
		name.append(std::to_string(num));
		m_logger = accentlog::CLogger(std::move(name));
	}

	bool isClose()const noexcept{
		return m_toClose.load();
	}
	void triggerCloseFlag() noexcept{
		m_toClose.store(true);
	}
	void popQueue(Args... p){
		while(true){
			if(m_SizeFun()!=0 ){
					if(!m_toClose.load()){
						try{
							auto data = m_Fun(p...);
							std::ostringstream dataStrStream;
							dataStrStream<<data;
							std::string ll = dataStrStream.str();
							m_logger<<ll;
						}
						catch(std::string s){
							std::cout<<s;
						}
						//sleep to mimic work for 20 till 40 seconds
						m_ServeTime.store(mathUtil::randomGen<int,int,int>(20,60));
						auto l = m_ServeTime.load();
						std::this_thread::sleep_for(std::chrono::seconds(m_ServeTime.load()));
					}
					else{
						//sleep 5 minutes and then set m_toClose to false
						std::this_thread::sleep_for(std::chrono::minutes(5));
						m_toClose.store(false);
					}
				}
			else{
				std::this_thread::yield();
			}
		}

	}

	std::size_t servingCurrServingTime(){
		return m_ServeTime.load();
	}
	void setFuncPop(std::function<D(Args...)> fun_)noexcept{
		m_Fun = fun_;
	}
	void setSizeFunc(std::function<std::size_t()> sizeFun_)noexcept{
		m_SizeFun = sizeFun_;
	}

private:
	volatile std::atomic<bool> m_toClose;
	std::atomic<std::size_t> m_ServeTime;
	std::function<D(Args...)> m_Fun;
	std::function<std::size_t()> m_SizeFun;
	accentlog::CLogger m_logger;
};
}

#endif /* COUNTER_H_ */
