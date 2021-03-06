#include<queue>
#include <mutex>

namespace tempDS{
	template<typename T>
	class parQueue{
		public:
			T pop(){
				std::lock_guard<std::mutex>lock(m_mutex);
				if(m_Queue.empty())
					throw std::string("The queue is empty no work to do.");
				else{
					T mt(m_Queue.front());
					m_Queue.pop();
					return mt;
				}
			}
			void push(T&& data_){
				std::lock_guard<std::mutex>lock(m_mutex);
				m_Queue.push(data_);
			}
			std::size_t qSize(){
				std::lock_guard<std::mutex>lock(m_mutex);
				return m_Queue.size();
			}
		private:
			using atomQ = std::queue<T>;
			atomQ m_Queue;
			mutable std::mutex m_mutex;
	};
}