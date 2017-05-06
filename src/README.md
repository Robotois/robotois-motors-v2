# Test the C++ Library

In the file `test.cpp` it is provided a simple test for the Servo Module. In the test the servomotor position is updated every `500ms`, where the position is rotated from `(-90) - 90` degrees. The function used for this test is `setAngle()`, and as it can be seen it is straightforward to command the desired angle for the servo.

To run the test follow these steps:

* Compile the sources with the following command: `make all`

* The previous command will generate an executable file named `runner`, which you can run as follows: `sudo ./runner`.

* To remove the compiled `*.o` files and the dist file `runner`, execute the following line: `make clean`.
