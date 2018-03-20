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

#include "AbstractVm.hpp"

AbstractVm::AbstractVm() {

}

AbstractVm::AbstractVm(AbstractVm const &copy) {
    *this = copy;
}

AbstractVm::~AbstractVm() {

}

AbstractVm &AbstractVm::operator=(AbstractVm const copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}