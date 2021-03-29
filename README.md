RT

This project’s goal is to transform the basic raytracer of the project (rtv1) to a raytracer able to generate
amazing images (RT). This is accomplished implementing a multitude of new functions to the raytracer.
This project has been realized by a group of 4 students.

* Here is an XML scene file example: [tridimensional_3.xml](scene_examples/xml/tridimensional_3.xml)
* Here is an OBJ scene file example: [low_tree.obj](scene_examples/obj/low_tree.obj)
* Here is an OBJ converted scene file example: [hard_house_converted.xml](scene_examples/obj/hard_house_converted.xml)


__NOTE:__
The whole project was realized using the school's graphic library: MinilibX.
This library contains only basic drawing functions: open a window, lit a pixel and manage events.
Everything else has to be coded by students ex: 
XML and OBJ files parser from scratch, Camera quaternion model, Object intersections,
Vector and Matrix calculations creating our own respectively libraries, Shading models: lambert, phong, Snell-Descartes laws...
Texture mapping, Screenshots from a char string containing rgb values to ppm format, Light color mixing, Polygons to Triangles convertions, ...

__Realized options:__
- Advanced XML format scenes
- Adjustable ambient light
- Adjustable resolution / FOV 
- Directions, rotations and translations for every object
- Dazzling light (ex. car headlights)
- Parallel light (directional lighting)
- Rectangle light (soft shadows)
- Reflexion (Possibility to decide the percentage)
- Transparence (Possibility to decide the percentage and refraction index)
- Shadows that change according to an object's transparency
- Other objects: paraboloids, hyperboloids, ellipsoid, cube
- Disk object: cutting a plane along the radius
- Third degree surface: Mobius strip (Cartesian equation)
- Fourth degree surface: Torus (Cartesian equation)
- Objects group (definition of one object composed of several objects)
- Negative objects
- Loading bar
- Camera rotations (x, y, z) / dazzling light activation / fov changements without relaunch of the program
- Perturbation: Normal (alternations with sinus algorithm)
- Perturbation: Color (checkerboard, perlin noise)
- Texture can be applied on: sphere, cone, cylinder and plane
- Texture can be stretched and moved
- Texture: normal alterations, bump mapping
- Effect: Antiliasing
- Effect: Celshading
- Effect: Motion blur
- Effect: Anaglyph 3D
- Effect: Color filters (sepia, inverted, grayscale)
- Computation: Multithread and/or Multicluster
- Screenshots (PPM format)
- OBJ file reader (and converter to XML format)

![alt text](screens/screen1.png)
![alt text](screens/screen2.png)
![alt text](screens/screen3.png)
![alt text](screens/screen4.png)
![alt text](screens/screen5.png)
![alt text](screens/screen6.png)
![alt text](screens/screen7.png)
![alt text](screens/screen8.png)
![alt text](screens/screen9.png)
![alt text](screens/screen10.png)
![alt text](screens/screen11.png)
![alt text](screens/screen12.png)
![alt text](screens/screen13.png)
![alt text](screens/screen14.png)
![alt text](screens/screen15.png)
![alt text](screens/screen16.png)
![alt text](screens/screen17.png)

_If you are interested in the complete code, please do not hesitate to contact me._
