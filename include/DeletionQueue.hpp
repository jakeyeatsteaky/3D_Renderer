#ifndef DELETION_QUEUE_HPP
#define DELETION_QUEUE_HPP

#include <functional>
#include <deque>

class DeletionQueue
{
public:

	void PushFunction(std::function<void()>&& function);
	void Flush(); 

private:
	std::deque<std::function<void()>> m_deletionFunctions;
};

#endif // !DELETION_QUEUE_HPP
