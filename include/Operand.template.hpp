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
	std::string		_str;
	int				_precision;
	eOperandType	_type;
	T				_value;

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

	Operand<T>(eOperandType type, std::string const &value): _type(type), _str(value) {
		std::cout << "New Operand is created, type:" << type << ", value:" << value << std::endl;
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

	IOperand const *operator+(IOperand const &rhs) const { return(NULL); }
	IOperand const *operator-(IOperand const &rhs) const { return(NULL); }
	IOperand const *operator*(IOperand const &rhs) const { return(NULL); }
	IOperand const *operator/(IOperand const &rhs) const { return(NULL); }
	IOperand const *operator%(IOperand const &rhs) const { return(NULL); }

};

#endif



//		IOperand const *resultat = NULL;
//
//		if (this->_precision > rhs.getPrecision())
//			resultat = AbstractVm::createOperand(this->_type, this->_str);
//		else
//			resultat = AbstractVm::createOperand(rhs.getType(), rhs.toString());