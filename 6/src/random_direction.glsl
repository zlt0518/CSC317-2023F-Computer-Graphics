// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction(vec3 seed)
{
  vec2 rand_seed = random2(seed);

  vec3 ret_vector = normalize(vec3(sin(M_PI*rand_seed.x) * cos(2*M_PI*rand_seed.y), sin(M_PI*rand_seed.x) * sin(2*M_PI*rand_seed.y), cos(M_PI*rand_seed.x)));

  return ret_vector;  
}
