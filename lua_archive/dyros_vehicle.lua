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
                if (auxiliaryData[1]==115) then
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

                if (auxiliaryData[1]==101) then
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
        --     차량의 position, orientation 값을 구하고
        objectPos = simGetObjectPosition(h_dyros_vehicle, -1)
        objectEulerAngle = simGetObjectOrientation(h_dyros_vehicle, -1)


        -- ed: Float32MultiArray 형식에 맞게 넣어준다
        localData = {}
        localData['data'] = {}
        localData['data'][1] = objectPos[1]            -- x
        localData['data'][2] = objectPos[2]            -- y
        localData['data'][3] = objectEulerAngle[2]     -- yaw
        localData['data'][4] = 0                       -- velocity

        -- ed: /LocalizationData 토픽으로 퍼블리시
        simExtRosInterface_publish(pub_localization, localData)


        simAuxiliaryConsolePrint(aux_console, "Motor Speed: ["..desiredWheelRotSpeed.."], Steer Angle: ["..steeringAngleLeft..","..steeringAngleRight.."]\n")


        -- ed: -----------------------------------------------


        -- Since this script is threaded, don't waste time here:
        simSwitchThread() -- Resume the script at next simulation loop start
    end
end


-- ed: INITIAL SETTINGS --------------------------------------
-- Put some initialization code here:
-- Retrieving of some handles and setting of some initial values:
steeringLeft=simGetObjectHandle('nakedCar_steeringLeft')
steeringRight=simGetObjectHandle('nakedCar_steeringRight')
motorLeft=simGetObjectHandle('nakedCar_motorLeft')
motorRight=simGetObjectHandle('nakedCar_motorRight')



-- ed: code added-------------------------------------------

aux_console=simAuxiliaryConsoleOpen("Aux Console", 500, 0)

-- ed: localization 전용 코드 추가
h_dyros_vehicle = simGetObjectHandle('dyros_vehicle')
-- ed: LocalizationData 토픽 퍼블리셔 선언
pub_localization = simExtRosInterface_advertise('/LocalizationData', 'std_msgs/Float32MultiArray')
simExtRosInterface_publisherTreatUInt8ArrayAsString(pub_localization)

-- ed: -----------------------------------------------------




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
