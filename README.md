# Ray_tracing

Ray Tracing in a nutshell:
```
for each pixel in image:
  compute viewing ray from camera
  if intersection occurs with ray parameter t > 0:
    compute normal n
    evaluate shading model
    set color
   else set color to background
 end for
```
- Note that if the scene has many objects, we take the intersection with the smallest t.

**Chapter 7+: Shading**

**Output**
The program outputs the image into a ppm file, in the same folder as the .sln file.


