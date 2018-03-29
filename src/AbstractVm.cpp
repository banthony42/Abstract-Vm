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
#include "../include/Operand.template.hpp"


/************************/
/****_INITIALIZATION_****/
/************************/

const AbstractVm::factory AbstractVm::makeFactory() {
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

/************************/
/*******_FUNCTION_*******/
/************************/

bool AbstractVm::parsing(vector_str line, std::string *message) {

	std::regex cmdList(REGEX_CMDLIST);
	std::regex integer_value(REGEX_INTVALUE);
	std::regex decimal_value(REGEX_DECIMALVALUE);

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
	bool exit = false;
	this->_line = 1;
	while (it != script.end()) {

		if (this->parsing(*it, &message) == false) {
			ERROR(this->_line);
			throw AbstractVm::AbstractVmException(message);
		}
		if (!exit && (*it)[0] == "exit")
			exit = true;
		this->_line++;
		it++;
	}
	if (!exit) {
		ERROR(this->_line - 1);
		throw AbstractVm::AbstractVmException("The programm should end with an exit command.");
	}
}

/* Aide rappel
 * (*it)		= vecteur de string, (correspond a une ligne issue d'un split suivant espaces, tab)
 * (*it)[0]		= premier mot de la ligne (*it)
 * (*it)[0][0]	= premier caractere du premier mot de la ligne (*it)
 */
void AbstractVm::execScript(vector_vstr const script) {

	vector_vstr::const_iterator it = script.begin();
	this->_line = 1;
	while (it != script.end()) {

		if ((*it)[0][0] != ';') {	/* Si la ligne n'est pas commentée on peut la traiter */
									/* Recup de la fonction associé a la commande, a partir de sa string */
			AbstractVm::cmdFuncPtr funcPointer = AbstractVm::_commandList.at((*it)[0]);

			if ((*it).size() > 1) {				/* Si la ligne contient plus de un mot 				*/
				if ((*it)[1][0] != ';') {		/* Et que le second mot n'est pas un commentaire 	*/
												/* alors on doit traiter un push ou un assert		*/
					std::regex int8(REGEX_INT8);
					std::regex int16(REGEX_INT16);
					std::regex int32(REGEX_INT32);
					std::regex decimal_float(REGEX_FLOAT);
					std::regex decimal_double(REGEX_DOUBLE);
					IOperand const *op = NULL;

					if (std::regex_match((*it)[1], int8) == true)
						op = AbstractVm::createOperand(INT8, (*it)[1]);

					if (std::regex_match((*it)[1], int16) == true)
						op = AbstractVm::createOperand(INT16, (*it)[1]);

					if (std::regex_match((*it)[1], int32) == true)
						op = AbstractVm::createOperand(INT32, (*it)[1]);

					if (std::regex_match((*it)[1], decimal_float) == true)
						op = AbstractVm::createOperand(FLOAT, (*it)[1]);

					if (std::regex_match((*it)[1], decimal_double) == true)
						op = AbstractVm::createOperand(DOUBLE, (*it)[1]);

					(this->*funcPointer)(op);
				}
				else						/* si le 2eme mot est un commentaire, alors on traite une commande simple */
					(this->*funcPointer)(NULL);
			}
			else							/* si la ligne ne comporte qu'un mot, alors on traite une commande simple */
				(this->*funcPointer)(NULL);
		}
		if ((*it)[0] == "exit")	// Si la commande est exit, on arrete l'execution
			return ;
		this->_line++;
		it++;
	}
}

AbstractVm *AbstractVm::getInstance(void) {
	if (_singleton == NULL)
		_singleton = new AbstractVm();
	return (_singleton);
}

/****CREATOR****/

IOperand const *AbstractVm::createOperand(eOperandType type, std::string const &value) {

	AbstractVm::createFuncPtr  funcPointer = this->_operandCreator[type];

	std::smatch cm;
	std::regex e(REGEX_INTEGER);
	unsigned long n_match = 2;

	if (type == FLOAT || type == DOUBLE) {
		e = REGEX_DECIMAL;
		n_match = 0;
	}

	if (std::regex_search(value.begin(),value.end(), cm, e) == false)
		throw  AbstractVmException("No match, during the value extraction.");

	if (n_match && cm.size() <= n_match)
		throw  AbstractVmException("Not enough match");

	return 	dynamic_cast<IOperand const *>((this->*funcPointer)(cm[n_match]));
}

IOperand const *AbstractVm::createInt8(std::string const &value) {
	int nb = std::stoi(value);
	if (nb < INT8_MIN || nb > INT8_MAX)
		throw AbstractVm::AbstractVmException("INT8: Out of range");

	IOperand *op = new Operand<char>(INT8, nb);
	return op;
}

IOperand const *AbstractVm::createInt16(std::string const &value) {
	int nb = std::stoi(value);
	if (nb < INT16_MIN || nb > INT16_MAX)
		throw AbstractVm::AbstractVmException("INT16: Out of range");

	IOperand *op = new Operand<short>(INT16, nb);
	return op;
}

IOperand const *AbstractVm::createInt32(std::string const &value) {
	int nb = std::stoi(value);
	if (nb < INT32_MIN || nb > INT32_MAX)
		throw AbstractVm::AbstractVmException("INT32: Out of range");

	IOperand *op = new Operand<int>(INT32, nb);
	return op;
}

IOperand const *AbstractVm::createFloat(std::string const &value) {

		double nb = std::stof(value);
		if (nb > std::numeric_limits<float>::max() || nb < std::numeric_limits<float>::min())
			throw AbstractVm::AbstractVmException("FLOAT: Out of range");

		IOperand *op = new Operand<float>(FLOAT, nb);
		return op;
}

IOperand const *AbstractVm::createDouble(std::string const &value) {

		double nb = std::stof(value);
		IOperand *op = new Operand<double>(DOUBLE, nb);
		return op;
}

/****STACK_COMMAND****/

/*
 * Recupere le dernier element et le supprime de la stack
 */
IOperand const *AbstractVm::popBack(void) {
	if (!this->_stack.size())
		return NULL;
	IOperand const * op = this->_stack.back();
	this->_stack.pop_back();
	return op;
}

/****COMMAND****/

void AbstractVm::push(IOperand const *operand) {
	this->_stack.push_back(operand);
}

void AbstractVm::pop(IOperand const *operand) {
	if (this->_stack.size() == 0) {
		ERROR(this->_line);
		throw AbstractVm::AbstractVmException("Pop on empty stack");
	}
	(void) operand;
}

void AbstractVm::dump(IOperand const *operand) {
	std::vector<IOperand const *>::const_iterator it = this->_stack.end();
	while (it != this->_stack.begin()) {
		it--;
		std::cout << (*it)->toString() << std::endl;

	}
	(void)(operand);
}

void AbstractVm::assert(IOperand const *operand) {
	DEBUG("----ASSERT CODE-----");
	(void) operand;
}

void AbstractVm::add(IOperand const *operand) {
	if (this->_stack.size() < 2)
		throw AbstractVm::AbstractVmException("Can't add operand, the stack size is strictly less than 2");

	IOperand const * op1 = this->popBack();
	IOperand const * op2 = this->popBack();
	IOperand const * op3 = *op1 + *op2;

	this->_stack.push_back(op3);
	(void) operand;
}

void AbstractVm::sub(IOperand const *operand) {
	if (this->_stack.size() < 2)
		throw AbstractVm::AbstractVmException("Can't sub operand, the stack size is strictly less than 2");

	IOperand const * op1 = this->popBack();
	IOperand const * op2 = this->popBack();
	IOperand const * op3 = *op1 - *op2;

	this->_stack.push_back(op3);
	(void) operand;
}

void AbstractVm::mul(IOperand const *operand) {
	DEBUG("----MUL CODE-----");
	(void) operand;
}

void AbstractVm::div(IOperand const *operand) {
	DEBUG("----DIV CODE-----");
	(void) operand;
}

void AbstractVm::mod(IOperand const *operand) {
	DEBUG("----MOD CODE-----");
	(void) operand;
}

void AbstractVm::print(IOperand const *operand) {
	DEBUG("----PRINT CODE-----");
	(void) operand;
}

void AbstractVm::exit(IOperand const *operand) {
	IOperand const * tmp;
	while (this->_stack.size()) {
		tmp = this->popBack();		// Depilage et recuperation d'une operand
		delete tmp;					// Liberation de la memoire
	}
	(void)operand;
}

/************************/
/**_CANONICAL_FUNCTION_**/
/************************/

AbstractVm::AbstractVm(): _operandCreator(this->makeFactory()), _commandList(this->createMap()) {
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
