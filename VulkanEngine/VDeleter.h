#pragma once

#include <functional>

template <typename T>
class VDeleter
{
public:
	VDeleter() : VDeleter([](T, VkAllocationCallbacks*) {}) {}	//default constructor

	VDeleter(std::function<void(T, VkAllocationCallbacks*)> deleteF)
	{
		this->deleter = [=](T obj) { deleteF(obj, nullptr); };	//default capture set to copy, obj param to delete
	}

	VDeleter(const VDeleter<VkInstance>& instance, std::function<void(VkInstance, T, VkAllocationCallbacks*)> deleteF)
	{
		this->deleter = [=, &instance](T obj) { deleteF(instance, obj, nullptr); };	//default capture set to copy with explicit ref for instance, obj param to delete
	}

	VDeleter(const VDeleter<VkDevice>& device, std::function<void(VkDevice, T, VkAllocationCallbacks*)> deleteF)
	{
		this->deleter = [=, &device](T obj) { deleteF(device, obj, nullptr); };	//default capture set to copy with explicit ref for device, obj param to delete
	}

	~VDeleter()
	{
		cleanup();
	}

	const T* operator &() const	//const ref to object to prevent modifying
	{
		return &object;
	}

	T* Replace()	//cleanup current object and return non const ref
	{
		Cleanup();
		return &object;
	}

	operator T() const
	{
		return object;
	}

	void operator=(T rhs)	//assignment op
	{
		if(rhs != object)
		{
			cleanup();
			object = rhs;
		}
	}

	template<typename V>
	bool operator==(V rhs)
	{
		return object == T(rhs);
	}

private:
	T object{ VK_NULL_HANDLE };
	std::function<void(T)> deleter;

	void Cleanup()
	{
		if(object != VK_NULL_HANDLE)
		{
			deleter(object);
		}
		object = VK_NULL_HANDLE;
	}
};

