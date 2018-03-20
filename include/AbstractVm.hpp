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


class AbstractVm {

public:
	AbstractVm();									// Canonical
	AbstractVm(AbstractVm const &copy);				// Canonical
	~AbstractVm();									// Canonical
	AbstractVm &operator=(AbstractVm const &copy);	// Canonical

private:

};


#endif
