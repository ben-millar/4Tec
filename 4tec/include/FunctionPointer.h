#ifndef FUNCTION_POINTER_INCLUDE
#define FUNCTION_POINTER_INCLUDE

#include <functional>

/// <summary>
/// Base Class for the templated functions to inherit from
/// </summary>
class FunctionPointer
{
public:
	FunctionPointer() = default;
	virtual	~FunctionPointer() = default;
	/// <summary>
	/// Allows the inherited function to be called through polymorphism
	/// </summary>
	virtual void call() = 0;
};

/// <summary>
/// Function pointer to any function that takes 0 arguments
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class Function : public FunctionPointer
{
public:
	Function(T* t_caller, std::function<void(T*)> t_func) : m_caller(t_caller), m_func(t_func) {}
	~Function() = default;

	/// <summary>
	/// Allows the class to call any function regardless of the class
	/// </summary>
	void call()override
	{
		if (m_caller)
			m_func(m_caller);
	}

private:
	T* m_caller;
	std::function<void(T*)> m_func;
};

/// <summary>
/// New class that accepts 1 argument
/// </summary>
/// <typeparam name="T"> Class Type </typeparam>
/// <typeparam name="U"> Argument </typeparam>
template<typename T, typename U>
class FunctionArg : public FunctionPointer
{
public:
	FunctionArg(T* t_caller, std::function<void(T*, U)> t_func, U t_arg) : m_caller(t_caller), m_func(t_func), m_arg(t_arg) {}
	~FunctionArg() = default;

	void call()override
	{
		if (m_caller)
			m_func(m_caller, m_arg);
	}

private:
	T* m_caller;
	std::function<void(T*, U)> m_func;
	U m_arg;
};

#endif