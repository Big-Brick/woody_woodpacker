/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:57:59 by adzikovs          #+#    #+#             */
/*   Updated: 2019/03/29 17:57:59 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void				handler(int signum)
{
	write(1, "Fail!\n", 6);
	exit(0);
}

int					conf_handling(void)
{
	struct sigaction	sig;

	sig.sa_handler = &handler;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGSEGV, &sig, NULL);
	return (0);
}
