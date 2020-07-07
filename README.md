# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---
# Rubric points

## Compilation

Code compiles without errors with cmake and make.
There are warning though since i have not used the steering value and speed in the code.


## PID controller Design and Implementation

The PID was designed using the PID concept and the Twiddle algorithm taught in the class.

#### Proportional control
The proportional part of the controller was responsible for mainly reducing the cross track error. I started by trying to manually tune the controller since the Twiddle had a really high overshoot at the start with a default value of 0. The proportional part was tuned manually to a value of 0.4. With only proportional values, the vehicle had oscillations and this oscillations increased with time and eventually went out of the track. This was expected though with no differential part to control the oscillations.

### Differential control
Then to control the oscillation of errors, i then used the differential part and started tuning. I ended with manually tuning it to a value of 8 and saw that the oscillations reduced drasctically and i was able to keep the vehicle in lane.

### Integral part
Having introduced the proportional and differential part, i proceeded to include an integral part. i started of with a value of 1 and observed that the vehicle started to go in circles. This was also expected since with a high weight to the integral control , i was eventually getting high values of steering.The i kept on reducing the values of the integral part until i was able to see a stable value.At last i arrived at a value of 0.001.

## Final tuning using twiddle
With the twiddle code, i used 600 iterations and calculated the error for second half.I then utilised the concept of resetting the simulator to run the twiddle logic in cycles.Using this average error from the 300 iterations, i started the cycle of iteratively increasing and decreasing the 3 parameters to fine tune them. After having run the twiddle for more than 30 cycles, i saw that the twiddle was not reducing much from the manually tuned parameters. At last i ended up with Kp = 0.5, Ki = 0.0009 and Kd = 7.5.

The twiddle logic is in the lines 67-189 of PID.cpp

From having run the twiddle, at least for this project, manual tuning seems to be working better than twiddle. I just tried using SGD and it wasnt giving a better result either.

## Simulation

A final video after tuning the parameters is attached here.

[video1]: ./PID_Controller_Video.mp4 "Video"

The vehicle successfully drove around the track without going out. At the end of the bridge with a high speed of 30Mph, it oscillates but then recovers to stay in the track.


## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

