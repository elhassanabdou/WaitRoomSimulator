/*
 * ticket.h
 *
 *  Created on: Mar 3, 2021
 *      Author: elhassan
 */

#ifndef TICKET_H_
#define TICKET_H_

#include "task.h"
#include <utility>
#include <ostream>

namespace accent{
class Ticket {
public:
	explicit Ticket(int,accent::Task::tasktypeArr task_);
	explicit Ticket(std::pair<unsigned int,accent::Task::tasktypeArr>&& ticket_);
	Ticket(const Ticket& ticket_);
	Ticket(Ticket&& ticket_);
	virtual ~Ticket()=default;
	accent::Task::tasktypeArr getTaskType()const noexcept{return m_ticketNumber.second;}
	unsigned int getTicketNumber()const noexcept {return m_ticketNumber.first;}
	friend std::ostream& operator<< (std::ostream& stream_, const Ticket ticket_){
    	return stream_<<ticket_.getTaskType()<<" "<<std::to_string(ticket_.getTicketNumber());
}
private:
	std::pair<unsigned int,accent::Task::tasktypeArr> m_ticketNumber;
};

}

#endif /* TICKET_H_ */
