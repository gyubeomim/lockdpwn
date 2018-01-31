--[[
    lua ==> dyros, velodyne sensor를 V-Rep --> ROS로 퍼블리시하려면 특정 플러그인을 설치해야한다

                   libv_repExtRosVelodyne.so 플러그인을 vrep_plugin_velodyne 패키지에서 catkin_make한 다음 vrep 폴더에 넣고
                   아래 코드를 실행하면 V-Rep에서 /velodyne_points로 토픽을 전송한다

                   https://github.com/omcandido/vrep_plugin_velodyne
]]--

if (sim_call_type==sim_childscriptcall_initialization) then
    visionSensorHandles={}

    for i=1,4,1 do
        visionSensorHandles[i]=simGetObjectHandle('velodyneHDL_64E_S2_sensor'..i)
    end

    rotJointHandle=simGetObjectHandle('velodyneHDL_64E_S2_rotJoint')
    ptCloudHandle=simGetObjectHandle('velodyneHDL_64E_S2_ptCloud')

    frequency=5 -- 5 Hz
    options=1+2+8 -- bit0 (1)=do not display points, bit1 (2)=display only current points, bit2 (4)=returned data is polar (otherwise Cartesian), bit3 (8)=displayed points are emissive
    pointSize=2
    coloring_closeAndFarDistance={1,4}
    displayScaling=0.999 -- so that points do not appear to disappear in objects

    _h=simExtVelodyneROS_createVelodyneROSModel(visionSensorHandles,frequency,options,pointSize,coloring_closeAndFarDistance,displayScaling)
end

if (sim_call_type==sim_childscriptcall_actuation) then

    p=simGetJointPosition(rotJointHandle)
    p=p+simGetSimulationTimeStep()*frequency*math.pi*2
    simSetJointPosition(rotJointHandle,p)

end


if (sim_call_type==sim_childscriptcall_sensing) then

    --Boolean, true if data is published (via VelodyneROS plugin)
    -- ed: /velodyne_points 토픽으로 퍼블리시한다 (odom (tf)를 사용한다)
    local fullRev=simExtVelodyneROS_handleVelodyneROSModel(_h,simGetSimulationTimeStep())

end


if (sim_call_type==sim_childscriptcall_cleanup) then

    simExtVelodyneROS_destroyVelodyneROSModel(_h)

end
