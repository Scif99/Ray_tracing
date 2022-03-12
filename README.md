# Ray_tracing

Ray Tracing in a nutshell:
```
initialise: scene, camera

for each pixel in image:
  compute viewing ray(s) from camera
  if intersection occurs with ray parameter t > 0:
    compute normal n
    evaluate shading model
    set color
   else set color to background
 end for
```
- Note that if the scene has many objects, we take the intersection with the smallest t.
- The intersection loop needs to store enough all relevant information needed to shade...

**Improving Quality**
- If each ray hits the centre of each pixel once, then we end up with jagged edges. If you had some small objects in the scene, they might even be missed. This is called **Antialiasing**. To get a more accurate color, we can take multiple samples per pixel (not necessarily hitting the centre), then take an average. 

**Chapter 7+: Shading**

**Output**
The program outputs the image into a ppm file, in the same folder as the .sln file.


**OOP**
- The scene might contain different geometries (i.e different shapes). What happens upon intersection will vary depending on the geometry.Because of this, it makes sense to use a class heirarchy to represent the shapes. 
- There is an abstract class 'hittable' from which all shapes derived from.



