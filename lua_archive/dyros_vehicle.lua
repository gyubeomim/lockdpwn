--[[
    lua ==> dyros simulator, V-Rep Vehicle Model

]]--

-- This script is threaded! It is a very simple example of how Ackermann steering can be handled.
-- Normally, one would use a non-threaded script for that

threadFunction=function()
    while simGetSimulationState() ~= sim_simulation_advancing_abouttostop do
        -- Read the keyboard messages (make sure the focus is on the main window, scene view):
        message, auxiliaryData = simGetSimulatorMessage()

        while message~=-1 do
            if (message == sim_message_keypress) then

                if (auxiliaryData[1]==119) then
                    -- up key : W
                    desiredWheelRotSpeed = desiredWheelRotSpeed + wheelRotSpeedDx
                end
                if (auxiliaryData[1]==120) then
                    -- down key : S
                    desiredWheelRotSpeed = desiredWheelRotSpeed - wheelRotSpeedDx
                end
                if (auxiliaryData[1]==97) then
                    -- left key : A
                    desiredSteeringAngle = desiredSteeringAngle + steeringAngleDx

                    if (desiredSteeringAngle > 30*math.pi/180) then
                        desiredSteeringAngle = 30*math.pi/180
                    end
                end
                if (auxiliaryData[1]==100) then
                    -- right key : D
                    desiredSteeringAngle = desiredSteeringAngle - steeringAngleDx

                    if (desiredSteeringAngle < -30*math.pi/180) then
                        desiredSteeringAngle = -30*math.pi/180
                    end
                end

                if (auxiliaryData[1]==115) then
                    -- stop key : E
                    desiredWheelRotSpeed = 0
                end

            end
            message,auxiliaryData=simGetSimulatorMessage()
        end

        -- We handle the front left and right wheel steerings (Ackermann steering):
        steeringAngleLeft=math.atan(l/(-d+l/math.tan(desiredSteeringAngle)))
        steeringAngleRight=math.atan(l/(d+l/math.tan(desiredSteeringAngle)))

        simSetJointTargetPosition(steeringLeft,steeringAngleLeft)
        simSetJointTargetPosition(steeringRight,steeringAngleRight)

        -- We take care of setting the desired wheel rotation speed:
        simSetJointTargetVelocity(motorLeft,desiredWheelRotSpeed)
        simSetJointTargetVelocity(motorRight,desiredWheelRotSpeed)


        -- ed: code added ------------------------------------
        --     차량의 position, orientation, velocity 값을 구하고
        objectPos = simGetObjectPosition(h_dyros_vehicle, -1)
        objectEulerAngle = simGetObjectOrientation(h_dyros_vehicle, -1)
        linearVelocity, angularVelocity = simGetObjectVelocity(h_dyros_vehicle)

        -- ed: 차량의 속도를 구한다 sqrt(x^2 + y^2 + z^2)
        vehicle_vel = math.sqrt(math.pow(linearVelocity[1], 2) + math.pow(linearVelocity[2], 2) + math.pow(linearVelocity[3], 2))

        -- ed: Float32MultiArray 형식에 맞게 넣어준다
        localData = {}
        localData['data'] = {}
        localData['data'][1] = objectPos[1]            -- x
        localData['data'][2] = objectPos[2]            -- y
        localData['data'][3] = objectEulerAngle[2]     -- yaw
        localData['data'][4] = vehicle_vel             -- velocity

        -- ed: /LocalizationData 토픽으로 퍼블리시
        simExtRosInterface_publish(pub_localization, localData)


        simAuxiliaryConsolePrint(aux_console, "Motor Speed: ["..string.format("%.2f",desiredWheelRotSpeed).."], Steer Angle: ["..string.format("%.2f",steeringAngleLeft)..","..string.format("%.2f",steeringAngleRight).."]\n")

        -- simAuxiliaryConsolePrint(aux_console, "["..string.format("%.2f",linearVelocity[1])..", "..string.format("%.2f",linearVelocity[2])..", "..string.format("%.2f",linearVelocity[3])..", "..string.format("%.2f",vehicle_vel).."]\n")


        -- To send several transforms at once, use simExtRosInterface_sendTransforms insteads
        transformations = {}
        transformations[1]=(getTransformStamped(h_dyros_vehicle,'base_link',-1,'map'))
        transformations[2]=(getTransformStamped(h_wheelFR,'wheel_link_fr',h_dyros_vehicle,'base_link'))
        transformations[3]=(getTransformStamped(h_wheelFL,'wheel_link_fl',h_dyros_vehicle,'base_link'))
        transformations[4]=(getTransformStamped(h_wheelRR,'wheel_link_rr',h_dyros_vehicle,'base_link'))
        transformations[5]=(getTransformStamped(h_wheelRL,'wheel_link_rl',h_dyros_vehicle,'base_link'))
        transformations[6]=(getTransformStamped(h_imu,'imu_link',h_dyros_vehicle,'base_link'))
        transformations[7]=(getTransformStamped(h_velodyne,'velodyne_link',h_dyros_vehicle,'base_link'))


        -- ed: V-Rep 차량의 tf를 broadcast한다
        simExtRosInterface_sendTransforms(transformations)

        -- ed: simGetSimulationTime  ==>  simGetSystemTime
        --     /clock 토픽으로 퍼블리시
        simExtRosInterface_publish(pub_clock,{clock=simExtRosInterface_getTime(0)})


        -- Since this script is threaded, don't waste time here:
        simSwitchThread() -- Resume the script at next simulation loop start
    end
end


-- ed: INITIAL SETTINGS --------------------------------------

-- ed: tf를 설정하는 함수 추가
-- function for tf publications
function getTransformStamped(objHandle, name, relTo, relToName)
    t=simExtRosInterface_getTime(0)
    p=simGetObjectPosition(objHandle,relTo)
    o=simGetObjectQuaternion(objHandle,relTo)

    -- simAuxiliaryConsolePrint(aux_console, vrep_clock.."\n")

    return {
        header={
            stamp=t,
            frame_id=relToName
        },
        child_frame_id=name,
        transform={
            -- ROS has definition x=front y=side z=up
            translation={x=p[1],y=p[2],z=p[3]},--V-rep
            rotation={x=o[1],y=o[2],z=o[3],w=o[4]}--v-rep
        }
    }
end



-- Put some initialization code here:
-- Retrieving of some handles and setting of some initial values:
steeringLeft=simGetObjectHandle('nakedCar_steeringLeft')
steeringRight=simGetObjectHandle('nakedCar_steeringRight')
motorLeft=simGetObjectHandle('nakedCar_motorLeft')
motorRight=simGetObjectHandle('nakedCar_motorRight')



-- ed: code added-------------------------------------------

aux_console=simAuxiliaryConsoleOpen("Aux Console", 500, 0)

-- ed: handle 추가
h_dyros_vehicle = simGetObjectHandle('dyros_vehicle')
h_wheelFR=simGetObjectHandle('nakedCar_frontRightWheel_respondable')
h_wheelFL=simGetObjectHandle('nakedCar_frontLeftWheel_respondable')
h_wheelRR=simGetObjectHandle('nakedCar_rearRightWheel_respondable')
h_wheelRL=simGetObjectHandle('nakedCar_rearLeftWheel_respondable')
h_imu=simGetObjectHandle('Imu')
h_velodyne=simGetObjectHandle('velodyneHDL_64E_S2')


-- ed: LocalizationData 토픽 퍼블리셔 선언
pub_localization = simExtRosInterface_advertise('/LocalizationData', 'std_msgs/Float32MultiArray')
simExtRosInterface_publisherTreatUInt8ArrayAsString(pub_localization)

-- ed: /clock 토픽 퍼블리셔 선언
pub_clock=simExtRosInterface_advertise('/clock','rosgraph_msgs/Clock')
simExtRosInterface_publisherTreatUInt8ArrayAsString(pub_clock)

desiredSteeringAngle=0
desiredWheelRotSpeed=0

-- ed: 한 번의 키보드로 움직이는 속도/각도의 양
steeringAngleDx=2*math.pi/180
wheelRotSpeedDx=20*math.pi/180

-- ed: 휠간 거리
d=0.755  -- 2*d=distance between left and right wheels

-- ed: 휠베이스
l=2.5772 -- l=distance between front and read wheels


-- Here we execute the regular thread code:
res,err=xpcall(threadFunction, function(err) return debug.traceback(err) end)


if not res then
    simAddStatusbarMessage('Lua runtime error: '..err)
end


-- Put some clean-up code here:
-- ed: /LocalizationData 퍼블리셔 소멸자
simExtRosInterface_shutdownPublisher(pub_localization)
