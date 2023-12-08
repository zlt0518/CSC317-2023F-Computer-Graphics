// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise( vec3 st) 
{
  //grid cell
  int x_0 = int(floor(st.x));
  int x_1 = x_0 + 1;
  int y_0 = int(floor(st.y));
  int y_1 = y_0 + 1;
  int z_0 = int(floor(st.z));
  int z_1 = z_0 + 1;

  //corner seed
  vec3 s_0 = vec3(x_0, y_0, z_0);
  vec3 s_1 = vec3(x_1, y_0, z_0);
  vec3 s_2 = vec3(x_1, y_1, z_0);
  vec3 s_3 = vec3(x_0, y_1, z_0);
  vec3 s_4 = vec3(x_0, y_0, z_1);
  vec3 s_5 = vec3(x_1, y_0, z_1);
  vec3 s_6 = vec3(x_1, y_1, z_1);
  vec3 s_7 = vec3(x_0, y_1, z_1);

  //gradient vectors using seeds
  vec3 g_v_0 = random_direction(s_0);
  vec3 g_v_1 = random_direction(s_1);
  vec3 g_v_2 = random_direction(s_2);
  vec3 g_v_3 = random_direction(s_3);
  vec3 g_v_4 = random_direction(s_4);
  vec3 g_v_5 = random_direction(s_5);
  vec3 g_v_6 = random_direction(s_6);
  vec3 g_v_7 = random_direction(s_7);

  float g_g_0  = dot(st - s_0, g_v_0);
  float g_g_1  = dot(st - s_1, g_v_1);
  float g_g_2  = dot(st - s_2, g_v_2);
  float g_g_3  = dot(st - s_3, g_v_3);
  float g_g_4  = dot(st - s_4, g_v_4);
  float g_g_5  = dot(st - s_5, g_v_5);
  float g_g_6  = dot(st - s_6, g_v_6);
  float g_g_7  = dot(st - s_7, g_v_7);

  // generate noise on x using mix
  vec3 step_val = improved_smooth_step(st - s_0);

  float interp_x_0 = mix(g_g_0, g_g_1, step_val.x);
  float interp_x_1 = mix(g_g_3, g_g_2, step_val.x);
  float interp_x_2 = mix(g_g_4, g_g_5, step_val.x);
  float interp_x_3 = mix(g_g_7, g_g_6, step_val.x);
  
  // along y axis
  float interp_xy_0 = mix(interp_x_0, interp_x_1, step_val.y);
  float interp_xy_1 = mix(interp_x_2, interp_x_3, step_val.y);

  return mix(interp_xy_0, interp_xy_1, step_val.z);
}

