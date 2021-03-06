/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:42:18 by vparis            #+#    #+#             */
/*   Updated: 2019/02/04 14:31:48 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "libft.h"
#include "audio.h"

int			audio_init(t_audio *audio)
{
	int		r;
	int		flags;

	flags = MIX_INIT_OGG | MIX_INIT_MOD;
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		return (audio_error(
			"Mix_OpenAudio: Failed to init audio !"));
	}
	r = Mix_Init(flags);
	if ((r & flags) != flags)
	{
		return (audio_error(
		"Mix_Init: Failed to init required ogg and mod support !"));
	}
	Mix_AllocateChannels(16);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	r = 0;
	while (r < 16)
		Mix_Volume(r++, (int)(MIX_MAX_VOLUME / 1.5));
	return (audio_load_all(audio));
}

static int	audio_load_music(t_audio *audio, char **files)
{
	int		i;

	audio->nb_musics = count_files(files);
	if ((audio->musics = (Mix_Music **)malloc(
		sizeof(Mix_Music *) * (size_t)audio->nb_musics)) == NULL)
		return (ERROR);
	i = 0;
	while (i < audio->nb_musics)
	{
		if ((audio->musics[i] = music_load(files[i])) == NULL)
			return (ERROR);
		++i;
	}
	return (SUCCESS);
}

static int	audio_load_sound(t_audio *audio, char **files)
{
	int		i;

	audio->nb_sounds = count_files(files);
	if ((audio->sounds = (Mix_Chunk **)malloc(
		sizeof(Mix_Chunk *) * (size_t)audio->nb_sounds)) == NULL)
		return (ERROR);
	i = 0;
	while (i < audio->nb_sounds)
	{
		if ((audio->sounds[i] = sound_load(files[i])) == NULL)
			return (ERROR);
		++i;
	}
	return (SUCCESS);
}

int			audio_load_all(t_audio *audio)
{
	if (audio_load_music(audio, music_get_files()) == ERROR
		|| audio_load_sound(audio, sound_get_files()) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void		audio_unload_all(t_audio *audio)
{
	int		i;

	i = 0;
	while (i < audio->nb_sounds)
	{
		Mix_FreeChunk(audio->sounds[i]);
		++i;
	}
	free(audio->sounds);
	i = 0;
	while (i < audio->nb_musics)
	{
		Mix_FreeMusic(audio->musics[i]);
		++i;
	}
	free(audio->musics);
}
