# JSRbot Description
University of Toronto Robotics Association 2024 Hackathon Autonomous Vehicle Challenge. This is an AV made with a limited list of components and facilities, competing against several other teams from all over Canada.

# 1. Software
## 1.1 Challenge 1 and 2: Line Following
### 1.1.1 Challenges
#### Basic Line following
This challenge will demonstrate that the team has properly assembled their robot and that their robot can follow a 1” black line on the ground. The team’s robot must automatically drive through a simple track while staying on the line. There will be 2 sections: a straight line segment and a gentle turn.
#### Advanced Line following
In this challenge, the team’s robot must follow a black line in a complex path on the ground. There will be sharp turns and loops that the robot must traverse.
### 1.1.2 Code explanation
Given 2 sensors, we made sure to not only follow the line but code for sharp turns and curves. 
#### Method 1
The sensors are set to go forward when both sensors get high reflections (both white) which ensures that at all times, the black strip or path will be between the sensors. This will make sure that the AV runs on it, given it starts on the line and the line is continuous. It turns left when it detects black on the left sensor and white on the right, and vice versa. When both sensors detect black, it randomizes Left and Right until it finds the path again. This is done by stopping and going a little forward in these cases and moving by small degrees, not enough to leave the path. 
#### Method 2
The sensors are set to go forward when say, the left wheel, is on the line. So when the left detects black and the right detects white, it goes ahead. This makes sure that the AV stays on track regardless of the direction the rest of the AV goes in. This became complicated as the AV started leaving the path without any chance of tracing back. Possibly could be solved by moving it backward and rotating it - which gives a 50% chance of tracing back its initial route to the starting point.
## 1.2 Challenge 3: 
### Description
#### 1.2.1 Obstacle Detection
The team’s robot must detect and avoid obstacles in this course. Black lines will be placed to help guide the robots however they are still expected to detect and avoid on their own.
### 1.2.2 Code explanation
We integrated the ultrasonic sensor code into our previous code to find distances of obstacles and turn right if they're less than a threshold value and keep repeating that until it finds one path (with some chance of tracing its path back).
## 1.3 Challenge 4:
### 1.3.1 Description
In this challenge, the robot must navigate across a maze autonomously without the help of any black lines. There may be dead ends in the maze and the finish will not be in the middle.
### 1.3.2 Code explanation
This code is a combination of the "Pledge" algorithm and the "Wall Following" algorithm built on the top of existing code. So this code follows Pledge algorithm until it finds a wall and can follow the wall-following algorithm. 
# 2. Hardware
Arduino Uno was used with the L298N Motor Driver Module. The wheels were made using a DC Gearbox Motor - "TT Motor" - 200RPM - 3 to 6VDC and Gear Motor 3 - 224:1 90 Degree Shaft. 2 MH Infrared Line Tracking Sensor Modules were attached in the front to detect reflection/color. A Basic Ultrasonic Sensor helped detect the distances with a 9V battery (that died during testing). All were temporarily duct taped to the chassis for testing.   

### L298N with DC Motor
<img src="https://github.com/kalashb/JSRbot/assets/66458799/32b997a0-1271-45c7-b0e1-aa0ca6f68250" alt="Image of Combinations and outcomes of L298N with DC Motor" title="Figure: Combinations and outcomes of L298N with DC Motor" width="400" height="200">

# 3. Mechanics
Given with a pre laser-cut chassis from the hackathon organizers, we built our AV on the chassis with some scope for design.
