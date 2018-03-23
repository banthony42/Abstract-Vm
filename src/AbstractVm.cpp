/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVm.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:01:30 by banthony          #+#    #+#             */
//   Updated: 2018/03/23 18:06:57 by banthony         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <regex>
#include "../include/AbstractVm.hpp"


/************************/
/****_INITIALIZATION_****/
/************************/

AbstractVm *AbstractVm::_singleton = NULL;    /* Initialisation de la singleton a NULL */

const AbstractVm::factory MakeFactory() {
	AbstractVm::factory f;

	f.push_back(&AbstractVm::createInt8);
	f.push_back(&AbstractVm::createInt16);
	f.push_back(&AbstractVm::createInt32);
	f.push_back(&AbstractVm::createFloat);
	f.push_back(&AbstractVm::createDouble);
	return f;
}

const AbstractVm::factory AbstractVm::_operandCreator = MakeFactory();


/************************/
/*******_FUNCTION_*******/
/************************/

bool AbstractVm::checkSyntax(vector_str line, std::string *message) {

	std::regex cmdList ("^(push|pop|dump|assert|add|sub|mul|div|mod|print|exit){1}$");		/* Liste des commandes possible */
	std::regex integer_value ("^(int((8)|(16)|(32))\\(){1}[-]?[0-9]+\\){1}$");				/* Tellement puissant ... */
	std::regex decimal_value ("^((float|double)\\(){1}[-]?[0-9]+(.){0,1}[0-9]+\\){1}$");	/* Explication des regex en fin de fichiers*/

	if (std::regex_match(line[0], cmdList) == false) {		/* Test parmis la liste des commandes disponnible	*/
		*message = "Command not found";				/* Si aucune n'est trouvé, erreur					*/
		return false;
	}

	if (line[0] == "push" || line[0] == "assert") {

		if (std::regex_match(line[1], integer_value) == false) {		/* Test si VALUE == intXX(XX)				*/
			if (std::regex_match(line[1], decimal_value) == false) {	/* Test si VALUE == float/double(XX.XX)		*/
				*message = "Syntax error";
				return false;											/* Si aucun pattern n'est trouvé, erreur	*/
			}
		}
	}

	if (line.size() > 2 && line[2][0] != ';') {
		*message = "Too many argument";
		return false;
	}
	return true;
}

void AbstractVm::execScript(vector_vstr const script) {
	vector_vstr::const_iterator it = script.begin();
	std::string message;
	int i = 1;
	while (it != script.end()) {

		if (this->checkSyntax(*it, &message) == false) {
			ERROR(i);
			throw AbstractVm::AbstractVmException(message);
		}
		i++;
		it++;
	}
}

AbstractVm AbstractVm::getInstance(void) {
	if (_singleton == NULL)
		_singleton = new AbstractVm();
	return *(_singleton);
}

IOperand const *AbstractVm::createOperand(eOperandType type, std::string const &value) {
	(*(AbstractVm::_operandCreator[type]))(value);
	return nullptr;
}

IOperand const *AbstractVm::createInt8(std::string const &value) {
	(void) value;
	DEBUG("int8");
	return nullptr;
}

IOperand const *AbstractVm::createInt16(std::string const &value) {
	(void) value;
	DEBUG("int16");
	return nullptr;
}

IOperand const *AbstractVm::createInt32(std::string const &value) {
	(void) value;
	DEBUG("int32");
	return nullptr;
}

IOperand const *AbstractVm::createFloat(std::string const &value) {
	(void) value;
	DEBUG("float");
	return nullptr;
}

IOperand const *AbstractVm::createDouble(std::string const &value) {
	(void) value;
	DEBUG("double");
	return nullptr;
}


/************************/
/**_CANONICAL_FUNCTION_**/
/************************/

AbstractVm::AbstractVm() {
	return;
}

AbstractVm::AbstractVm(AbstractVm const &copy) {
	*this = copy;
}

AbstractVm::~AbstractVm() {
	return;
}

AbstractVm &AbstractVm::operator=(AbstractVm const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}


/***************************/
/**_ABSTRACT_VM EXCEPTION_**/
/***************************/

AbstractVm::AbstractVmException::AbstractVmException(std::string message): _errorMessage(message) {
}

const char *AbstractVm::AbstractVmException::what() const throw() {
	return this->_errorMessage.c_str();
}

AbstractVm::AbstractVmException::AbstractVmException(): _errorMessage("AbstractVm error:") {
}

AbstractVm::AbstractVmException::AbstractVmException(const AbstractVm::AbstractVmException &copy) {
	if (this != &copy)
		*this = copy;
}

AbstractVm::AbstractVmException::~AbstractVmException() throw() {
}

AbstractVm::AbstractVmException AbstractVm::AbstractVmException::operator=(const AbstractVm::AbstractVmException &rhs) {
	return rhs;
}

/***************************/
/***_REGEXP EXPLANATIONS_***/
/***************************/

/*
 * N = ^(int((8)|(16)|(32))\(){1}[-]?[0-9]+\){1}$
 *
 * ^ oblige que le pattern soit au debut de la string
 *
 * Groupe 1: ( int ((8) | (16) | (32)) \( ){1}
 * Oblige a trouver au moins une fois : "int8(" ou "int16(" ou "int32("
 *
 * Groupe 2: [-]?[0-9]+
 * [-] Le caractere '-'
 * ? Autorise la sequence precedente a etre presente une ou zero fois
 * [0-9] Autorise un chiffre de 0 a 9 inclus
 * + Autorise a repeter la sequence precedente une ou plusieurs fois
 *
 * \) Le caractere ')'
 * {1} La sequence precedente doit etre presente une fois
 *
 */
