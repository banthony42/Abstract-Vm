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

template<typename T>

class Operand : public IOperand {

public:

	IOperand const * createOperand( eOperandType type, std::string const & value ) const {

	}

	Operand<T>(Operand<T> const &copy) {                // Canonical
		*this = copy;
	}

	~Operand<T>() {                                     // Canonical
	}

	Operand<T> &operator=(Operand<T> const &copy) {     // Canonical
		if (this != &copy)
		{
			this->_type = copy.getType();
			this->_precision = copy.getPrecision();
			this->_str = toString();
		}
	}


	IOperand const *operator+(IOperand const &rhs) const {
		if (this->_precision > rhs.getPrecision())
			;
	}


	int getPrecision(void) const {				        // Precision of the type of the instance
		return this->_precision;
	}

	eOperandType getType(void) const {    				// Type of the instance
		return this->_type;
	}

	std::string const &toString(void) const {
		return this->_str;
	}

private:
	Operand<T>();                                       // Canonical

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	static std::vector<  > *factory;

	std::string _str;
	int _precision;
	eOperandType _type;
};

#endif
