// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
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
// expects: PI, blinn_phong
void main()
{
  vec4 light = view * vec4(4 * cos( M_PI * animation_seconds/4), 4, 4 * sin(M_PI * animation_seconds/4), 1);
  vec3 n = normalize(normal_fs_in);
  vec3 v = - normalize(view_pos_fs_in.xyz);
  vec3 l = normalize(light - view_pos_fs_in).xyz;

  if(is_moon)
  {
    float p = 1000.0;
    vec3 ka = vec3(0.03,0.03,0.03);
    vec3 ks = vec3(1,1,1);  
    vec3 kd = vec3(0.5, 0.5, 0.5);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  else
  {
    float p = 1000.0;
    vec3 ka = vec3(0.03,0.03,0.03);
    vec3 ks = vec3(1,1,1);
    vec3 kd = vec3(0.1, 0.2, 0.7);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
 
}
