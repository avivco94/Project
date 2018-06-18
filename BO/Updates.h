#pragma once
#include <mutex>
#include <shared_mutex>
#include <deque>
#include <functional>

class Request;
class Response;

//Manage thread-safe deque
template <typename T, typename S = Request>
class Updates {
	public:
		static Updates& getInstance();
		void add(T gu);
		void iterateAndPop(std::function<void(const T& gu)> f);
		bool empty();
		const T& front();
		void pop();
		T& operator[](int index);
		unsigned int size();
		void clear();
	private:
		std::shared_mutex m_mutex;
		Updates();
		~Updates();
		std::deque<T> m_updates;
};

template <typename T, typename S>
Updates<T, S>::Updates() {}
template <typename T, typename S>
Updates<T, S>::~Updates() {}

template <typename T, typename S>
Updates<T, S>& Updates<T, S>::getInstance() {
	static Updates instance;
	return instance;
}

template <typename T, typename S>
void Updates<T, S>::add(T gu) {
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_updates.push_back(gu);
}

template <typename T, typename S>
void Updates<T, S>::iterateAndPop(std::function<void(const T& gu)> f) {
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	while (!m_updates.empty()) {
		f(m_updates.front());
		m_updates.pop_front();
	}
}

template <typename T, typename S>
bool Updates<T, S>::empty() {
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_updates.empty();
}

template <typename T, typename S>
const T& Updates<T, S>::front() {
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_updates.front();
	
}
template <typename T, typename S>
void Updates<T, S>::pop() {
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_updates.pop_front();
}

template <typename T, typename S>
T& Updates<T, S>::operator[](int index) {
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_updates[index];
}

template <typename T, typename S>
unsigned int Updates<T, S>::size() {
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return (unsigned int)m_updates.size();
}

template <typename T, typename S>
void Updates<T, S>::clear() {
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_updates.clear();
}