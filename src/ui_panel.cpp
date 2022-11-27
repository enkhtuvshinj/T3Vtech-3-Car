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

	m_lap = tt_2d_object_new();
	tt_2d_object_make_sprite(m_lap);
	tt_vec2 lap_pos = {0.0f, 1.0f};
	tt_vec2 lap_size = {0.25f, 0.1f};
	tt_2d_object_set_position(m_lap, &lap_pos);
	tt_2d_object_scale(m_lap, &lap_size);

	m_lap_time = tt_2d_object_new();
	tt_2d_object_make_sprite(m_lap_time);
	tt_vec2 lap_time_pos = {0.0f, 0.90f};
	tt_vec2 lap_time_size = {0.3f, 0.05f};
	tt_2d_object_set_position(m_lap_time, &lap_time_pos);
	tt_2d_object_scale(m_lap_time, &lap_time_size);
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
	float current_lap_time;
	unsigned int current_lap;
	for(int i = 0; i<car.size(); i++) //getting data from the player
	{
		if(car[i].m_is_player)
		{
			place = car[i].get_place();
			vel = car[i].get_vel();
			current_lap = car[i].get_current_lap();
			current_lap_time = car[i].get_current_lap_time();
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
	tt_vec2 speed_pos = {1.0f - (float)((float)speed_str.length()*0.1), 0.15f};
	tt_vec2 speed_size = {(float)((float)speed_str.length()*0.1), 0.15f};
	tt_2d_object_set_position(m_speed, &speed_pos);
	tt_2d_object_scale(m_speed, &speed_size);
	tt_2d_object_render(m_speed);

	//displaying the lap
	std::string lap_str = "Lap: ";
	lap_str += std::to_string(current_lap);
	lap_str += std::string("/");
	lap_str += std::to_string((int)MAX_LAP);
	m_lap_tex = tt_2d_texture_make_text(m_font_big, lap_str.c_str(), place_color);
	tt_2d_object_use_texture(m_lap, m_lap_tex);
	tt_2d_object_render(m_lap);	

	//displaying the current lap time
	std::string lap_time_str = "";
	lap_time_str += std::to_string(current_lap_time);
	lap_time_str += std::string("s");
	m_lap_time_tex = tt_2d_texture_make_text(m_font_big, lap_time_str.c_str(), place_color);
	tt_2d_object_use_texture(m_lap_time, m_lap_time_tex);
	tt_2d_object_render(m_lap_time);	
}