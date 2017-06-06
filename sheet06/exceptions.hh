/*
 * exceptions.hh
 *
 *  Created on: 5 Jun 2017
 *      Author: fighterlin
 */

#ifndef EXCEPTIONS_HH_
#define EXCEPTIONS_HH_

#include <string>
#include <exception>

class OutOfBoundsException : public std::exception
{
public:

	OutOfBoundsException(std::string msg_)
	{
		msg = msg_;
	}

	~OutOfBoundsException() throw()
	{

	}

	const char* what() const throw()
	{
		return msg.c_str();
	}

private:
	std::string msg;

};

class IncompatibleDimensionException : public std::exception
{
public:

	IncompatibleDimensionException(std::string msg_)
	{
		msg = msg_;
	}

	~IncompatibleDimensionException() throw()
	{

	}

	const char* what() const throw()
	{
		return msg.c_str();
	}

private:
	std::string msg;

};



#endif /* EXCEPTIONS_HH_ */
