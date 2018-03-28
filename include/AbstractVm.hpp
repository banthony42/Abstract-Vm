/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVm.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:02:02 by banthony          #+#    #+#             */
/*   Updated: 2018/03/20 14:02:02 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include <map>
#include "IOperand.hpp"

/* Explication breve des regex en fin de fichier */

#define REGEX_INTEGER "([-]?\\d+).*?([-]?\\d+)"
#define REGEX_DECIMAL "[-]?\\d+[.]\\d+"

#define REGEX_CMDLIST "^(push|pop|dump|assert|add|sub|mul|div|mod|print|exit){1}$"	/* Liste des commandes disponible */
#define REGEX_INTVALUE "^(int((8)|(16)|(32))\\(){1}[-]?[0-9]+[\\)]$"				/* Definit la grammaire d'un parametre de type entier */
#define REGEX_DECIMALVALUE "^((float|double)\\(){1}([-]?[0-9]+[.][0-9]+)[\\)]$"		/* Definit la grammaire d'un parametre de type decimal */

#define REGEX_INT8 "^(int(8)\\(){1}[-]?[0-9]+[\\)]$"								/* Definit la grammaire d'un parametre pour chaque type */
#define REGEX_INT16 "^(int(16)\\(){1}[-]?[0-9]+[\\)]$"
#define REGEX_INT32 "^(int(32)\\(){1}[-]?[0-9]+[\\)]$"
#define REGEX_FLOAT "^(float\\(){1}[-]?[0-9]+[.][0-9]+[\\)]$"
#define REGEX_DOUBLE "^(double\\(){1}[-]?[0-9]+[.][0-9]+[\\)]$"

#define ERROR(i) std::cerr << "Line " << i << ": Error : ";

#define DEBUGVAR(str, var) std::cout << str << var << std::endl
#define DEBUG(str) std::cout << str << std::endl

class AbstractVm {

public:
	AbstractVm(AbstractVm const &copy);				// Canonical
	~AbstractVm();									// Canonical
	AbstractVm &operator=(AbstractVm const &copy);	// Canonical

	typedef IOperand const *(AbstractVm::*createFuncPtr)(std::string const &);
	typedef std::vector < createFuncPtr >	factory;

	typedef void(AbstractVm::*cmdFuncPtr)(IOperand const *);
	typedef std::map < std::string, cmdFuncPtr >	mapped_command;

	static AbstractVm *getInstance(void);
	IOperand const * createOperand( eOperandType type, std::string const & value );

	void execScript(vector_vstr const script);
	void checkSyntax(vector_vstr const script);

	/****************************/
	/***_AbstractVm Exception_***/
	/****************************/

	class AbstractVmException : public std::exception {

	public:
		AbstractVmException();
		AbstractVmException(std::string message);
		AbstractVmException(AbstractVmException const &copy);
		virtual ~AbstractVmException() throw();
		virtual const char *what() const throw();

	private:
		std::string const _errorMessage;
		AbstractVmException operator=(AbstractVmException const &rhs);
	};

private:
	const factory			_operandCreator;		// Factory
	const mapped_command	_commandList;			// Association d'une string a une commande
	std::vector<IOperand*>	_stack;					// Stack
	static AbstractVm *		_singleton;				// Gestion instance unique

	AbstractVm();										// Canonical
	const mapped_command createMap();
	const factory makeFactory();

	bool parsing(vector_str line, std::string *message);

	IOperand const * createInt8( std::string const & value );
	IOperand const * createInt16( std::string const & value );
	IOperand const * createInt32( std::string const & value );
	IOperand const * createFloat( std::string const & value );
	IOperand const * createDouble( std::string const & value );

	void push(IOperand const *operand);
	void pop(IOperand const *operand);
	void dump(IOperand const *operand);
	void assert(IOperand const *operand);
	void add(IOperand const *operand);
	void sub(IOperand const *operand);
	void mul(IOperand const *operand);
	void div(IOperand const *operand);
	void mod(IOperand const *operand);
	void print(IOperand const *operand);
	void exit(IOperand const *operand);
};

/***************************/
/***_REGEXP EXPLANATIONS_***/
/***************************/

/*
 * Exemple:
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

#endif