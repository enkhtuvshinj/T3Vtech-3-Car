#include "crg.hpp"

#define CAR_ACC 3.0f
#define CAR_ROT 0.6f

crg::car::car(bool is_player, tt_vec3& pos, crg::assets& assets)
{
	m_is_player = is_player;
	m_pos = pos;

	m_obj = tt_3d_object_new();

	//player
	if(m_is_player)
	{
		tt_3d_object_use_custom_model(m_obj, assets.car_mesh);
		tt_3d_object_use_texture(m_obj, assets.car_tex);
		tt_3d_object_set_position(m_obj, &m_pos);
	}
	//npc
	else 
	{
		tt_3d_object_use_custom_model(m_obj, assets.npc_car_mesh);
		tt_3d_object_set_position(m_obj, &m_pos);
	    tt_3d_object_use_texture(m_obj, assets.npc_car_tex);
		tt_3d_object_back_face_culling(m_obj, false); //the model looks weird otherwise
	}
}

crg::car::~car()
{

}

void crg::car::update()
{
	tt_vec3 vel_delta = tt_math_vec3_mul_float(&m_acc, tt_time_current_frame_s());
	m_vel = tt_math_vec3_add(&m_vel, &vel_delta);
	tt_vec3 pos_delta = tt_math_vec3_mul_float(&m_vel, tt_time_current_frame_s());
	m_pos = tt_math_vec3_add(&m_pos, &pos_delta);
	tt_3d_object_set_position(m_obj, &m_pos);

	if(m_is_player)
	{
		//accelerating the car
		if(tt_input_keyboard_key_down(TT_KEY_W) ||
			tt_input_keyboard_key_down(TT_KEY_S))
		{
			m_acc = tt_math_vec3_normalize(&m_dir);
			if(tt_input_keyboard_key_down(TT_KEY_W))
			{
				m_acc = tt_math_vec3_mul_float(&m_acc, CAR_ACC);				
			}
			else
			{
				m_acc = tt_math_vec3_mul_float(&m_acc, -CAR_ACC);
			}
		}
		else
		{
			if(tt_math_vec3_length(&m_vel) > 0.0f)
			{
				m_acc = tt_math_vec3_normalize(&m_vel);
				m_acc = tt_math_vec3_mul_float(&m_acc, -5.0f);				
			}
			if(	tt_math_vec3_length(&m_vel) < 0.01f)
			{
				m_vel.x = 0.0f;
				m_vel.y = 0.0f;
				m_vel.z = 0.0f;
			}
		}
		//turning the car
		if(tt_input_keyboard_key_down(TT_KEY_A))
		{
			m_dir.x *= -1.0f;
			tt_vec3 rot_axis = {0.0f, 1.0f, 0.0f};
			float radians = CAR_ROT * tt_time_current_frame_s();
			m_dir = tt_math_vec3_rotate(
				&rot_axis, 
				radians,
				&m_dir);
			tt_3d_object_rotate(m_obj, &rot_axis, radians);
			tt_camera_rotate(&rot_axis, -radians);
			m_dir.x *= -1.0f;
		}
		if(tt_input_keyboard_key_down(TT_KEY_D))
		{
			m_dir.x *= -1.0f;
			tt_vec3 rot_axis = {0.0f, 1.0f, 0.0f};
			float radians = -CAR_ROT * tt_time_current_frame_s();
			m_dir = tt_math_vec3_rotate(
				&rot_axis, 
				radians,
				&m_dir);
			tt_3d_object_rotate(m_obj, &rot_axis, radians);
			tt_camera_rotate(&rot_axis, -radians);
			m_dir.x *= -1.0f;
		}

		//positioning the camera
		tt_vec3 cam_pos_delta = tt_math_vec3_mul_float(&m_dir, -7.5f);
		tt_vec3 cam_pos = tt_math_vec3_add(&m_pos, &cam_pos_delta);
		cam_pos.y += 2.0f;
		tt_camera_set_position(&cam_pos);
	}
}

void crg::car::get_position(tt_vec3* pos_out) {
    pos_out->x = m_pos.x;
    pos_out->y = m_pos.y;
    pos_out->z = m_pos.z;
}

