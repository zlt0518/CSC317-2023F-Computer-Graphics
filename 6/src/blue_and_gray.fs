// Set the pixel color to blue or gray depending on is_moon.
//
// Uniforms:
uniform bool is_moon;
// Outputs:
out vec3 color;
void main()
{
  if(is_moon)
  {
    color = vec3(0.51, 0.51, 0.51);//grey
  }
  else
  {
    color = vec3(0.239, 0.286, 0.769);//blue
  }
}
