/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVm.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:01:30 by banthony          #+#    #+#             */
/*   Updated: 2018/03/20 14:01:30 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AbstractVm.hpp"

AbstractVm *AbstractVm::_singleton = NULL;	/* Initialisation de la singleton a NULL */

AbstractVm::factory AbstractVm::_operatorCreator({
		&AbstractVm::createInt8,
//		&AbstractVm::createInt16,
//		&AbstractVm::createInt32,
//		&AbstractVm::createFloat,
//		&AbstractVm::createDouble,
												 });


AbstractVm AbstractVm::getInstance(void) {
	if (_singleton == NULL)
		_singleton = new AbstractVm();
	return *(_singleton);
}



void AbstractVm::test(void) {
	(*(AbstractVm::_operatorCreator[INT8]))("42");
}

IOperand const *AbstractVm::createInt8(std::string const &value)  {
	(void)value;
	DEBUG("int8");
	return nullptr;
}

IOperand const *AbstractVm::createInt16(std::string const &value) const {
	(void)value;
	DEBUG("int16");
	return nullptr;
}

IOperand const *AbstractVm::createInt32(std::string const &value) const {
	(void)value;
	DEBUG("int32");
	return nullptr;
}

IOperand const *AbstractVm::createFloat(std::string const &value) const {
	(void)value;
	DEBUG("float");
	return nullptr;
}

IOperand const *AbstractVm::createDouble(std::string const &value) const {
	(void)value;
	DEBUG("double");
	return nullptr;
}

/*	CANONICAL FUNCTION	*/

AbstractVm::AbstractVm()
{
	return ;
}

AbstractVm::AbstractVm(AbstractVm const &copy) {
	*this = copy;
}

AbstractVm::~AbstractVm() {
	return ;
}

AbstractVm &AbstractVm::operator=(AbstractVm const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}
