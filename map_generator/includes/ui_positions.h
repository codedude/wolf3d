/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_positions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:48:08 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 23:23:42 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_POSITIONS_H
# define UI_POSITIONS_H

/*
**	To clarify reading:
**		C = color
**		P = position
**		OFF = Offset
**		SZ = Size
*/

/*
**	GRID
*/

# define GRID_OFF_X			1
# define GRID_OFF_Y			5
# define GRID_PERC_X		74

# define GRID_SZ_X		(GRID_PERC_X - (GRID_OFF_X * 2))
# define GRID_SZ_Y		(100 - (GRID_OFF_Y * 2))

/*
**	BRUSHES
*/

# define PREV_BOX_PERC		10

# define BRUSH_C_SZ		10
# define BRUSH_OFF_X		(GRID_PERC_X + GRID_OFF_X)
# define BRUSH_OFF_Y		95

# define OBJ_OFF_X			(91)
# define OBJ_OFF_Y			GRID_OFF_Y
# define OBJ_SZ_X			7
# define OBJ_SZ_Y			GRID_SZ_Y

/*
**	MPROPS
*/

# define MPROPS_SZ_X			(MPROPS_B_SZ_X + MPROPS_B_OFF_X * 2 + 2)
# define MPROPS_SZ_Y			(MPROPS_B_SZ_Y + MPROPS_B_OFF_Y * 2 + 6)
# define MPROPS_TOP_P_Y		OBJ_OFF_Y
# define MPROPS_TOP_P_X		(OBJ_OFF_X - (MPROPS_SZ_X + 1))

# define MPROPS_B_SZ_X		4
# define MPROPS_B_SZ_Y		4

# define MPROPS_B_P_LX		(1 + MPROPS_TOP_P_X)
# define MPROPS_B_P_X			(MPROPS_B_P_LX + MPROPS_B_OFF_X)
# define MPROPS_B_P_RX		(MPROPS_B_P_X + MPROPS_B_OFF_X)
# define MPROPS_B_P_Y			(3 + MPROPS_TOP_P_Y)
# define MPROPS_B_OFF_X			(1 + MPROPS_B_SZ_X)
# define MPROPS_B_OFF_Y			(2 + MPROPS_B_SZ_Y)

/*
**	BRUSH_TYPE_BUTTONS
*/

# define B_TYPE_TOP_P_Y		INSPECT_TOP_P_Y
# define B_TYPE_TOP_P_X		INSPECT_TOP_P_X

# define B_TYPE_B_SZ		4

# define B_TYPE_B_P_X		(INSPECT_MID_P_X + 1)
# define B_TYPE_B_P_X2		(INSPECT_MID_P_X - 1 - B_TYPE_B_SZ)
# define B_TYPE_B_P_Y		(4 + B_TYPE_TOP_P_Y)
# define B_TYPE_B_OFF_X		(1 + B_TYPE_B_SZ)
# define B_TYPE_B_OFF_Y		(1 + B_TYPE_B_SZ)

/*
**	INSPECTOR
*/

# define INSPECT_SZ_X	(BUTTON_SZ + BUTTON_OFFSET * 2 + 2)
# define INSPECT_SZ_Y	(BUTTON_TOP_P_Y - (MPROPS_TOP_P_Y + MPROPS_SZ_Y + 4))
# define INSPECT_TOP_P_Y	(MPROPS_TOP_P_Y + (MPROPS_SZ_Y + 2))
# define INSPECT_TOP_P_X	(OBJ_OFF_X - (INSPECT_SZ_X + 1))
# define INSPECT_MID_P_X	(INSPECT_TOP_P_X + INSPECT_SZ_X / 2)

# define BUTTON_SZ			4
# define BUTTON_OFFSET		(BUTTON_SZ + 1)
# define BUTTON_TOP_P_Y		(OBJ_OFF_Y + OBJ_SZ_Y - (BUTTON_SZ * 2) - 1)

/*
**	EDITMOD
*/

# define EDITMOD_SZ_X		INSPECT_SZ_X
# define EDITMOD_SZ_Y		((GRID_OFF_Y + GRID_SZ_Y) - EDITMOD_P_Y)
# define EDITMOD_P_X		INSPECT_TOP_P_X
# define EDITMOD_P_Y		(INSPECT_TOP_P_Y + INSPECT_SZ_Y + 1)
# define EDITMOD_MID_P_X	(EDITMOD_P_X + EDITMOD_SZ_X / 2)
# define EDITMOD_MID_P_Y	(EDITMOD_P_Y + EDITMOD_SZ_Y / 2)

# define EM_B_P_X			(EDITMOD_MID_P_X - (EM_B_SZ_X + 1))
# define EM_B_P_Y			(EDITMOD_MID_P_Y - (EM_B_SZ_Y + 1))
# define EM_B_POS2_X		(EDITMOD_MID_P_X + 1)
# define EM_B_POS2_Y		(EDITMOD_MID_P_Y + 1)

# define EM_B_SZ_X			5
# define EM_B_SZ_Y			3


/*
**	GRID_SNAP_SLIDER
*/

# define G_SNAP_P_Y			(INSPECT_TOP_P_Y + INSPECT_SZ_Y - 6)
# define G_SNAP_P_X			INSPECT_TOP_P_X + 1

# define G_SNAP_S_SZ_X		(INSPECT_SZ_X - 2)
# define G_SNAP_S_SZ_Y		2

# define G_SNAP_C_SZ_X		1
# define G_SNAP_C_SZ_Y		4

/*
**	CHECKBOX_IS_SOLID
*/

# define CB_SOL_P_Y			(G_SNAP_P_Y - (CB_SOL_S_SZ + 5))
# define CB_SOL_P_X			(G_SNAP_P_X + (G_SNAP_S_SZ_X - 1))

# define CB_SOL_S_SZ			3

#endif
