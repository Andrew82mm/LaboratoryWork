**Lab #1**  
**Sergienko Andrey**  
**Group**: b82  
**Email**:  
- Personal: andryman1024@gmail.com  
- University: st135882@student.spbu.ru  

---

### Program Overview:
This project applies a Gaussian filter to the provided BMP image, and rotate the image 90 degrees clockwise and counterclockwise.

---

### How to Use the Program:
1. **Compile and Run**:  
   Print `make`. After compiling the program with `make`, You will need to run it with ./main. Than enter the `filename.bmp` image.
   
2. **Clean Up**:  
   Run `make clean` to remove any temporary files created during execution and to delete any modified images.

---

### Explanation of How the Program Works:
1. **Load BMP Image**:
    - The BMP file is loaded into memory with the `file_data` buffer. This uses **100%** of the image's memory.

2. **Apply Gaussian Filter**:
    - A temporary buffer (`file_data`) is created to store the filtered result. This temporarily increases memory usage to **200%** (original image + filtered image).
    - After filtering, the data is copied back into the original buffer, and the temporary buffer is deleted. Memory usage returns to **100%**.

3. **Rotate Image 90 Degrees Counterclockwise**:
    - A new buffer (`file_data`) is created for the rotated image. This temporarily increases memory usage to **200%** (original image + rotated image).
    - After saving the rotated image, the temporary buffer is deleted, returning memory usage to **100%**.

4. **Rotate Image 90 Degrees Clockwise**:
    - Similar to the counterclockwise rotation, a new buffer is created for the clockwise rotated image, bringing memory usage temporarily to **200%**.
    - After saving the rotated image, the buffer is deleted, and memory usage returns to **100%**.

---

### Final Memory Usage:
- The program will **never** exceed **200%** memory usage. This occurs during operations where both the original image and either the filtered or rotated image are stored in memory.
- After each operation (filtering or rotating), temporary buffers are deleted, ensuring that memory usage returns to **100%**.

**In conclusion**, memory usage **never exceeds 200%** at any point during execution.

---

