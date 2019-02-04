/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:11:31 by vparis            #+#    #+#             */
/*   Updated: 2019/02/04 14:14:48 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include "sdl_m.h"

# define MUSIC_FOLDER	"data/music/"
# define SOUND_FOLDER	"data/sound/"

# define MUSIC_TITLE	0

enum {
	SOUND_DASH = 0, SOUND_DOOR_CLOSE = 1, SOUND_DOOR_OPEN, SOUND_EXPLOSION,
	SOUND_FALL_JUMP, SOUND_GRAVEL, SOUND_LEAVES, SOUND_MUD, SOUND_STONE,
	SOUND_WOOD, SOUND_PICKUP, SOUND_DOOR_UNLOCK, SOUND_DOOR_NOKEY
};

typedef struct s_audio	t_audio;

struct				s_audio {
	Mix_Music		**musics;
	Mix_Chunk		**sounds;
	int				nb_musics;
	int				nb_sounds;
	int				current_music;
};

char				**music_get_files(void);
char				**sound_get_files(void);

int					audio_error(char *info);
void				*audio_error_null(char *info);
int					count_files(char **files);

int					audio_init(t_audio *audio);
int					audio_destroy(t_audio *audio);
int					audio_load_all(t_audio *audio);
void				audio_unload_all(t_audio *audio);

Mix_Music			*music_load(char *filename);
Mix_Chunk			*sound_load(char *filename);

int					music_play(t_audio *audio, int id);
void				music_stop(t_audio *audio);

int					sound_play(t_audio *audio, int id);

#endif
