#include "solar_system.hpp"

solarSystem:solarSystem(){
  
~solarSystem:solarSystem(){}
  
void solarSystem::init(){
  //create sunNode
  //set sun position
  //set sun size
  //add it to sceneGraph
  sceneGraph_.setRoot()->addChild(sunNode);
  
  //create Mercury
  //set Mercury start position
  //set Mercury size
  //set Mercury rotation velocity
  sunNode->addChildren(MercuryNode);
  mercuryNode->setParent(sunNode);
  //Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune are the same as Mercury
}

void solarSystem::update(){
  // Get planetNodes from sceneGraph
  std::vector<std::shared_ptr<Node>> planets = scene_graph_->getRoot()->getChildren();

  // update each planetNode
  //for (int i = 0; i < planets.size(); i++) {
    // calculate rotation angle
   

    // calculate the new position 
    //float x = ;
    //float y = 0.0f;
    //float z = ;
}

void solarSystem::render(){
  //render sun
  
}
