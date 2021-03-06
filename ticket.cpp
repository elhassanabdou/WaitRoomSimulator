/*
 * ticket.cpp
 *
 *  Created on: Mar 3, 2021
 *      Author: elhassan
 */

#include "ticket.h"
namespace accent{
Ticket::Ticket( int num,accent::Task::tasktypeArr task_):
m_ticketNumber(num,task_){
}
Ticket:: Ticket(std::pair<unsigned int,accent::Task::tasktypeArr>&& ticket_):m_ticketNumber(ticket_){

}
Ticket::Ticket(const Ticket& ticket_){
    m_ticketNumber=ticket_.m_ticketNumber;
}
Ticket::Ticket(Ticket&& ticket_){
    m_ticketNumber=std::move(ticket_.m_ticketNumber);
}

}


