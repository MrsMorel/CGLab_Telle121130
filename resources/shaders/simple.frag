#version 150

in  vec3 pass_Normal;
out vec4 out_Color;

//Assignment 3: Lights
uniform vec3 planetColor; //diffuse color
uniform vec3 ambientColor; //planet color
uniform float lightIntensity;
uniform vec3 colorSpecular;
uniform vec3 lightPosition; //light direction
uniform vec3 cameraPosition;
in vec4 passedPosition;

//Newly add(Cel-Shading)
vec3 color1 = vec3(1.0,0.0,0.0);
vec3 color2 = vec3(0.0,1.0,0.0);
vec3 color3 = vec3(0.0,0.0,1.0);
float threshold1 = 0.6;
float threshold2 = 0.3;
out vec3 passedColor;
//Newly add(Cel-Shading)
out vec3 celShadingColor;

//Assignment 4:
in vec2 passedTexturePoint;
uniform sampler2D YourTexture;


void main() {
//Blinn-Phong lightning model
  vec3 viewVec = normalize(cameraPosition - vec3(passedPosition));
  vec3 lightVec = normalize(lightPosition - vec3(passedPosition));  //point to light vector
  vec3 halfVec = normalize(lightVec + viewVec); //half-angle vector between view vector and light vector

  //specular
  float specAngle = max(dot(pass_Normal, halfVec), 0.0f); //angle where light hits surface of planet
  vec3 specular = pow(specAngle, 10) * lightIntensity * colorSpecular;

  //diffuse
  float diffAngle = max(dot(pass_Normal, lightVec), 0.0f);
  vec3 diffuse = diffAngle * lightIntensity * planetColor;

  //texture color
  vec3 texture_color = texture2D(YourTexture, passedTexturePoint).xyz;

  //addition of light
  out_Color = vec4((texture_color +  texture_color * diffuse + specular), 1.0);


}

//Newly add(Cel-Shading)
/*
float calculateBrightness(vec3 color){
  float brightness = (color.r + color.g + color.b)/3;
  return brightness;
}

vec3 discretizeColor(float brightness){
  if(brightness > threshold1){
    return color1;
  }
  else if(brightness > threshold2){
    return color2;
  }
  else{
    return color3;
  }
}*/