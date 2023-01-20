
![transportino](https://github.com/mattsays/transportino/blob/main/images/mechanics_showcase_1.png?raw=true)

# transportino

## Overview

![transportino](https://github.com/mattsays/transportino/blob/main/images/mechanics_showcase_0.gif?raw=true)

## About the project

Transportino is an automated robot that can bring you things around the house using just your vocal assistant.

Making and also understanding this project will hopefully help enthusiasts that want to know more about robotics and automated navigation, learn the basics of it.

However, this project was born because of my curiosity to learn robotics so It is far from industrial perfection. If you have new ideas or you want to change something just make a pull request!

## Why this name?

Its name is literally made of two words: Transport and Arduino. 

## What's the main idea behind it?

This robot was originally meant to be a new version of an older one called [ArduCar](https://github.com/mattsays/arducar).

However it ended up being an entirely new robot that required me to make things entirely different and it was also an opportunity for me to learn more stuff about robotics, electronics, programming and also a little bit of mechanics.

This is just a project that I made to explore a field that was quite unknown to me and that made really passionate about.

So the main idea behind the whole project is making a robot which can move objects from one room of your house to another one.
The robot should know how to navigate in your house and at least bring objects at the entrance of the room.

## Known Limitations

Transportino has a raspberry pi 3 at its core, so by actually making It, I have encountered several performance issues that made me voluntarily limit the wanted capabilities of the robot.
For example, I had to separate the route planning algorithm from the actual robot and make it run on my local computer so I could lower the load on the raspberry.
It also would have been great if I implemented a more efficient cooling system.
Besides these major issues, I can proudly say that making this robot has made me learn a lot about what challenges are encountered when making a robot and I love it.

## What is it made of?

Transportino is composed by three important parts:
- [Mechanics](https://github.com/mattsays/transportino/tree/main/mechanics), the main structure, the usage of the right motors for a specific torque, etc.
- [Electronics](https://github.com/mattsays/transportino/tree/main/electronics), the main motherboard, data connections with raspberry pi and power management.
- [Software](https://github.com/mattsays/transportino/tree/main/code), the ros2 application that controls all the motors and analyzes data appropriately.

## To Do list

- [X] Make the main motherboard
- [X] Code the embedded part
- [X] Add ROS2 integration
- [X] Make a decent design that so Transportino looks sexy.
- [ ] Add integration with Amazon Alexa.
- [ ] Add a speaker so Transportino can also talk.
- [X] Add some cool aesthetics.

## Some cool renderings and animations 

![transportino](https://github.com/mattsays/transportino/blob/main/images/mechanics_showcase_1.png?raw=true)
![transportino](https://github.com/mattsays/transportino/blob/main/images/mechanics_showcase_2.png?raw=true)
![transportino](https://github.com/mattsays/transportino/blob/main/images/mechanics_showcase_3.gif?raw=true)


## What is that 46 logo?

![fortisix](https://github.com/mattsays/transportino/blob/main/images/46.png?raw=true)

This logo it literally has no sense, it is from a startup idea named "Fortisix" that I had some time ago which had this beautiful and simple logo.
