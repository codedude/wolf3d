/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:19:11 by vparis            #+#    #+#             */
/*   Updated: 2019/02/04 14:31:44 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "libft.h"
#include "audio.h"

int			audio_error(char *info)
{
	ft_putendl_fd(info, 2);
	ft_putendl_fd(Mix_GetError(), 2);
	return (ERROR);
}

void		*audio_error_null(char *info)
{
	ft_putendl_fd(info, 2);
	ft_putendl_fd(Mix_GetError(), 2);
	return (NULL);
}

int			count_files(char **files)
{
	int	n;

	n = 0;
	while (*files != NULL)
	{
		++n;
		++files;
	}
	return (n);
}

int			audio_destroy(t_audio *audio)
{
	audio_unload_all(audio);
	Mix_CloseAudio();
	while (Mix_Init(0))
		Mix_Quit();
	return (SUCCESS);
}
