#include "crg.hpp"

#define FENCE_LENGTH 0.6f

crg::track::track(crg::assets& assets)
{
	m_obj = tt_3d_object_new();
	tt_3d_object_make_cube(m_obj);

	tt_vec3 scale = {500.0f, 0.1f, 500.0f};
	tt_vec3 pos = {0.0f, -2.0f, 0.0f};
	tt_3d_object_scale(m_obj, &scale);
	tt_3d_object_set_position(m_obj, &pos);

	tt_3d_object_use_texture(m_obj, assets.track_tex);
	tt_3d_object_back_face_culling(m_obj, false);

	//create fences
	//inner border of the track
	for(int i = 0; i < 400; i++)
	{
		//left side
		tt_3d_object *fence = tt_3d_object_new();
		tt_vec3 fence_pos = {-100.0f, -1.0f, -120.0f + i * FENCE_LENGTH};
		tt_vec3 scale = {1.0f, 4.0f, 1.0f};
		tt_vec3 rot_axis = {0.0f, 1.0f, 0.0f};
		tt_3d_object_scale(fence, &scale);
		tt_3d_object_set_position(fence, &fence_pos);
		tt_3d_object_use_texture(fence, assets.fence_tex);
		tt_3d_object_use_custom_model(fence, assets.fence_mesh);
		m_fence.emplace_back(fence);

		//right side
		fence_pos.x = 40.0f;
		fence = tt_3d_object_new();
		tt_3d_object_scale(fence, &scale);
		tt_3d_object_rotate(fence, &rot_axis, 1.0f * tt_PI);
		tt_3d_object_set_position(fence, &fence_pos);
		tt_3d_object_use_texture(fence, assets.fence_tex);
		tt_3d_object_use_custom_model(fence, assets.fence_mesh);
		m_fence.emplace_back(fence);		
	}
	for(int i = 0; i < 233; i++)
	{
		//bottom
		tt_3d_object *fence = tt_3d_object_new();
		tt_vec3 fence_pos = {-100.0f + i * FENCE_LENGTH, -1.0f, -120.0f};
		tt_vec3 rot_axis = {0.0f, 1.0f, 0.0f};
		tt_vec3 scale = {1.0f, 4.0f, 1.0f};
		tt_3d_object_scale(fence, &scale);
		tt_3d_object_rotate(fence, &rot_axis, 1.5f * tt_PI);
		tt_3d_object_set_position(fence, &fence_pos);
		tt_3d_object_use_texture(fence, assets.fence_tex);
		tt_3d_object_use_custom_model(fence, assets.fence_mesh);
		m_fence.emplace_back(fence);

		//top
		fence_pos.z = 120.0f;
		fence = tt_3d_object_new();
		tt_3d_object_scale(fence, &scale);
		tt_3d_object_rotate(fence, &rot_axis, 0.5f * tt_PI);
		tt_3d_object_set_position(fence, &fence_pos);
		tt_3d_object_use_texture(fence, assets.fence_tex);
		tt_3d_object_use_custom_model(fence, assets.fence_mesh);
		m_fence.emplace_back(fence);	
	}
}
