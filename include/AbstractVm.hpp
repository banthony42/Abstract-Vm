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

class AbstractVm {

public:

	typedef std::vector<const IOperand  *(*)(std::string const &)> factory;

	AbstractVm(AbstractVm const &copy);				// Canonical
	~AbstractVm();									// Canonical
	AbstractVm &operator=(AbstractVm const &copy);	// Canonical

	static AbstractVm getInstance(void);
	void execCommand(vector_str line);
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	void test(void);

private:
	static factory											_operatorCreator;		// Factory
	std::map<std::string, void(AbstractVm::*)(IOperand *)>	_commandList;			// Association d'une string a une commande
	std::vector<IOperand*>									_stack;					// Stack
	static AbstractVm *										_singleton;				// Gestion instance unique

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

	bool checkSyntax(vector_str line);

	static IOperand const * createInt8( std::string const & value ) ;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};


#endif
