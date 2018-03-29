/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.template.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:04:18 by banthony          #+#    #+#             */
/*   Updated: 2018/03/20 14:04:18 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_TEMPLATE_HPP
#define OPERAND_TEMPLATE_HPP

#include <sstream>
#include <cmath>
#include "IOperand.hpp"
#include "AbstractVm.hpp"

template<typename T>
class Operand : public IOperand {

private:
	eOperandType	_type;
	std::string		_str;
	T				_value;
	int				_precision;

	Operand<T>() {	} // Canonical

public:

/****************************/
/****_CANONICAL_FUNCTION_****/
/****************************/

	Operand<T>(Operand<T> const &copy) { *this = copy; }	// Canonical

	~Operand<T>() { } 										// Canonical

	Operand<T> &operator=(Operand<T> const &copy)			// Canonical
	{
		if (this != &copy)
		{
			std::ostringstream convert;
			this->_type = copy.getType();
			convert << copy._value;
			this->_str = convert.str();
			this->_value = copy._value;
			this->_precision = copy.getPrecision();
			return *this;
		}
	}

/************************/
/*******_FUNCTION_*******/
/************************/

	Operand<T>(eOperandType const type, T const val): _type(type), _value(val) {

		std::ostringstream convert;
		convert << static_cast<double>(this->_value);
		this->_str = convert.str();

		std::cout << "New Operand is created, type:" << type << ", string value:" << this->toString() << ", numeric value:";
		if (type == FLOAT)
			std::cout << static_cast<float>(val) << std::endl;
		else if (type == DOUBLE)
			std::cout << static_cast<double>(val) << std::endl;
		else
			std::cout << static_cast<int>(val) << std::endl;
	}

	int getPrecision(void) const {
		return this->_precision;
	}

	eOperandType getType(void) const {
		return this->_type;
	}

	std::string const &toString(void) const {
		return this->_str;
	}

/************************/
/*******_OPERATOR_*******/
/************************/

	IOperand const *operator+(IOperand const &rhs) const {
		eOperandType t = (this->getType() > rhs.getType()) ? (this->getType()) : (rhs.getType());
		double nb = std::stod(rhs.toString());

		switch(t) {
			case INT8:
				limitAddSub<char>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<char>(INT8, this->_value + nb));
			case INT16:
				limitAddSub<short>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<short>(INT16, this->_value + nb));
			case INT32:
				limitAddSub<int>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<int>(INT32, this->_value + nb));
			case FLOAT:
				limitAddSub<float>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<float>(FLOAT, this->_value + nb));
			case DOUBLE:
				limitAddSub<double>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<double>(DOUBLE, this->_value + nb));
			case NB_TYPE:
				return NULL;
		}
		return NULL;
	}

	IOperand const *operator-(IOperand const &rhs) const {
		eOperandType t = (this->getType() > rhs.getType()) ? (this->getType()) : (rhs.getType());
		double nb = std::stod(rhs.toString());

		switch(t) {
			case INT8:
				limitAddSub<char>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<char>(INT8, this->_value - nb));
			case INT16:
				limitAddSub<short>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<short>(INT16, this->_value - nb));
			case INT32:
				limitAddSub<int>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<int>(INT32, this->_value - nb));
			case FLOAT:
				limitAddSub<float>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<float>(FLOAT, this->_value - nb));
			case DOUBLE:
				limitAddSub<double>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<double>(DOUBLE, this->_value - nb));
			case NB_TYPE:
				return NULL;
		}
		return NULL;
	}

	IOperand const *operator*(IOperand const &rhs) const { (void)rhs; return(NULL); }
	IOperand const *operator/(IOperand const &rhs) const { (void)rhs; return(NULL); }
	IOperand const *operator%(IOperand const &rhs) const { (void)rhs; return(NULL); }

	template <typename A>
	void limitAddSub(double a, double b) const {

		A max = std::numeric_limits<A>::max();
		A min = std::numeric_limits<A>::min();

		if ((a < 0) == (b < 0)) {		// Si a et b ont le meme signe
			if (a < 0) {        		// Si a est negatif (rappel: a ce stade b a forcement le meme signe que a)

				if (std::fabs(b) > (std::fabs(min) - std::fabs(a)))
					throw AbstractVm::AbstractVmException("Operation will underflow");
			}
			else if (b > (max - a))		// Si b > x, ou x est ce qu'il manque à a pour atteindre le max
				throw AbstractVm::AbstractVmException("Operation will overflow");
		}
	}
};


#endif