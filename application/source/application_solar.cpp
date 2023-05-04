#include "application_solar.hpp"
#include "window_handler.hpp"

#include "utils.hpp"
#include "shader_loader.hpp"
#include "model_loader.hpp"


#include <glbinding/gl/gl.h>
// use gl definitions from glbinding 
using namespace gl;

//don't load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

ApplicationSolar::ApplicationSolar(std::string const& resource_path)
 :Application{resource_path}
 ,sceneGraph_{}
 ,planet_object{}
 ,m_view_transform{glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 4.0f})}, m_view_projection{utils::calculate_projection_matrix(initial_aspect_ratio)}
{
  initializeSceneGraph();
  initializeGeometry();
  initializeShaderPrograms();
}

ApplicationSolar::~ApplicationSolar() {
  glDeleteBuffers(1, &planet_object.vertex_BO);
  glDeleteBuffers(1, &planet_object.element_BO);
  glDeleteVertexArrays(1, &planet_object.vertex_AO);
}

void ApplicationSolar::render() const {
    //TODO Render Planets correctly
    //making new list for only planets
    std::vector<std::shared_ptr<Node>> planets;
    // pushing planet nodes into new list
    planets.push_back(sceneGraph_.getRoot().getChildren("Mercury"));
    planets.push_back(sceneGraph_.getRoot().getChildren("Venus"));
    planets.push_back(sceneGraph_.getRoot().getChildren("Mercury"));
    planets.push_back(sceneGraph_.getRoot().getChildren("Earth"));
    planets.push_back(sceneGraph_.getRoot().getChildren("Moon"));
    planets.push_back(sceneGraph_.getRoot().getChildren("Mars"));
    planets.push_back(sceneGraph_.getRoot().getChildren("Jupiter"));
    planets.push_back(sceneGraph_.getRoot().getChildren("Saturn"));
    planets.push_back(sceneGraph_.getRoot().getChildren("Uranus"));
    planets.push_back(sceneGraph_.getRoot().getChildren("Neptun"));

    for ( const std::shared_ptr<Node>& i : planets) {

        glm::mat4 matrix_render; //solution after rotation
        // bind shader to upload uniforms
        glUseProgram(m_shaders.at("planet").handle);

        if (i->getName() != "Moon"){ //all the planets (moon is not a planet)
            std::shared_ptr<Node> planetGeo = i->getChildren(i->getName()+"G"); //getting geometry of planet
            //rotate identity matrix

            glm::mat4 matrix_rotation = glm::rotate(glm::fmat4{}, float(glfwGetTime()) , glm::vec3{0.0f,1.0f,0.0f}); //float cast or else function doesn't work
            i->setLocalTransform(matrix_rotation * i->getWorldTransform());
            matrix_render = glm::rotate(i->getLocalTransform(),float(glfwGetTime()), glm::vec3{0.0f,1.0f,0.0f}); //matrix for rendering with computed local transformation matrix
            //TODO update the parent transform
            //TODO do nt get the parent new world transform
        } else { //Moon render
            std::shared_ptr<Node> moonGeo = i->getChildren("MoonG"); //getting geometry
            glm::mat4 matrix_rotation = glm::rotate(glm::fmat4{}, float(glfwGetTime()), glm::vec3{0.0f,1.0f,0.0f}); //float cast or else function doesn't work
            i->setLocalTransform(matrix_rotation * i->getWorldTransform());
            //i->setLocalTransform( matrix_rotation * moonGeo->getLocalTransform()); //multiplying rotation matrix with moon geometry local transform for translating
            matrix_render = glm::rotate(i->getLocalTransform(),float(glfwGetTime()), glm::vec3{0.0f,1.0f,0.0f}); //matrix for rendering with computed local transformation matrix
        }
        //uniformmatrix with matrix_render solution
        glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
                           1, GL_FALSE, glm::value_ptr(matrix_render));
        //bind the VAO to draw
        glBindVertexArray(planet_object.vertex_AO);
        //draw bound vertex array using bound shader
        glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);

    }
    // bind shader to upload uniforms
    glUseProgram(m_shaders.at("planet").handle);
    glm::fmat4 model_matrix = glm::rotate(glm::fmat4{}, float(glfwGetTime()), glm::fvec3{0.0f, 0.0f, 1.0f});
    model_matrix = glm::translate(model_matrix, glm::fvec3{0.0f, 0.0f, -1.0f});

    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
                       1, GL_FALSE, glm::value_ptr(model_matrix));
    // extra matrix for normal transformation to keep them orthogonal to surface
    glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix);
    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"),
                       1, GL_FALSE, glm::value_ptr(normal_matrix));
    // bind the VAO to draw
    glBindVertexArray(planet_object.vertex_AO);

    // draw bound vertex array using bound shader
    glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);




}

void ApplicationSolar::uploadView() {
  // vertices are transformed in camera space, so camera transform must be inverted
  glm::fmat4 view_matrix = glm::inverse(m_view_transform);
  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ViewMatrix"),
                     1, GL_FALSE, glm::value_ptr(view_matrix));
}

void ApplicationSolar::uploadProjection() {
  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ProjectionMatrix"),
                     1, GL_FALSE, glm::value_ptr(m_view_projection));
}

// update uniform locations
void ApplicationSolar::uploadUniforms() { 
  // bind shader to which to upload unforms
  glUseProgram(m_shaders.at("planet").handle);
  // upload uniform values to new locations
  uploadView();
  uploadProjection();
}

///////////////////////////// intialisation functions /////////////////////////
// load shader sources
void ApplicationSolar::initializeShaderPrograms() {
  // store shader program objects in container
  m_shaders.emplace("planet", shader_program{{{GL_VERTEX_SHADER,m_resource_path + "shaders/simple.vert"},
                                           {GL_FRAGMENT_SHADER, m_resource_path + "shaders/simple.frag"}}});
  // request uniform locations for shader program
  m_shaders.at("planet").u_locs["NormalMatrix"] = -1;
  m_shaders.at("planet").u_locs["ModelMatrix"] = -1;
  m_shaders.at("planet").u_locs["ViewMatrix"] = -1;
  m_shaders.at("planet").u_locs["ProjectionMatrix"] = -1;
}

// load models
void ApplicationSolar::initializeGeometry() {
  model planet_model = model_loader::obj(m_resource_path + "models/sphere.obj", model::NORMAL);

  // generate vertex array object
  glGenVertexArrays(1, &planet_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(planet_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &planet_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, planet_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planet_model.data.size(), planet_model.data.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
  // activate second attribute on gpu
  glEnableVertexAttribArray(1);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::NORMAL]);

   // generate generic buffer
  glGenBuffers(1, &planet_object.element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * planet_model.indices.size(), planet_model.indices.data(), GL_STATIC_DRAW);

  // store type of primitive to draw
  planet_object.draw_mode = GL_TRIANGLES;
  // transfer number of indices to model object 
  planet_object.num_elements = GLsizei(planet_model.indices.size());
}

///////////////////////////// callback functions for window events ////////////
// handle key input
void ApplicationSolar::keyCallback(int key, int action, int mods) {
  if (key == GLFW_KEY_W  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, -0.1f});
    uploadView();
  }
  else if (key == GLFW_KEY_S  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, 0.1f});
    uploadView();
  }
  else if (key == GLFW_KEY_A  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      m_view_transform = glm::translate(m_view_transform, glm::fvec3{-0.1f, 0.0f, 0.0f});
      uploadView();
  }
  else if (key == GLFW_KEY_D  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.1f, 0.0f, 0.1f});
      uploadView();
  }
}

//handle delta mouse movement input
void ApplicationSolar::mouseCallback(double pos_x, double pos_y) {
  // mouse handling
  //imagine dividing window with coordinate system in the middle -> 4 cases
  /*
    if (pos_x > 0 && pos_y > 0){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.01f, 0.01f,0.0f});
        uploadView();
    }
    if (pos_x < 0 && pos_y > 0){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{-0.01f, 0.01f,0.0f});
        uploadView();
    }
    if (pos_y < 0 && pos_x > 0){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.01f, -0.01f,0.0f});
        uploadView();
    }
    if (pos_y < 0 && pos_x < 0){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{-0.01f, -0.01f,0.0f});
        uploadView();
    }*/
    if (pos_x > 0){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{-0.01f, 0.0f,0.0f});
        uploadView();
    }
    if (pos_x < 0){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.01f, 0.0f,0.0f});
        uploadView();
    }
    if (pos_y > 0){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.01f,0.0f});
        uploadView();
    }
    if (pos_y < 0){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, -0.01f,0.0f});
        uploadView();
    }
}

//handle resizing
void ApplicationSolar::resizeCallback(unsigned width, unsigned height) {
  // recalculate projection matrix for new aspect ration
  m_view_projection = utils::calculate_projection_matrix(float(width) / float(height));
  // upload new projection matrix
  uploadProjection();
}

//function to connect scenegraph to application
void ApplicationSolar::initializeSceneGraph() {
//root node
    Node root{"Root",glm::translate({},glm::vec3{0.0f,0.0f,0.0f}), glm::translate( {}, glm::vec3{1.0f, 0.0f, 0.0f})};
//Point Light
    PointLightNode pointLightNode;
    GeometryNode sunGeometry; //TODO
    root.addChild(std::make_shared<Node>(pointLightNode));
//Camera
    CameraNode cameraNode{}; //TODO
    root.addChild(std::make_shared<Node>(cameraNode));

//Mercury
    Node mercuryNode("Mercury" ,glm::translate({},glm::vec3{5.79f,0.0f,0.0f}),  std::make_shared<Node>(root));
    GeometryNode mercuryGeo("MercuryG", glm::translate({},glm::vec3{5.79f,0.0f,0.0f}), std::make_shared<Node>(mercuryNode));
    //geoNode do not translate
    mercuryNode.addChild(std::make_shared<Node>(mercuryGeo)); //adding geonode to planetnode
    root.addChild(std::make_shared<Node>(mercuryNode)); //adding node to root
//Venus
    Node venusNode("Venus" ,glm::translate({},glm::vec3{10.82f,0.0f,0.0f}),  std::make_shared<Node>(root));
    GeometryNode venusGeo("VenusG", glm::translate({},glm::vec3{10.82f,0.0f,0.0f}), std::make_shared<Node>(venusNode));
    venusNode.addChild(std::make_shared<Node>(venusGeo));//adding geonode to planetnode
    root.addChild(std::make_shared<Node>(venusNode));//adding node to root


//Earth
    Node earthNode("Earth" ,glm::translate({},glm::vec3{14.96f,0.0f,0.0f}),  std::make_shared<Node>(root));
    GeometryNode earthGeo("EarthG" ,glm::translate({},glm::vec3{14.96f,0.0f,0.0f}),  std::make_shared<Node>(earthNode));
    earthNode.addChild(std::make_shared<Node>(earthGeo));

//Moon TODO
//parent relation not right
    Node moonNode("Moon" ,glm::translate({},glm::vec3{10.0f,0.0f,0.0f}),  std::make_shared<Node>(earthNode)); //moon has earth as parent node
    GeometryNode moonGeo("MoonG" ,glm::translate({},glm::vec3{10.0f,0.0f,0.0f}),  std::make_shared<Node>(moonNode));
    moonNode.addChild(std::make_shared<Node>(moonGeo));
    earthNode.addChild(std::make_shared<Node>(moonNode)); //earth node holds moon node
    root.addChild(std::make_shared<Node>(earthNode));

//Mars
    Node marsNode("Mars" ,glm::translate({},glm::vec3{22.8f,0.0f,0.0f}),  std::make_shared<Node>(root));
    GeometryNode marsGeo("MarsG" ,glm::translate({},glm::vec3{22.8f,0.0f,0.0f}),  std::make_shared<Node>(marsNode));
    marsNode.addChild(std::make_shared<Node>(marsGeo));
    root.addChild(std::make_shared<Node>(marsNode));


//Jupiter
    Node jupiterNode("Jupiter" ,glm::translate({},glm::vec3{77.85f,0.0f,0.0f}),  std::make_shared<Node>(root));
    GeometryNode jupiterGeo("JupiterG" ,glm::translate({},glm::vec3{77.85f,0.0f,0.0f}),  std::make_shared<Node>(jupiterNode));
    jupiterNode.addChild(std::make_shared<Node>(jupiterGeo));
    root.addChild(std::make_shared<Node>(jupiterNode));

//Saturn
    Node saturnNode("Saturn" ,glm::translate({},glm::vec3{143.2f,0.0f,0.0f}), std::make_shared<Node>(root));
    GeometryNode saturnGeo("SaturnG" ,glm::translate({},glm::vec3{143.2f,0.0f,0.0f}),  std::make_shared<Node>(saturnNode));
    saturnNode.addChild(std::make_shared<Node>(saturnGeo));
    root.addChild(std::make_shared<Node>(saturnNode));

//Uranus
    Node uranusNode("Uranus" ,glm::translate({},glm::vec3{250.0f,0.0f,0.0f}),  std::make_shared<Node>(root));
    GeometryNode uranusGeo("UranusG" ,glm::translate({},glm::vec3{250.0f,0.0f,0.0f}),  std::make_shared<Node>(uranusNode));
    uranusNode.addChild(std::make_shared<Node>(uranusGeo));
    root.addChild(std::make_shared<Node>(uranusNode));

//Neptun
    Node neptunNode("Neptun" ,glm::translate({},glm::vec3{500.0f,0.0f,0.0f}), std::make_shared<Node>(root));
    GeometryNode neptunGeo("NeptunG" ,glm::translate({},glm::vec3{500.0f,0.0f,0.0f}),  std::make_shared<Node>(neptunNode));
    neptunNode.addChild(std::make_shared<Node>(neptunGeo));
    root.addChild(std::make_shared<Node>(neptunNode));

    SceneGraph sceneGraph{"SceneGraph",root};
    sceneGraph_ = sceneGraph;
    //sceneGraph_.printGraph();
//std::cout << root.getPath() << std::endl;
//std::cout << root.getDepth() << std::endl;
}


// exe entry point
int main(int argc, char* argv[]) {
  Application::run<ApplicationSolar>(argc, argv, 3, 2);
}