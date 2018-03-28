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
			this->_type = copy.getType();
			this->_precision = copy.getPrecision();
			this->_str = toString();
		}
	}

/************************/
/*******_FUNCTION_*******/
/************************/

	Operand<T>(eOperandType type, std::string const &value, T val): _type(type), _str(value), _value(val) {
		std::cout << "New Operand is created, type:" << type << ", string value:" << value << ", numeric value:";

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
		//plutot utiliser une conversion de la variable T _value vers une string
	}

/************************/
/*******_OPERATOR_*******/
/************************/

	IOperand const *operator+(IOperand const &rhs) const { (void)rhs; return(NULL); }
	IOperand const *operator-(IOperand const &rhs) const { (void)rhs; return(NULL); }
	IOperand const *operator*(IOperand const &rhs) const { (void)rhs; return(NULL); }
	IOperand const *operator/(IOperand const &rhs) const { (void)rhs; return(NULL); }
	IOperand const *operator%(IOperand const &rhs) const { (void)rhs; return(NULL); }

};

#endif