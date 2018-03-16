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

std::vector<std::string> *get_script(char *filename)
{
    std::ifstream file;
    std::string buf;
    std::vector<std::string> *config = new std::vector<std::string>;

    file.open(filename, std::ifstream::in);
    if (file.is_open())
    {
        std::cout << "file is open" << std::endl << std::endl;
        while (getline(file, buf))
        {
            if (!buf.empty())
                config->push_back(buf);
        }
        file.close();
        return (config);
    }
    return (NULL);
}

std::vector<std::string> *get_script_by_stdin(void)
{
    std::vector<std::string> *config = NULL;
    config = new std::vector<std::string>;

    /**** SIMULATION ENTREE CLAVIER ****/

    config->push_back(";");
    config->push_back("; FAKE STDIN SCRIPT");
    config->push_back(";");

    config->push_back("push int8(10)");
    config->push_back("push int8(10)");
    config->push_back("add");
    config->push_back("exit");
    config->push_back(";;");

    return (config);
}

int main(int ac, char **av)
{
    std::vector<std::string> *config = NULL;
    std::vector<std::string>::const_iterator it;

    if (!(config = get_script(av[1])))
        config = get_script_by_stdin();

    it = config->begin();
    while (it != config->end())
    {
        std::cout << *it << std::endl;
        it++;
    }


    char str[] ="This,a sample string coucou salut les amis";
    char * pch;
    printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok (str," ,.-");
    while (pch != NULL)
    {
        printf ("%s\n",pch);
        pch = strtok (NULL, " ");
    }


    (void)ac;
    return (0);
}
