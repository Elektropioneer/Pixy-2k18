# Camera-2017
Pixy camera for 2017 robotics tournament.

Things you need:

The camera we are using is the Pixy camera, we can check what it sees through a software called ''PixyMon''
For communication with the camera we are using an arduino microcontrollers.
For programming itself we are using Arduino IDE since it contains libraries to make the whole work easier (check in header file).
I inserted all the libraries you can download if you want to use each type of communication, we are only using SPI.
In another case, you can download whole library here: http://www.cmucam.org/projects/cmucam5/wiki/Latest_release

How to set up:

First, check the if the camera works by connecting it to your computer with an USB cable, then open PixyMon and set up camera focus.
Next, there are two ways on how you can teach the camera to remember certain object (AKA color):
 1. Hold the button on the camera for 2-3 seconds, then release, the object should have some grid on itself, click the button again, camera should remember it's signature (you can set up signature name in the options)
 2. Just go to Actions>Set signature (x), the screen should freeze, just drag your mouse over some of the object area, camera should do rest of the job
 
You can tweak the camera in the options, distance of detection, brightness, signature names and so on and so on...

Code:

The way we are doing it is, since every time we will encounter 3 colors (even when there is black, though we are ignoring black since pixy camera cannot detect colors with low hue), we first find which block is where by comparing the x-axis of each block, then we just put the block signatures (colors) in an array so it's easier for us, after that, we are checking which combination we are looking at and according to that sending signal to the main board so it can do it's job.
