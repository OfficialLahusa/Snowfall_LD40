#include <vector>

#include "../utils.h"

namespace sse
{
	template<typename T>
	T nextMultiple(T multipleOf, T value)
	{
		T multiple = value + multipleOf - 1;
		multiple -= (multiple % multipleOf);
		return multiple;
	}

	class StackAllocatorDestrctor
	{
	private:
		const void* m_data;
		void(*destructor)(const void*);

	public:
		template<typename T>
		explicit StackAllocatorDestrctor(const T& data)
			:m_data(std::addressof(data))
		{
			destructor = [](const void* lambdaData)
			{
				auto originalType = static_cast<const T*>(lambdaData);
				originalType->~T();
			};
		}

		void operator()()
		{
			destructor(m_data);
		}
	};

	class StackAllocatorMarker
	{
	public:
		byte* m_makerValue;
		size_t m_destructorHandle;

		StackAllocatorMarker(byte* makerValue, size_t destructorHandle)
			:m_makerValue(makerValue)
			, m_destructorHandle(destructorHandle)
		{

		}
	};

	//TODO: template the allocator
	class StackAllocator
	{
	private:
		static const size_t STACK_ALLOCATOR_DEFAULT_SIZE = 1024;
		byte* m_data = nullptr;
		byte* m_head = nullptr;
		size_t m_size = 0;

		std::vector<StackAllocatorDestrctor> destructors;

		template<typename T>
		inline typename std::enable_if<std::is_trivially_destructible<T>::value>::type
			addDestructorToList(T* object)
		{
			
		}

		template<typename T>
		inline typename std::enable_if<!std::is_trivially_destructible<T>::value>::type
			addDestructorToList(T* object)
		{
			destructors.push_back(StackAllocatorDestrctor(*object));
		}
	public:
		explicit StackAllocator(size_t size = STACK_ALLOCATOR_DEFAULT_SIZE)
			:m_size(size)
		{
			m_data = new byte[m_size];
			m_head = m_data;
		}

		~StackAllocator()
		{
			if (m_data != m_head)
			{
				logger::logError("In StackAllocator: Not all allocations were successfully deallocated!\n");
				DEBUG_BREAK
			}
			
			delete[] m_data;
			m_data = nullptr;
			m_head = nullptr;
		}

		StackAllocator(const StackAllocator& other) = delete; //copy constructor
		StackAllocator(StackAllocator&& other) = delete; //move constructor
		StackAllocator& operator=(const StackAllocator& other) = delete; //copy Assignment
		StackAllocator& operator=(StackAllocator&& other) = delete; //move Assignment

		void* allocate(size_t amountOfBytes, size_t alignment = 1)
		{
			byte* allocationLocation = (byte*)(nextMultiple(alignment, (size_t)m_head));
			byte* newHeadPointer = allocationLocation + amountOfBytes;
			if (newHeadPointer <= m_data + m_size)
			{
				m_head = newHeadPointer;
				return allocationLocation;
			}
			else
			{
				logger::logError("In StackAllocator: StackAllocator is full!\n");
				DEBUG_BREAK
					return nullptr;
			}
		}

		template<typename T, typename... arguments>
		T* allocateObject(size_t amountOfObjects = 1, arguments&&... args)
		{
			byte* allocationLocation = (byte*)nextMultiple(alignof(T), (size_t)m_head);
			byte* newHeadPointer = allocationLocation + amountOfObjects * sizeof(T);
			if (newHeadPointer <= m_data + m_size)
			{
				T* returnPointer = reinterpret_cast<T*>(allocationLocation);
				m_head = newHeadPointer;
				for (size_t i = 0; i < amountOfObjects; i++)
				{
					T* object = new(std::addressof(returnPointer[i])) T(std::forward<arguments>(args)...);
					addDestructorToList(object);
				}
				return returnPointer;
			}
			else
			{

				logger::logError<const char*>("In StackAllocator: StackAllocator is full!\n");
				DEBUG_BREAK
					return nullptr;
			}
		}

		StackAllocatorMarker getMarker()
		{
			return StackAllocatorMarker(m_head, destructors.size());
		}

		void deallocateToMarker(StackAllocatorMarker s_a_m)
		{
			m_head = s_a_m.m_makerValue;
			while (destructors.size() > s_a_m.m_destructorHandle)
			{
				destructors.back()();
				destructors.pop_back();
			}
		}

		void deallocateAll()
		{
			m_head = m_data;
			while (destructors.size() > 0)
			{
				destructors.back()();
				destructors.pop_back();
			}
		}

	};
}