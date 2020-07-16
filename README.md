# FPT Digital Race 2020

The platform that I used for this personal project is from [FPT Digital Race 2020 contest](https://github.com/fpt-corp/DiRa). 

## Description
### Environment 
* The contest used Unity as a simulator.  
* [ROS](https://www.ros.org/) was used to communicate with the simulator (transfering frames, sending car speeds/steering angles between ROS nodes).  
![sim](https://github.com/khanhvu207/FPT-DigitalRace2020/blob/master/img/sim.JPG)

### Lane detection (tools: C++ and OpenCV3)
[Code](https://github.com/khanhvu207/FPT-DigitalRace2020/blob/master/FPT-DigitalRace2020/src/lane_detect/src/detectlane.cpp)  
1. Receive raw images from ROS server.
2. Convert color space from RGB to HSV.
3. Perform [image thresholding](https://docs.opencv.org/master/d7/d4d/tutorial_py_thresholding.html) to extract the roadsides.  
![img_thresholding](https://github.com/khanhvu207/FPT-DigitalRace2020/blob/master/img/img_thresholding.JPG)  
4. I used [Hough Line Transform](https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_imgproc/py_houghlines/py_houghlines.html) to get two straight lines which almost the regression lines of the two roadsides. The reason why I did not do the normal lines regression is Hough lines definitely go through points, where regression lines sometimes do not.
![hough](https://github.com/khanhvu207/FPT-DigitalRace2020/blob/master/img/hough.JPG).
5. Create birdview scene for future usages.  
![birdview](https://github.com/khanhvu207/FPT-DigitalRace2020/blob/master/img/birdview.JPG).
6. To suppress the shadows created by trees, I again used color thresholing and did the bitwise-OR to combine two binary images.   

### Sign detection
[Code](https://github.com/khanhvu207/FPT-DigitalRace2020/blob/master/FPT-DigitalRace2020/src/lane_detect/src/carcontrol.cpp)  
1. Perform image thresholding to extract the **blue** color.
2. I used the [findContour](https://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/find_contours/find_contours.html) to detect round shapes in the binary image. Here, we could possibly use the [Hough Circle Transform](https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html) to detect the sign. The Hough circle transform didn't work well for me, since from the car's perspective, signs always look like an oval shape and I had an hard time tuning those params :(. After the sign's position have been determined, just put a minimum bounding box that encloses our sign.  
![sign](https://github.com/khanhvu207/FPT-DigitalRace2020/blob/master/img/sign.JPG)
3. To know whether the sign is the left sign or right sign, I splitted the box and count white pixels in each half (not so efficient, but simple!).

### Car controlling (tools: PID controller)
1. Set an offset point that represent your car's position (the red point).
2. Set an green point which has the same Y-coordinate as the red point, and lays in the bisector of the two green Hough lines.
3. Compute the relative distance between the red point and the green point.
4. Use the above distance as a error parameter of PID controller.

## Demo GIF
![demo](https://github.com/khanhvu207/FPT-DigitalRace2020/blob/master/img/demo.gif)
