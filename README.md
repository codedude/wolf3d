# wolf3d

Fonctions les plus gourmandes (ratio) :
- dark_color - 19
- sdl_get_pixel - 8.5
- les fonctions d'effet - 8-10
- compute_depth - 4.5
- sdl_get_texture - 3

Les plus appelées :
1) dark_color, get_pixel, filters, compute_depth (65M)
2) get_textures, get_texture, get_cf_color (39M)
3) floor (sse4, 270k), ultra rapide
4) clamp_int (180k), ultra rapide
5) rc_render et ses découlés, (90k)

Detail :
get_cf_color : 37% fonction, 19% dark_color, 5% get_pixel, 4% get_texture
dark_color : 31% fonction, 12% filter, 4.5% compute depth
filter : 5% compute depth

Solutions :
Améliorer chargement textures + infos, et leur accès
