# ecse373_f23_sxw1127_ik_service
## Build
1. Download this repository to `<workspace>/src`
1. `cd <workspace>`
2. `catkin_make`
## Setup the environment
`source <workspace>/devel/setup.bash`
## Start Service
There are 2 different methods to start the service, the method 1 needs to firslty run roscore, and method 2 can direclty start the service with a single command.
### Method 1:
1. `roscore &`
2. `rosrun ik_service ik_service_node`
### Method 2:
`roslaunch ik_service ik_service.launch`
## Start Client Once
`rosrun ik_service ik_client_node`
