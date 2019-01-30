/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:22:42 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:18:41 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "types.h"
#include "ft_type.h"
#include "audio.h"

char		**music_get_files(void)
{
	static char	*music_files[] = {
		"chip.ogg",
		NULL
	};

	return ((char **)music_files);
}

Mix_Music	*music_load(char *filename)
{
	Mix_Music	*music;
	char		*file;

	file = concat_path_file(MUSIC_FOLDER, filename);
	music = Mix_LoadMUS(file);
	free(file);
	if (!music)
	{
		return (audio_error_null(
			"Mix_LoadMUS : can't load music"));
	}
	return (music);
}

int			music_play(t_audio *audio, int id)
{
	if (audio->current_music != -1)
		music_stop(audio);
	if (Mix_PlayMusic(audio->musics[id], -1) == -1)
		return (audio_error("Can't play music"));
	audio->current_music = id;
	return (SUCCESS);
}

void		music_stop(t_audio *audio)
{
	Mix_FadeOutMusic(2000);
	audio->current_music = -1;
}
