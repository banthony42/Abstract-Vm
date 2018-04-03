/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:01:15 by banthony          #+#    #+#             */
/*   Updated: 2018/03/16 14:01:15 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "../include/IOperand.hpp"
#include "../include/AbstractVm.hpp"

/*
 * Chaque ligne du programme correspond a un element d'un tableau de tableau. (vector de vector de string)
 * Chaque ligne est stockee sous forme de vector de string, issue d'un strsplit sur les espaces.
 *
 * Consideront un programme simple, et une variable tab, qui est un tableau, de tableau de string. (std::vector< std::vector<std::string> > )
 *
 * push int32(42) ;commentaire   =  tab[0]
 *                                      tab[0].begin()      = push
 *                                      tab[0].begin() + 1  = int32(42)
 *                                      tab[0].begin() + 2  = ;commentaire
 *
 * push int32(21)               =   tab[1]
 *                                      tab[1].begin()      = push
 *                                      tab[1].begin() + 1  = int32(21)
 *
 * dump                         =   tab[2]
 *                                      tab[2].begin()      = dump
 *
 * exit                         =   tab[3]
 *                                      tab[3].begin()      = exit
 */

/*
 * Separe une chaine de caractere sous forme de string, en fonction
 * des espaces et tabulations, qu'elle contient.
 * Stock le resultat dans un vector de string, ou chaque element correspond a un split.
 */
static std::vector<std::string> my_strsplit(std::string str) {
	std::vector<std::string> tab;
	char *cstr = const_cast<char *>(str.c_str());
	char *tmp;

	tmp = strtok(cstr, " \t");
	while (tmp != NULL) {
		tab.push_back(tmp);
		tmp = strtok(NULL, " \t");
	}
	return (tab);
}

/*
 * Ouvre le fichier recu en parametre du programme, le lis.
 * Les lignes sont séparé par les espaces et tabulations, puis stocké dans un tableau de tableau.
 */
static vector_vstr *get_script(char *filename) {
	std::ifstream file;
	std::string buf;
	vector_vstr *script = new vector_vstr;

	file.open(filename, std::ifstream::in);
	if (file.is_open()) {
		while (getline(file, buf)) {
			if (!buf.empty())
				script->push_back(my_strsplit(buf));
		}
		file.close();
		return (script);
	}
	return (NULL);
}

/*
 * Lis depuis l'entrée standard.
 * Les lignes sont séparé par les espaces et tabulations, puis stocké dans un tableau de tableau.
 * La lecture de l'entrée standard s'arrête lorsque la séquence ";;" est trouvé.
 */
static vector_vstr *get_script_by_stdin(void) {
	vector_vstr *tab = new vector_vstr;
	vector_vstr::const_iterator it;
	vector_str::const_iterator tmp;
	bool stop = false;
	std::string buf;

	while (std::cin.good()) {
		getline(std::cin, buf);
		if (!buf.empty())
			tab->push_back(my_strsplit(buf));

		if (!tab->empty()) {
			it = tab->end() - 1;							/* Recup du dernier vector_str (derniere entree user) */
			tmp = it->begin();
			while (tmp != it->end()) {
				if ((*it)[0] == ";;" && (*it).size() == 1)	/* Recherche de la séquence ";;" (Fin entree utilisateur) */
					stop = true;
				tmp++;
			}
			if (stop)										/* Si ";;" est trouvé on stop la saisi */
				break;
		}
	}
	return (tab);
}

int main(int ac, char **av) {
	vector_vstr *script = NULL;
	vector_vstr::const_iterator it;

	if (ac > 1) {
		if (!(script = get_script(av[1])))  /* Recup du programme via un fichier */
			return (0);
	} else
		script = get_script_by_stdin();     /* Recup du programme via STDIN */

	if (script->size() == 0) {              /* Stop si fichier vide */
		DEBUG("File is empty.");
		delete script;
		return (0);
	}

	try {
		AbstractVm *avm = AbstractVm::getInstance();	/* Recuperation de la seule instance possible de avm */
		avm->checkSyntax(*script);						/* Parsing, vérification de la syntaxe */
		avm->execScript(*script);						/* Exécution du script */
		delete avm;
	}
	catch(std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}

	delete script;
	return (0);
}
