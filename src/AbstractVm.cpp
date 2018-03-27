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

static const AbstractVm::factory makeFactory() {
	AbstractVm::factory f;

	f.push_back(&AbstractVm::createInt8);
	f.push_back(&AbstractVm::createInt16);
	f.push_back(&AbstractVm::createInt32);
	f.push_back(&AbstractVm::createFloat);
	f.push_back(&AbstractVm::createDouble);
	return f;
}

const AbstractVm::mapped_command AbstractVm::createMap() {
	AbstractVm::mapped_command m;

	m["push"] = &AbstractVm::push;
	m["pop"] = &AbstractVm::pop;
	m["dump"] = &AbstractVm::dump;
	m["assert"] = &AbstractVm::assert;
	m["add"] = &AbstractVm::add;
	m["sub"] = &AbstractVm::sub;
	m["mul"] = &AbstractVm::mul;
	m["div"] = &AbstractVm::div;
	m["mod"] = &AbstractVm::mod;
	m["print"] = &AbstractVm::print;
	m["exit"] = &AbstractVm::exit;

	return m;
}

AbstractVm *AbstractVm::_singleton = NULL;        /* Initialisation de la singleton a NULL */

const AbstractVm::factory AbstractVm::_operandCreator = makeFactory();

const AbstractVm::mapped_command AbstractVm::_commandList = AbstractVm::createMap();

/************************/
/*******_FUNCTION_*******/
/************************/

bool AbstractVm::parsing(vector_str line, std::string *message) {

	std::regex cmdList("^(push|pop|dump|assert|add|sub|mul|div|mod|print|exit){1}$");        /* Liste des commandes possible */
	std::regex integer_value("^(int((8)|(16)|(32))\\(){1}[-]?[0-9]+\\){1}$");                /* Tellement puissant ... */
	std::regex decimal_value("^((float|double)\\(){1}[-]?[0-9]+(.){0,1}[0-9]+\\){1}$");    /* Explication des regex en fin de fichiers*/

	if (line[0][0] == ';')    /* Si commentaire on passe */
		return true;

	if (std::regex_match(line[0], cmdList) == false) {        /* Test parmis la liste des commandes disponnible	*/
		*message = "Command not found";                        /* Si aucune n'est trouvé, erreur					*/
		return false;
	}

	if (line[0] == "push" || line[0] == "assert") {    /* Commandes qui necessitent un argument en parametre */

		if (std::regex_match(line[1], integer_value) == false) {        /* Test si VALUE == intXX(XX)				*/

			if (std::regex_match(line[1], decimal_value) == false) {    /* Test si VALUE == float/double(XX.XX)		*/
				*message = "Syntax error";
				return false;                                            /* Si aucun pattern n'est trouvé, erreur	*/
			}
		}

		if (line.size() > 2 && line[2][0] != ';') {        /* Si la ligne comporte plusieurs mots et que le troisieme ne commence pas par ; */
			*message = "Too many argument";                /* un commentaires, alors erreur. */
			return false;
		}
	} else {    /* Commandes qui n'ont aucun parametre */

		if (line.size() > 1 && line[1][0] != ';') {        /* Si la ligne comporte plusieurs mots et que le second ne commence pas par ; */
			*message = "Too many argument";                /* un commentaires, alors erreur. */
			return false;
		}
	}

	return true;
}

void AbstractVm::checkSyntax(vector_vstr const script) {

	vector_vstr::const_iterator it = script.begin();
	std::string message;
	int i = 1;
	while (it != script.end()) {

		if (this->parsing(*it, &message) == false) {
			ERROR(i);
			throw AbstractVm::AbstractVmException(message);
		}
		i++;
		it++;
	}
}

void AbstractVm::execScript(vector_vstr const script) {

	vector_vstr::const_iterator it = script.begin();
	int i = 1;
	while (it != script.end()) {

		if ((*it)[0][0] != ';') {

			/* Recup de la fonction associé a la commande, qui est sous forme de string */
			AbstractVm::cmdFuncPtr funcPointer = AbstractVm::_commandList.at((*it)[0]);

			if ((*it).size() > 1) {

				if ((*it)[1][0] != ';') {        /* La commande est un push ou un assert il faut creer une operand */

					// create operand
					DEBUG(":push ou assert:");
					(this->*funcPointer)(NULL);
				}

				/* Sinon la commande ne prend aucun parametre et est suivi d'un commentaire, ex: "add ;ajout"	*/
			} else
				(this->*funcPointer)(NULL);
		}
		i++;
		it++;
	}
}

AbstractVm *AbstractVm::getInstance(void) {
	if (_singleton == NULL)
		_singleton = new AbstractVm();
	return (_singleton);
}

IOperand const *AbstractVm::createOperand(eOperandType type, std::string const &value) {
	(*(AbstractVm::_operandCreator[type]))(value);
	return nullptr;
}

void AbstractVm::push(IOperand *operand) {
	DEBUG("----PUSH CODE-----");
	(void) operand;
}

void AbstractVm::pop(IOperand *operand) {
	DEBUG("----POP CODE-----");
	(void) operand;
}

void AbstractVm::dump(IOperand *operand) {
	DEBUG("----DUMP CODE-----");
	(void) operand;
}

void AbstractVm::assert(IOperand *operand) {
	DEBUG("----ASSERT CODE-----");
	(void) operand;
}

void AbstractVm::add(IOperand *operand) {
	DEBUG("----ADD CODE-----");
	(void) operand;
}

void AbstractVm::sub(IOperand *operand) {
	DEBUG("----SUB CODE-----");
	(void) operand;
}

void AbstractVm::mul(IOperand *operand) {
	DEBUG("----MUL CODE-----");
	(void) operand;
}

void AbstractVm::div(IOperand *operand) {
	DEBUG("----DIV CODE-----");
	(void) operand;
}

void AbstractVm::mod(IOperand *operand) {
	DEBUG("----MOD CODE-----");
	(void) operand;
}

void AbstractVm::print(IOperand *operand) {
	DEBUG("----PRI CODE-----");
	(void) operand;
}

void AbstractVm::exit(IOperand *operand) {
	DEBUG("----EXI CODE-----");
	(void) operand;
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

AbstractVm::AbstractVmException::AbstractVmException(std::string message) : _errorMessage(message) {
}

const char *AbstractVm::AbstractVmException::what() const throw() {
	return this->_errorMessage.c_str();
}

AbstractVm::AbstractVmException::AbstractVmException() : _errorMessage("AbstractVm error:") {
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
