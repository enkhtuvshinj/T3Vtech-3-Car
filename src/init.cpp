#include "crg.hpp"

void crg::init()
{
	tt_init("Wild Racing Game", 1366, 768, false, 0, NULL);

	//setting general lighting properties
	tt_gfx_gouraud_shading(true);
	tt_gfx_phong_shading(false);
}