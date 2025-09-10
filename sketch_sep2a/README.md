# Robot
Programmable robot with the purpose to navigate a track and avoid any obstacles. Has two sensors to help it navigate, one linesensor used to see if the robot is over white or black surface.
One ultasonic sensor used to see if there is something blocking the robots way.

## Code
In order for the code to work three libraries needs to be installed ("freertos.zip", "makeblockdrive.zip" & "kaulab.zip") and imported using "Sketch" -> "Include library" -> "Add .zip library"

## Linesensor
zRobotGetLineSensor() return an int from 0-3. Returnvalue 0 == both linesensors sees black, 1 == left sensor sees black, 2 == right sensor sees black, 3 == no sensor sees black
black meaning no reflection so could be no surface or a darker color.

## Ultrasonic sensor
zRobotGetUltraSensor() returns an int with the distance from the sensor to the object infront (cm). With a range from 0 - 400, 400 meaning nothing infront or object 400cm infront.