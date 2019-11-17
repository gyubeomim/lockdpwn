
executable="/home/dyros-vehicle/catkin_ws/devel/lib/adv_animation/assign4"

# comment(edward): program should run once before debugging. 
# And we need to use same node name for debugging.
node_name="__name:="  # __name:=node-name


gdb --ex="set print thread-events off" --args $executable $node_name
