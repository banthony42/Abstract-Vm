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

typedef std::vector<std::vector<std::string> > vector_vstr;
typedef std::vector<std::string> vector_str;

#define DEBUG(str) std::cout << str << std::endl

std::vector<std::string> my_strsplit(std::string str) {
	std::vector<std::string> tab;
	char *cstr = const_cast<char *>(str.c_str());
	char *tmp;

	tmp = strtok(cstr, " ");
	while (tmp != NULL) {
		tab.push_back(tmp);
		tmp = strtok(NULL, " ");
	}
	return (tab);
}

vector_vstr *get_script(char *filename) {
	std::ifstream file;
	std::string buf;
	vector_vstr *config = new vector_vstr;

	file.open(filename, std::ifstream::in);
	if (file.is_open()) {
		DEBUG("file is open");
		while (getline(file, buf)) {
			if (!buf.empty())
				config->push_back(my_strsplit(buf));
		}
		file.close();
		return (config);
	}
	return (NULL);
}

vector_vstr *get_script_by_stdin(void) {
	vector_vstr *tab = new vector_vstr;
	vector_vstr::const_iterator it;
	vector_str::const_iterator tmp;
	std::string buf;

	while (std::cin.good()) {
		getline(std::cin, buf);
		if (!buf.empty())
			tab->push_back(my_strsplit(buf));
		if (tab->empty() == false) {
			it = tab->end() -
				 1;                                /* Recuperation du dernier vector_str (derniere entree utilisateur) */
			tmp = find(it->begin(), it->end(),
					   ";;");           /* Recherche de la séquence ";;" (Fin entree utilisateur) */
			if (tmp != it->end())                               /* Si ";;" est trouvé on stop la saisi */
				break;
		}
	}
	return (tab);
}

int main(int ac, char **av) {
	vector_vstr *config = NULL;
	vector_vstr::const_iterator it;

	if (ac > 1) {
		if (!(config = get_script(av[1])))  /* Recup du programme dans le fichier */
			return (0);
	} else
		config = get_script_by_stdin();     /* Recup du programme via STDIN */


	if (config->size() == 0) {              /* Stop si fichier vide */
		DEBUG("File is empty.");
		delete config;  /* Leaks ? */
		return (0);
	}

	it = config->begin();
	while (it != config->end()) {
		if (it->size())
			std::cout << it->front() << std::endl;
		it++;
	}

	delete config;

	return (0);
}
