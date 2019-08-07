CS 475 Assignment-3 
  
Animation  

Video link - https://youtu.be/AQkbWkEoZoE 

Shreyas Pimpalgaonkar - 160050024 
Saiteja Nangunoori - 160050089 
 
 
The assignment is our own work and we have not copied it from anywhere 
 
 
Interface for saving frame - press the key '5' to append the current parameters into the file. Only the parameters that have been changed are added to the file. 
 
Press key '6' to get the parameters from the file (keyframes) and interpolate them 
 
Press the key '7' to render the camera moving animation on the bezier spline 
 
Press the key '8' to render the animation of  
 
Press the key '9' to go into drawing mode - in the drawing mode press the mouse button to add a point at the location of the camera. 

Uncomment the line in the   while (glfwWindowShouldClose(window) == 0) loop in model.cpp to capture and save the rendered frames.
~                                                                                                                                                                                                           

Some bug in the video capture that's why it is capturing 1/4th of the part. Another bug in the interpolation which is causing the model to oscillate.

