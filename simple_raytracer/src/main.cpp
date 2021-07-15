// ========================================================================= //
// Copyright (c) 2021 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// main.cpp                                                                  //
// ========================================================================= //

#include "Raytracer.h"
#include "Scene.h"

int main(int argc, char* argv[]) {
  const int WIDTH = 500;
  const int HEIGHT = 500;

  Scene scene;

  auto sphere1 = ObjectsFactory::createSphere(Vec3(100, 0, -250), 100);
  sphere1->pvtMaterial().diffuse = Vec3(0.8f, 0.2f, 0.2f);
  scene.addObject(sphere1);

  auto sphere2 = ObjectsFactory::createSphere(Vec3(-100, 0, -100), 100);
  sphere2->pvtMaterial().diffuse = Vec3(0.2f, 0.8f, 0.2f);
  scene.addObject(sphere2);

  auto triangle = ObjectsFactory::createTriangle(
      Vec3(300, -100, 400), Vec3(0, -100, -600), Vec3(-300, -100, 400));
  scene.addObject(triangle);

  scene.addLight(Vec3(-200, 0, 200), Vec3(1, 1, 1), true);

  Raytracer raytracer(WIDTH, HEIGHT);
  raytracer.setEyeLocation(Vec3(0, 0, 1000));
  RaytracerImage image = raytracer.raytrace(scene, 2);

  bool ok = RaytracerImageSaver::save(image, "output.ppm",
                                      RaytracerImageSaver::FORMAT::PPM);
  if (ok) system("output.ppm");

  return 0;
}