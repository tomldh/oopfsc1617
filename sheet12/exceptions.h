
#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>
#include <sstream>
#include <exception>

class TypeException : public std::exception
{
public:

	TypeException(std::string msg, std::string expect)
	{

		std::stringstream ss;
		ss << "ERROR " << msg << ": ";
		ss << "expected \"" << expect << "\"." << std::endl;

		op_msg = ss.str();


	}

	~TypeException() throw() {}

	const char* what() const throw()
	{
		return op_msg.c_str();
	}

private:
	std::string op_msg;
};


class DimensionException : public std::exception
{
public:
	DimensionException(std::string msg, std:: string obj1, unsigned int d1, std::string obj2, unsigned int d2)
	{
		std::stringstream ss;
		ss << "ERROR " << msg << ": ";
		ss << obj1 << " " << d1 << ", ";
		ss << obj2 << " " << d2 << " " << std::endl;

		op_msg = ss.str();
	}

	~DimensionException() {}

	const char* what() const throw()
	{
		return op_msg.c_str();
	}

private:
	std::string op_msg;
};


#endif /* EXCEPTIONS_H_ */
