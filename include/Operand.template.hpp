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

private:
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
			this->_type = copy.getType();
			this->_str = copy.toString();
			this->_value = copy._value;
			this->_precision = copy.getPrecision();
			return *this;
		}
	}

/************************/
/*******_FUNCTION_*******/
/************************/

	Operand<T>(eOperandType const type, T const val): _type(type), _value(val), _precision(type) {

		std::ostringstream convert;
		switch(type) {
			case INT8:
				this->_str = std::to_string(this->_value);
				break ;
			case INT16:
				this->_str = std::to_string(this->_value);
				break ;
			case INT32:
				this->_str = std::to_string(this->_value);
				break ;
			case FLOAT:
				this->_str = std::to_string(this->_value);
				break ;
			case DOUBLE:
				this->_str = std::to_string(this->_value);
				break ;
			case NB_TYPE:
				break ;
		}
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

		/* Changement de signe de nb, pour utiliser la meme fonction d'overflow */

		switch(t) {
			case INT8:
				limitAddSub<char>(this->_value, (nb * -1));
				return reinterpret_cast<const IOperand *>(new Operand<char>(INT8, this->_value - nb));
			case INT16:
				limitAddSub<short>(this->_value, (nb * -1));
				return reinterpret_cast<const IOperand *>(new Operand<short>(INT16, this->_value - nb));
			case INT32:
				limitAddSub<int>(this->_value, (nb * -1));
				return reinterpret_cast<const IOperand *>(new Operand<int>(INT32, this->_value - nb));
			case FLOAT:
				limitAddSub<float>(this->_value, (nb * -1));
				return reinterpret_cast<const IOperand *>(new Operand<float>(FLOAT, this->_value - nb));
			case DOUBLE:
				limitAddSub<double>(this->_value, (nb * -1));
				return reinterpret_cast<const IOperand *>(new Operand<double>(DOUBLE, this->_value - nb));
			case NB_TYPE:
				return NULL;
		}
		return NULL;
	}

	IOperand const *operator*(IOperand const &rhs) const {
		eOperandType t = (this->getType() > rhs.getType()) ? (this->getType()) : (rhs.getType());
		double nb = std::stod(rhs.toString());

		switch (t) {
			case INT8:
				limitMult<char>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<char>(INT8, this->_value * nb));
			case INT16:
				limitMult<short>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<short>(INT16, this->_value * nb));
			case INT32:
				limitMult<int>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<int>(INT32, this->_value * nb));
			case FLOAT:
				limitMult<float>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<float>(FLOAT, this->_value * nb));
			case DOUBLE:
				limitMult<double>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<double>(DOUBLE, this->_value * nb));
			case NB_TYPE:
				return NULL;
		}
		return (NULL);
	}

	IOperand const *operator/(IOperand const &rhs) const {
		eOperandType t = (this->getType() > rhs.getType()) ? (this->getType()) : (rhs.getType());
		double nb = std::stod(rhs.toString());

		switch (t) {
			case INT8:
				limitDivMod<char>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<char>(INT8, this->_value / nb));
			case INT16:
				limitDivMod<short>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<short>(INT16, this->_value / nb));
			case INT32:
				limitDivMod<int>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<int>(INT32, this->_value / nb));
			case FLOAT:
				limitDivMod<float>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<float>(FLOAT, this->_value / nb));
			case DOUBLE:
				limitDivMod<double>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<double>(DOUBLE, this->_value / nb));
			case NB_TYPE:
				return NULL;
		}
		return (NULL);
	}

	IOperand const *operator%(IOperand const &rhs) const {
		eOperandType t = (this->getType() > rhs.getType()) ? (this->getType()) : (rhs.getType());
		double nb = std::stod(rhs.toString());

		switch (t) {
			case INT8:
				limitDivMod<char>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<char>(INT8, std::fmod(this->_value, nb)));
			case INT16:
				limitDivMod<short>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<short>(INT16, std::fmod(this->_value, nb)));
			case INT32:
				limitDivMod<int>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<int>(INT32, std::fmod(this->_value, nb)));
			case FLOAT:
				limitDivMod<float>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<float>(FLOAT, std::fmod(this->_value, nb)));
			case DOUBLE:
				limitDivMod<double>(this->_value, nb);
				return reinterpret_cast<const IOperand *>(new Operand<double>(DOUBLE, std::fmod(this->_value, nb)));
			case NB_TYPE:
				return NULL;
		}
		return (NULL);
	}

	template <typename A>
	void limitAddSub(double a, double b) const {

		A max = std::numeric_limits<A>::max();
		A min = std::numeric_limits<A>::min();

		if ((a < 0) == (b < 0)) {		// Si a et b ont le meme signe
			if (a < 0) {        		// Et que a et b sont < a 0
				if (std::fabs(b) > (std::fabs(min) - std::fabs(a)))	// Si b > x, ou x = Le reste pour que a atteigne le min
					throw AbstractVm::AbstractVmException("Error: Operation will underflow");
			}
			else if (b > (max - a))		// a et b sont > a 0 ; Si b > x, ou x = Le reste pour que a atteigne le max
				throw AbstractVm::AbstractVmException("Error: Operation will overflow");
		}
	}

	template <typename B>
	void limitMult(double a, double b) const {
		B max = std::numeric_limits<B>::max();
		B min = std::numeric_limits<B>::min();

		if ((a < 0) == (b < 0)) {        				// Si a et b ont le meme signe
			if (std::fabs(b) > (max / std::fabs(a)))	// si b est superieur a x, ou x * a = max
				throw AbstractVm::AbstractVmException("Error: Operation will overflow");
		}												// Sinon a et b ont un signe different, l'underflow est possible
		else if (std::fabs(b) > (min / std::fabs(a)))	// si b est superieur a x, ou x * a = min
			throw AbstractVm::AbstractVmException("Error: Operation will underflow");
	}

	template <typename C>
	void limitDivMod(double a, double b) const {
		C min = std::numeric_limits<C>::min();

		if (b == 0)
			throw AbstractVm::AbstractVmException("Error: Divide by zero");
		else if (a == min && b == -1)
			throw AbstractVm::AbstractVmException("Error: Operation will underflow");
	}
};

#endif