// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
//reference: https://en.wikipedia.org/wiki/Perlin_noise and https://www.youtube.com/watch?v=7fd331zsie0
float perlin_noise( vec3 st) 
{
  //grid cell
  int x_0 = int(floor(st.x));
  int x_1 = x_0 + 1;
  int y_0 = int(floor(st.y));
  int y_1 = y_0 + 1;
  int z_0 = int(floor(st.z));
  int z_1 = z_0 + 1;

  //seeds
  vec3 s_0 = vec3(x_0, y_0, z_0);
  vec3 s_1 = vec3(x_1, y_0, z_0);
  vec3 s_2 = vec3(x_0, y_1, z_0);
  vec3 s_3 = vec3(x_0, y_0, z_1);
  vec3 s_4 = vec3(x_1, y_1, z_0);
  vec3 s_5 = vec3(x_1, y_0, z_1);
  vec3 s_6 = vec3(x_0, y_1, z_1);
  vec3 s_7 = vec3(x_1, y_1, z_1);

  //gradient vectors using seeds
  vec3 g_v_0 = random_direction(s_0);
  vec3 g_v_1 = random_direction(s_1);
  vec3 g_v_2 = random_direction(s_2);
  vec3 g_v_3 = random_direction(s_3);
  vec3 g_v_4 = random_direction(s_4);
  vec3 g_v_5 = random_direction(s_5);
  vec3 g_v_6 = random_direction(s_6);
  vec3 g_v_7 = random_direction(s_7);

  //grid_grident
  float g_g_0 = dot( g_v_0, st - s_0 );
  float g_g_1 = dot( g_v_1, st - s_1 );
  float g_g_2 = dot( g_v_2, st - s_2 );
  float g_g_3 = dot( g_v_3, st - s_3 );
  float g_g_4 = dot( g_v_4, st - s_4 );
  float g_g_5 = dot( g_v_5, st - s_5 );
  float g_g_6 = dot( g_v_6, st - s_6 );
  float g_g_7 = dot( g_v_7, st - s_7 );

  // generate noise on x using mix
  vec3 steps = smooth_step(st - s_0);

  float interp_x_0 = mix(g_g_0, g_g_1, steps.x);
  float interp_x_1 = mix(g_g_2, g_g_3, steps.x);
  float interp_x_2 = mix(g_g_4, g_g_5, steps.x);
  float interp_x_3 = mix(g_g_6, g_g_7, steps.x);

  float interp_xy_0 = mix(interp_x_0,interp_x_1, steps.y);
  float interp_xy_1 = mix(interp_x_2,interp_x_3, steps.y);

  return mix(interp_xy_0,interp_xy_1, steps.z);

}

