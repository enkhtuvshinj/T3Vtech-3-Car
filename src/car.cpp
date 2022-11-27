#include "crg.hpp"
#include <fstream>

#define CAR_ACC 50.0f //acceleration
#define CAR_RACC -10.0f //reverse acceleration
#define CAR_ROT 0.6f //car turning speed
#define CAR_FRICTION -0.99f //friction value
#define CAR_COLL 0.5f //speed after colliding with something

crg::car::car(unsigned int place, bool is_player, crg::assets& assets)
{
	m_is_player = is_player;
	m_place = place; 
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

void crg::car::update() {
	static tt_vec3 starting_point = {0.0f, 0.0f, 0.0f};
	static bool have_starting_point = false;
	static tt_vec3 end_point = {0.0f, 0.0f, 0.0f};

	static tt_vec3 copied_point = {0.0f, 0.0f, 0.0f};
	static bool have_copied_point = false;

	tt_vec3 vel_delta = tt_math_vec3_mul_float(&m_acc, tt_time_current_frame_s());
	m_vel = tt_math_vec3_add(&m_vel, &vel_delta);
	tt_vec3 pos_delta = tt_math_vec3_mul_float(&m_vel, tt_time_current_frame_s());
	m_pos = tt_math_vec3_add(&m_pos, &pos_delta);
	tt_3d_object_set_position(m_obj, &m_pos);

	m_current_lap_time += tt_time_current_frame_s();

	m_acc.x = 0.0f;
	m_acc.y = 0.0f;
	m_acc.z = 0.0f;

	/* NOTE:
	 * Very idiotic way to store current car positions to a file,
	 * I use it to build the fence lines, so that I don't have to
	 * type the fence positions manually.
	 *
	 * To remove at the very end.
	 * */
	if(m_is_player)
	{
		if (tt_input_keyboard_key_down(TT_KEY_U)) {
			// Save starting point;
			starting_point = m_pos;
			have_starting_point = true;
			printf(
				"Set start point: %.03f, %.03f, %.03f\n",
				starting_point.x, starting_point.y, starting_point.z);
		}
		if (tt_input_keyboard_key_down(TT_KEY_R)) {
			// Save starting point;
			if (have_starting_point) {
				have_starting_point = false;
				end_point = m_pos;

				static std::fstream points{"points.txt", std::ios::in | std::ios::out};
				if (points.is_open()) {
					points
						<< "{{" << starting_point.x << ", "
					       << starting_point.y << ", "
					       << starting_point.z << "}, "
						<< "{" << end_point.x << ", "
					       << end_point.y << ", "
					       << end_point.z << "}},\n";
					printf(
						"Wrote end point: %.03f, %.03f, %.03f\n",
						end_point.x, end_point.y, end_point.z
					);
				}

			} else {
				printf("No Starting point set\n");
			}
		}
		/* Same but for trees. */
		if (tt_input_keyboard_key_down(TT_KEY_C)) {
			// Save starting point;
			copied_point = m_pos;
			have_copied_point = true;
			printf(
				"Copied point: %.03f, %.03f, %.03f\n",
				copied_point.x, copied_point.y, copied_point.z);
		}
		if (tt_input_keyboard_key_down(TT_KEY_P)) {
			// Save starting point;
			if (have_copied_point) {
				have_copied_point = false;

				static std::fstream points{"points_trees.txt", std::ios::in | std::ios::out};
				if (points.is_open()) {
					points
						<< "{{" << copied_point.x << ", "
					       << copied_point.y << ", "
					       << copied_point.z << "}},\n";
					printf(
						"Stored point: %.03f, %.03f, %.03f\n",
						copied_point.x, copied_point.y, copied_point.z
					);
				}

			} else {
				printf("No Copied point set\n");
			}
		}

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
				m_acc = tt_math_vec3_mul_float(&m_acc, CAR_RACC);
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

	//friction
	tt_vec3 friction = tt_math_vec3_mul_float(&m_vel, CAR_FRICTION);
	m_acc = tt_math_vec3_add(&m_acc, &friction);
}

void crg::car::get_position(tt_vec3* pos_out) {
    pos_out->x = m_pos.x;
    pos_out->y = m_pos.y;
    pos_out->z = m_pos.z;
}

void crg::car::set_at_starting_position(crg::track& track)
{
	m_pos = track.get_finish_pos();
	m_pos.z += m_place * 15.0f;
	m_pos.x += m_place%2 * 10.0f;
	m_pos.x -= 12.5f;
	tt_3d_object_set_position(m_obj, &m_pos);
}

void crg::car::colliding_with_car(crg::car& car)
{
	tt_3d_object *other_car = car.get_3d_object();
	if(m_obj == other_car)
	{
		return;
	}

	//checking if there would be a collision in the next frame
	tt_vec3 tmp_pos = tt_math_vec3_mul_float(&m_vel, tt_time_current_frame_s());
	tmp_pos = tt_math_vec3_add(&m_pos, &tmp_pos);
	tt_3d_object_set_position(m_obj, &tmp_pos);
	tt_3d_object *other_obj = car.get_3d_object();
	tt_vec3 vel_other = car.get_vel();
	tt_vec3 pos_other;
	car.get_position(&pos_other);
	tmp_pos = tt_math_vec3_mul_float(&vel_other, tt_time_current_frame_s());
	tmp_pos = tt_math_vec3_add(&pos_other, &tmp_pos);
	tt_3d_object_set_position(other_obj, &tmp_pos);
	if(tt_3d_object_colliding_aabb(m_obj, other_car))
	{
		tt_vec3 vel_other = car.get_vel();
		tt_vec3 vel_coll = tt_math_vec3_add(&m_vel, &vel_other);
		m_vel = tt_math_vec3_mul_float(&vel_coll, 0.5f * CAR_COLL);
		car.set_vel(m_vel); //set the velocity for the other car
		m_vel = tt_math_vec3_mul_float(&m_vel, -1.0f); //setting the direction for this car
		m_acc.x = 0.0f;
		m_acc.y = 0.0f;
		m_acc.z = 0.0f;
	}
	tt_3d_object_set_position(m_obj, &m_pos);
	tt_3d_object_set_position(other_obj, &pos_other);
}

void crg::car::colliding_with_track(crg::track& track)
{
	//checking if there would be a collision in the next frame
	tt_vec3 tmp_pos = tt_math_vec3_mul_float(&m_vel, tt_time_current_frame_s());
	tmp_pos = tt_math_vec3_add(&m_pos, &tmp_pos);
	tt_3d_object_set_position(m_obj, &tmp_pos);
	for(int i = 0; i<track.m_fence.size(); i++)
	{
		if(tt_3d_object_colliding_aabb(m_obj, track.m_fence[i]))
		{
			m_vel = tt_math_vec3_mul_float(&m_vel, -0.5f * CAR_COLL); //setting the direction for this car
			m_acc.x = 0.0f;
			m_acc.y = 0.0f;
			m_acc.z = 0.0f;
			break;
		}
	}
	tt_3d_object_set_position(m_obj, &m_pos);


}