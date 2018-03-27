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

#define ERROR(i) std::cerr << "Line " << i << ": Error : ";

class AbstractVm {

public:
	AbstractVm(AbstractVm const &copy);				// Canonical
	~AbstractVm();									// Canonical
	AbstractVm &operator=(AbstractVm const &copy);	// Canonical

	static AbstractVm *getInstance(void);
	void execScript(vector_vstr const script);
	void checkSyntax(vector_vstr const script);

	typedef std::vector < const IOperand *(*)(std::string const &) >	factory;
	typedef void(AbstractVm::*cmdFuncPtr)(IOperand *);
	typedef std::map < std::string, cmdFuncPtr >	mapped_command;

	static const mapped_command createMap();

	static IOperand const * createOperand( eOperandType type, std::string const & value );
	static IOperand const * createInt8( std::string const & value );
	static IOperand const * createInt16( std::string const & value );
	static IOperand const * createInt32( std::string const & value );
	static IOperand const * createFloat( std::string const & value );
	static IOperand const * createDouble( std::string const & value );

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
	static const factory		_operandCreator;		// Factory
	static const mapped_command	_commandList;			// Association d'une string a une commande
	std::vector<IOperand*>		_stack;					// Stack
	static AbstractVm *			_singleton;				// Gestion instance unique

	AbstractVm();	// Canonical

	void push(IOperand *operand);
	void pop(IOperand *operand);
	void dump(IOperand *operand);
	void assert(IOperand *operand);
	void add(IOperand *operand);
	void sub(IOperand *operand);
	void mul(IOperand *operand);
	void div(IOperand *operand);
	void mod(IOperand *operand);
	void print(IOperand *operand);
	void exit(IOperand *operand);

	bool parsing(vector_str line, std::string *message);
};

#endif