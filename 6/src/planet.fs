// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  vec4 light = view * vec4(4 * cos( M_PI * animation_seconds/4), 4, 4 * sin(M_PI * animation_seconds/4), 1);

  vec3 v = - normalize(view_pos_fs_in.xyz);
  vec3 l = normalize(light - view_pos_fs_in).xyz;
  float p = 750.0;

  // tangent & bump_height & bump_position
  vec3 T, B;
  tangent(sphere_fs_in, T, B);
  float epsilon = 0.0001;
  vec3 bump = bump_position(is_moon, sphere_fs_in);
  vec3 delta_t = (bump_position(is_moon, sphere_fs_in + epsilon * T) - bump) / epsilon;
  vec3 delta_b = (bump_position(is_moon, sphere_fs_in + epsilon * B) - bump) / epsilon;
  
  vec3 n = normalize(cross((bump_position(is_moon, sphere_fs_in + T * epsilon) - bump_position(is_moon, sphere_fs_in))/epsilon, (bump_position(is_moon, sphere_fs_in + B * epsilon) - bump_position(is_moon, sphere_fs_in))/epsilon));

  // using turbulence function from textbook 
  float omega = 7; 
  float w = 7;
  float k1 = 15; 
  float k2 = 5; 
  float noise1 = sqrt( abs (1 + sin( sphere_fs_in.x + k1 * improved_perlin_noise(k2 * sphere_fs_in) ) / w) );
  float noise2 = (1 + sin(k1 * (sphere_fs_in.x/3 + sphere_fs_in.y/3.2 + sphere_fs_in.z/5) + improved_perlin_noise(k2 * sphere_fs_in)) / omega) / 2;
  float noise = noise1*noise2;

  if(is_moon)
  {
    //moon
    vec3 ka = vec3(0.05,0.05,0.05);
    vec3 ks = vec3(1,1,1);  
    vec3 kd = vec3(0.6, 0.6, 0.6);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  else
  {

    if(bump_height(is_moon, sphere_fs_in) > 0){
      //land
      vec3 ka = vec3(0.282, 0.722, 0.573);
      vec3 kd = mix(vec3(0.1, 0.2, 0.7), vec3(3), noise)+ 5* improved_perlin_noise((rotate_about_y(animation_seconds * M_PI/4) * vec4(sphere_fs_in, 1)).xyz);
      vec3 ks = vec3(1,1,1);
      color = blinn_phong(ka, kd, ks, p, n, v, l);
    }
    else
    {
      //sea
      vec3 ka = vec3(0.01, 0.2, 0.81);
      vec3 kd = mix(vec3(0.2, 0.2, 0.6), vec3(3), noise)+3* improved_perlin_noise((rotate_about_y(animation_seconds * M_PI/4) * vec4(sphere_fs_in, 1)).xyz);
      vec3 ks = vec3(1,1,1);
      color = blinn_phong(ka, kd, ks, p, n, v, l);
    }

  }    
}










