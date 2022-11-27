#include "crg.hpp"

using namespace crg;

ui_panel::ui_panel()
{
	m_font_big = tt_font_open("assets/Pixellettersfull-BnJ5.ttf", 32);
	m_font_mid = tt_font_open("assets/Pixellettersfull-BnJ5.ttf", 16);
	m_font_small = tt_font_open("assets/Pixellettersfull-BnJ5.ttf", 8);

	m_place = tt_2d_object_new();
	tt_2d_object_make_sprite(m_place);
	tt_vec2 place_pos = {0.75f, 1.0f};
	tt_vec2 place_size = {0.25f, 0.1f};
	tt_2d_object_set_position(m_place, &place_pos);
	tt_2d_object_scale(m_place, &place_size);

	m_speed = tt_2d_object_new();
	tt_2d_object_make_sprite(m_speed);
}

ui_panel::~ui_panel()
{

}

void ui_panel::update(std::vector<crg::car>& car)
{
	tt_color_rgba_u8 place_color = {255, 255, 0, 255};
	std::string place_str = "Place: ";
	unsigned int place = 0;
	tt_vec3 vel;
	for(int i = 0; i<car.size(); i++) //getting data from the player
	{
		if(car[i].m_is_player)
		{
			place = car[i].get_place();
			vel = car[i].get_vel();
		}
	}

	//displaying the current place of the player
	place_str += std::to_string(place);
	m_place_tex = tt_2d_texture_make_text(m_font_big, place_str.c_str(), place_color);
	tt_2d_object_use_texture(m_place, m_place_tex);
	tt_2d_object_render(m_place);

	//displaying the speed
	std::string speed_str;
	unsigned int speed = tt_math_vec3_length(&vel) * 3.6f; //conversion to kmh
	speed_str += std::to_string(speed);
	m_speed_tex = tt_2d_texture_make_text(m_font_big, speed_str.c_str(), place_color);
	tt_2d_object_use_texture(m_speed, m_speed_tex);
	//adjust the size of the speed display according to the speed
	tt_vec2 speed_pos = {1.0f - ((float)speed_str.length()*0.1), 0.15f};
	tt_vec2 speed_size = {((float)speed_str.length()*0.1), 0.15f};
	tt_2d_object_set_position(m_speed, &speed_pos);
	tt_2d_object_scale(m_speed, &speed_size);
	tt_2d_object_render(m_speed);
}