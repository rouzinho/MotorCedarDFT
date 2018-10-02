# A ROS Subscriber in Cedar
This is a DFT plugin to integrate ROS inside Cedar.

Everything you want to know about DFT -> https://dynamicfieldtheory.org/

Cedar is the C++ Framework implementing the concepts of DFT -> https://cedar.ini.rub.de/

Everything you need to know about ROS -> http://www.ros.org/

## Getting Started

The plugin is a basic ROS subscriber reading data from a topic with the type Float64.

Of course you can adapat it to subscribe to any topic.

It basically consists of a C++ code starting a ROS init() thread, then the plugin itself is listening to the topic. 

The code work for the 6.x version of Cedar.


### Prerequisites

You first need to install cedar by following the instructions here : https://bitbucket.org/cedar/development

You can't use a precompiled version of Cedar to compile and run the plugin.

I suggest reading about how to create a plugin in Cedar first, it will greatly help to understand how it works : https://cedar.ini.rub.de/tutorials/writing_custom_code_for_cedar/

Install ROS : http://wiki.ros.org/ROS/Installation

The code was tested on ROS Kinetic Kame

**Warning**

ROS comes with Qt5 and Cedar officially support only Qt4, so I suggest a basic installation of ROS.
For my case, I have Cedar and a basic ROS on a computer and a complete ROS desktop on another computer dedicated to my robot. I communicate between them through the network with the topics.

Anyway, ROS and Cedar are a bit to powerful to run on the same computer (if you have a big DFT model and a complex robot), so I recommend using 2 different computer.

### Installing

First clone the repository :

`git clone https://github.com/rouzinho/ROS-Subscriber-Cedar.git`

In the project.conf, change the CEDAR_HOME directory to your own :

`set(CEDAR_HOME "your_own_cedar_repository")`

Then create a build repository and prepare the environment for the compilation :

`mkdir build`

`cd build`

`cmake ..`

Finally start the compilation :

`make`

You should see the plugin under the name libEarListener.so in the build/ repository

## Run the plugin

Execute cedar and load it into cedar 

*Tools -> Manage plugins*

In the plugin Manager window, click on *add* and choose the plugin libEarListener.so. This one should appear in the window.

You can close the window. The plugin is loaded inside cedar and before loading it, make sure your ROS node is running.

Run the ROS init() thread 

*Scripting -> C++ Scripts...*

In the window, you should see the name of the thread inside the plugin (InitRos here). Click on the add button.
Then click on play to start the Ros initialisation. This will create a thread that will init ROS in order to subscribe to any topics you want.


You can now go back to the cedar main interface and click on the Utilities tab.

Drag the EarSubscriber widget into the architecture panel. When your architecture is ready, you can start the simulation.
You will see that the EarSubscriber transform the input of a topic into a 1D Gaussian function.
For this case, I read data from a noise sensor and use the value as amplitude of the gaussian function.


## Work in progress

This plugin is right now more a proof of concept than a stable module. As you have seen, you have to specify everything inside the code (topic subscription, type read...)

In the future, the plugin will use the Qt widget interface to select the nodes, topics and types in order to avoid changing the code everytime you want to subscribe to a topic.

The plugin will be more like an artefact binding sensors to DFT.



## Authors

Quentin Houbre - Tampere University of Technology

## License

This project is licensed under the BSD licence

# MotorHeadDft
