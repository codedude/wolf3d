/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:22:38 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 10:58:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "types.h"
#include "ft_type.h"
#include "libft.h"
#include "audio.h"

char		**sound_get_files(void)
{
	static char	*sound_files[] = {
		"dash.ogg",
		"door_close.ogg",
		"door_open.ogg",
		"explosion.ogg",
		"fall_jump.ogg",
		"gravel.ogg",
		"leaves.ogg",
		"mud.ogg",
		"stone.ogg",
		"wood.ogg",
		"pickup_key.ogg",
		"guitar.ogg",
		"door_nokey.ogg",
		NULL
	};

	return ((char **)sound_files);
}

Mix_Chunk	*sound_load(char *filename)
{
	Mix_Chunk	*chunk;
	char		*file;

	file = concat_path_file(SOUND_FOLDER, filename);
	chunk = Mix_LoadWAV(file);
	free(file);
	if (!chunk)
	{
		return (audio_error_null(
			"Mix_LoadWAV : can't load chunk"));
	}
	Mix_VolumeChunk(chunk, MIX_MAX_VOLUME / 2);
	return (chunk);
}

int			sound_play(t_audio *audio, int id)
{
	if (Mix_PlayChannel(-1, audio->sounds[id], 0) == -1)
		return (audio_error("Can't play sound"));
	return (SUCCESS);
}
