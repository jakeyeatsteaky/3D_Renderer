#include "DeletionQueue.hpp"

void DeletionQueue::PushFunction(std::function<void()>&& function)
{
	m_deletionFunctions.push_back(std::move(function));
}

void DeletionQueue::Flush()
{
	// Flush the queue in reverse order of which it was initialized

	for (std::deque<std::function<void()>>::reverse_iterator it = m_deletionFunctions.rbegin();
		it != m_deletionFunctions.rend(); 
		it++) {
		(*it)(); // call the function which was added to the deletion queue
	}
	
	m_deletionFunctions.clear();
}