#include "crg.hpp"


int main(int argc, char *argv[])
{
	crg::init();

	crg::assets assets;

	//creating player car
	tt_vec3 player_pos = {0.0f, 0.0f, 0.0f};
	crg::car car(true, player_pos, assets);

	tt_vec3 npc_pos = {-1.5f, 0.0f, 6.0f};
	crg::npc npc(npc_pos, assets);

	crg::track track(assets);

    tt_vec3 light_col={0.5f, 0.3f, 0.03f};
    tt_vec3 light_pos={-20.0f, 10.0f, -50.0f};
    tt_point_light light=tt_point_light_new();
    tt_point_light_set_color(light, &light_col);
    tt_point_light_set_position(light, &light_pos);
    tt_point_light_set_strength(light, 2500.0f);

	while(!tt_input_keyboard_key_press(TT_KEY_ESC))
	{
		car.update();
		tt_new_frame();
	}

	return 0;
}
