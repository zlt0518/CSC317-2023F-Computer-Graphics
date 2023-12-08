// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  vec4 light = view * vec4(4 * cos( M_PI * animation_seconds/4), 4, 4 * sin(M_PI * animation_seconds/4), 1);

  vec3 v = - normalize(view_pos_fs_in.xyz);
  vec3 l = normalize(light - view_pos_fs_in).xyz;

  // tangent & bump_height & bump_position
  vec3 T, B;
  tangent(sphere_fs_in, T, B);
  float epsilon = 0.0001;
  vec3 bump = bump_position(is_moon, sphere_fs_in);
  vec3 delta_t = (bump_position(is_moon, sphere_fs_in + epsilon * T) - bump) / epsilon;
  vec3 delta_b = (bump_position(is_moon, sphere_fs_in + epsilon * B) - bump) / epsilon;
  
  vec3 n = normalize(cross((bump_position(is_moon, sphere_fs_in + T * epsilon) - bump_position(is_moon, sphere_fs_in))/epsilon, (bump_position(is_moon, sphere_fs_in + B * epsilon) - bump_position(is_moon, sphere_fs_in))/epsilon));

  
  if(is_moon)
  {
    float p = 1000.0;
    vec3 ka = vec3(0.05,0.05,0.05);
    vec3 ks = vec3(1,1,1);  
    vec3 kd = vec3(0.6, 0.5, 0.45);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  else
  {
    float p = 1000.0;
    vec3 ka = vec3(0.05,0.05,0.05);
    vec3 ks = vec3(1,1,1);
    vec3 kd = vec3(0.1, 0.2, 0.7);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
}
