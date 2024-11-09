Lab #1 Sergienko Andrey b82 group
Mail: Personal - andryman1024@gmail.com University - st135882@student.spbu.ru

Print make. Then ./main Filename.bmp to run it.

This project will apply a Gaussian filter to a provided photo. It is also 90 degrees clockwise and counterclockwise.

To run a check on the amount of RAM consumed. Enter "make run_mem" or /usr/bin/time -v ./main. "The Maximum resident set size (kbytes): " line will indicate the amount of RAM consumed. 
The repository also contains an example photo Makaka.bmp. You can use a photo example to check the program or any other at your discretion.

At the end print make clean

### Program stages and memory consumption

##### Initial image loading (readBMP):
The original image is loaded. It takes up 100% of the memory relative to the image size.
##### Rotate 90 degrees clockwise (rotate90Clockwise):
Temporary memory consumption: 100% for the original image + 100% for the rotated copy.
After the rotation is complete, the original image is released, leaving only the new rotated copy.
Total memory consumption at this stage: temporarily up to 200%, then drops to 100%.
##### Rotate 90 degrees counterclockwise (rotate90CounterClockwise):
Before rotation starts, the original is loaded again, again taking up 100% of the memory.
Rotation temporarily consumes 200% of the memory (original + rotated image).
After saving and clearing the copy, only the original remains.
Total memory consumption at this stage: temporarily up to 200%, then again 100%.
##### Apply Gaussian Filter (applyGaussianFilter):
The original image is loaded, taking up 100% of the memory.
The Gaussian filter is applied in place, replacing the pixels of the original image, which does not require an additional copy.
Once the filter is complete, the memory is freed.
The total memory consumption at this stage: 100% remains.
