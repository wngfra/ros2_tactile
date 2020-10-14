# Tactile-based Hybrid Control for TacSense Project

## <img src="https://i.udemycdn.com/course/480x270/1797828_c391_3.jpg" width="48" height="27" /> 

1. [libfranka](https://frankaemika.github.io/docs/libfranka.html) is needed
2. `franka_control` contains Franka Emika Panda control interface
3. `can2wifi2ros` contains codes for a DIY `CAN2WIFI` module, see `README` there
4. Using a [CPM-Finger](https://www.cyskin.com/cpm-finger-the-finger-for-textile-manipulation/) tactile sensor
5. Non-realtime config will be applied to `robot` automatically when `PREEMPT_RT` not detected
6. Default `UDP` socket ip is binded to `0.0.0.0` for use in containers
7. `/tactile_publisher/change_state` service is created with the node to enable calibration state; set state of the node to `0` for calibration and `1` to publish calibrated signals; number of samples used for calibration can be set in `tactile_signal_publisher.py`

## Docker/Podman
1. `Dockerfile` is provided for development/deployment in containers
2. Alternatively, pull images `wngfra/ros2franka` from [dockerhub](https://hub.docker.com/)
3. `run_container.sh <container-name>` helps to run a development container with X11 forwarding, host-net support, username `ubuntu` at the default workdir `/home/ubuntu/ros2_ws`