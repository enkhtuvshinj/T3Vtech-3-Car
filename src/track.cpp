#include "crg.hpp"
#include <cmath>

#define FENCE_LENGTH 0.6f
#define TREE_DISTANCE 6.0f

static uint32_t get_random_number_in_range(uint32_t max_bound) {
	return 1 + std::rand()/((RAND_MAX + 1u)/max_bound);
}


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

	//finish/starting line
	m_finish = tt_3d_object_new();
	tt_3d_object_set_position(m_finish, &m_finish_pos);
	tt_3d_object_use_texture(m_finish, assets.finish_tex);
	tt_3d_object_use_custom_model(m_finish, assets.finish_mesh);

	std::vector<std::vector<tt_vec3>> track_lines = {
		{{-129.672, 0, 88.2025}, {-118.527, 0, -5.26465}},
		{{-118.545, 0, -5.11436}, {-129.176, 0, -103.379}},
		{{-129.167, 0, -103.319}, {-94.6283, 0, -174.433}},
		{{-94.586, 0, -174.488}, {41.6933, 0, -183.636}},
		{{41.6672, 0, -183.635}, {138.709, 0, -163.462}},
		{{138.765, 0, -163.424}, {131.316, 0, -116.201}},
		{{131.328, 0, -116.254}, {75.4387, 0, -68.704}},
		{{75.5161, 0, -68.7745}, {87.2467, 0, 12.3364}},
		{{87.2372, 0, 12.2623}, {127.186, 0, 133.337}},
		{{127.203, 0, 133.389}, {1.27825, 0, 183.225}},
		{{1.37212, 0, 183.194}, {-117.48, 0, 132.778}},
		{{-117.48, 0, 132.778}, {-129.672, 0, 88.2025}},

		/* Outer fences. */
		{{-177.466, 0, 85.0413}, {-180.009, 0, 1.75275}},
		{{-180.007, 0, 1.70557}, {-174.877, 0, -85.459}},
		{{-174.88, 0, -85.535}, {-189.898, 0, -170.457}},
		{{-189.905, 0, -170.635}, {-158.501, 0, -214.556}},
		{{-158.466, 0, -214.605}, {-75.3426, 0, -231.09}},
		{{-75.1428, 0, -231.129}, {16.0814, 0, -237.564}},
		{{16.1051, 0, -237.565}, {140.51, 0, -235.478}},
		{{140.594, 0, -235.477}, {206.116, 0, -203.036}},
		{{206.021, 0, -203.085}, {220, 0, -146.477}},
		{{220.023, 0, -146.394}, {213.442, 0, -106.112}},
		{{213.436, 0, -106.077}, {156.053, 0, -57.7697}},
		{{155.957, 0, -57.7003}, {135.591, 0, -33.8707}},
		{{135.555, 0, -33.7787}, {177.073, 0, 53.5841}},
		{{177.098, 0, 53.6351}, {186.938, 0, 136.254}},
		{{186.94, 0, 136.285}, {135.33, 0, 211.101}},
		{{135.298, 0, 211.151}, {15.274, 0, 235.481}},
		{{15.0385, 0, 235.508}, {-112.183, 0, 211.623}},
		{{-112.142, 0, 211.636}, {-158.671, 0, 169.224}},
		{{-158.671, 0, 169.224}, {-177.466, 0, 85.0413}},
	};

	for (auto& line : track_lines) {
		//tt_vec3 start_pos = {-129.672, 0, 88.2025};
		//tt_vec3 end_pos = {-118.527, 0, -5.26465};
		tt_vec3 start_pos = line[0];
		tt_vec3 end_pos = line[1];

		tt_vec3 line_vec = tt_math_vec3_sub(&end_pos, &start_pos);
		float total_length = tt_math_vec3_length(&line_vec);
		line_vec = tt_math_vec3_normalize(&line_vec);

		tt_vec3 ref_frame = {0, 0, -1};

		float angle = std::acos(
			tt_math_vec3_dot(&line_vec, &ref_frame) / 1.0 // Vectors are normalized.
		);

		float fence_length = 0.0f;
		for (int i = 0; total_length > fence_length; ++i) {
			tt_vec3 fence_pos = tt_math_vec3_mul_float(&line_vec, i * FENCE_LENGTH);
			fence_length = tt_math_vec3_length(&fence_pos);
			fence_pos = tt_math_vec3_add(&start_pos, &fence_pos);
			fence_pos.y = -1.0f;

			tt_3d_object *fence = tt_3d_object_new();
			tt_vec3 scale = {1.0f, 6.0f, 1.0f};
			tt_vec3 rot_axis = {0.0f, 1.0f, 0.0f};
			tt_3d_object_scale(fence, &scale);
			tt_3d_object_set_position(fence, &fence_pos);
			tt_3d_object_use_texture(fence, assets.fence_tex);
			tt_3d_object_use_custom_model(fence, assets.fence_mesh);
			tt_3d_object_rotate(fence, &rot_axis, angle);
			m_fence.emplace_back(fence);
		}
	}

	tt_vec3 initial_fence_pos = { -100.0f, -1.0f, -120.0f};
	tt_vec3 initial_tree_pos = {
		initial_fence_pos.x + 1.0f,
		pos.y,  // No increments with respect to track.
		initial_fence_pos.x + 1.0f,
	};
	tt_vec3 tree_pos = initial_tree_pos;


	std::vector<tt_vec3> tree_locations;
	std::vector<tt_3d_texture*> tree1_textures{
		assets.tree1_tex1,
		assets.tree1_tex2,
		assets.tree1_tex3,
		assets.tree1_tex4
	};
	std::vector<float> tree_rotations{
		0.0f * tt_PI,
		0.5f * tt_PI,
		1.0f * tt_PI,
		1.5f * tt_PI,
		2.0f * tt_PI
	};
	std::vector<tt_vec3> tree_scales{
		{1.50f, 1.50f, 1.50f},
		{1.75f, 1.75f, 1.75f},
		{2.00f, 2.00f, 2.00f},
		{2.25f, 2.25f, 2.25f},
		{2.50f, 2.50f, 2.50f},
		{2.75f, 2.75f, 2.75f},
		{3.00f, 3.00f, 3.00f}
	};
	tt_vec3 rot_axis = {0.0f, 1.0f, 0.0f};

	// Create trees.
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 10; ++j) {
			tree_pos.z += TREE_DISTANCE;
			tree_locations.push_back({tree_pos.x, tree_pos.y, tree_pos.z});
		}
		tree_pos.x += TREE_DISTANCE;
		tree_pos.z = initial_tree_pos.z;
	}

	uint32_t tex_idx = 0;
	uint32_t rot_idx = 0;
	uint32_t sca_idx = 0;
	for (auto& tpos: tree_locations) {
		tt_3d_object *tree = tt_3d_object_new();
		tex_idx = get_random_number_in_range(tree1_textures.size()) - 1;
		rot_idx = get_random_number_in_range(tree_rotations.size()) - 1;
		sca_idx = get_random_number_in_range(tree_scales.size()) - 1;

		tt_3d_object_set_position(tree, &tpos);
		tt_3d_object_use_custom_model(tree, assets.tree1_mesh);
		tt_3d_object_use_texture(tree, tree1_textures[tex_idx]);
		tt_3d_object_rotate(tree, &rot_axis, tree_rotations[rot_idx]);
		tt_3d_object_scale(tree, &tree_scales[sca_idx]);
		m_trees.emplace_back(tree);
	}
}

