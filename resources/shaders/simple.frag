#version 150

in  vec3 pass_Normal;
out vec4 out_Color;

//Assignment 3: Lights
uniform vec3 planetColor; //diffuse color
uniform vec3 ambientColor;
uniform float lightIntensity;
uniform vec3 colorSpecular;
uniform vec3 lightPosition; //light direction
uniform vec3 cameraPosition;
in vec3 passedPosition;

out vec3 passedColor;

void main() {
//Blinn-Phong lightning model
  vec3 viewVec = normalize(cameraPosition - vec3(passedPosition));
  vec3 lightVec = normalize(lightPosition - vec3(passedPosition));  //point to light vector
  vec3 halfVec = normalize(lightVec + viewVec); //half-angle vector between view vector and light vector

  //specular
  float specAngle = max(dot(pass_Normal, halfVec), 0.0f); //angle where light hits surface of planet
  vec3 specular = pow(specAngle, 50) * lightIntensity * colorSpecular;

  //diffuse
  float diffAngle = max(dot(pass_Normal, lightVec), 0.0f);
  vec3 diffuse = diffAngle * lightIntensity * planetColor;

  //addition of light
  out_Color = vec4((ambientColor + diffuse + specular), 1.0);

}
