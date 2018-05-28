#pragma once
#include <mutex>
#include <shared_mutex>
#include <deque>
#include <functional>
#include "GameUpdate.h"

template <typename T>
class Updates
{
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

template <typename T>
Updates<T>::Updates() {}
template <typename T>
Updates<T>::~Updates() {}

template <typename T>
Updates<T>& Updates<T>::getInstance() {
	static Updates instance;
	return instance;
}

template <typename T>
void Updates<T>::add(T gu) {
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_updates.push_back(gu);
}

template <typename T>
void Updates<T>::iterateAndPop(std::function<void(const T& gu)> f) {
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	while (!m_updates.empty()) {
		f(m_updates.front());
		m_updates.pop_front();
	}
}

template <typename T>
bool Updates<T>::empty() {
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_updates.empty();
}

template <typename T>
const T& Updates<T>::front() {
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_updates.front();
	
}
template <typename T>
void Updates<T>::pop() {
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_updates.pop_front();
}

template <typename T>
T& Updates<T>::operator[](int index) {
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_updates[index];
}

template <typename T>
unsigned int Updates<T>::size() {
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return (unsigned int)m_updates.size();
}

template <typename T>
void Updates<T>::clear() {
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_updates.clear();
}