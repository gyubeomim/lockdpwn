visualizePath=function(path)
   if not _lineContainer then
      _lineContainer=simAddDrawingObject(sim_drawing_lines,3,0,-1,99999,{1,1,0})
   end
   simAddDrawingObjectItem(_lineContainer,nil)
   if path then
      forbidThreadSwitches(true)
      local initConfig=getConfig()
      local l=#jh
      local pc=#path/l
      for i=1,pc-1,1 do
         local config1={path[(i-1)*l+1],path[(i-1)*l+2],path[(i-1)*l+3],path[(i-1)*l+4],path[(i-1)*l+5],path[(i-1)*l+6]}
         local config2={path[i*l+1],path[i*l+2],path[i*l+3],path[i*l+4],path[i*l+5],path[i*l+6]}
         setConfig(config1)
         local lineDat=simGetObjectPosition(ikTip,-1)
         setConfig(config2)
         local p=simGetObjectPosition(ikTip,-1)
         lineDat[4]=p[1]
         lineDat[5]=p[2]
         lineDat[6]=p[3]
         simAddDrawingObjectItem(_lineContainer,lineDat)
      end
      setConfig(initConfig)
      forbidThreadSwitches(false)
   end
   simSwitchThread()
end

displayInfo=function(txt)
   if dlgHandle then
      simEndDialog(dlgHandle)
   end
   dlgHandle=nil
   if txt and #txt>0 then
      dlgHandle=simDisplayDialog('Jaco info',txt,sim_dlgstyle_message,false)
      simSwitchThread()
   end
end

_getJointPosDifference=function(startValue,goalValue,isRevolute)
   local dx=goalValue-startValue
   if (isRevolute) then
      if (dx>=0) then
         dx=math.mod(dx+math.pi,2*math.pi)-math.pi
      else
         dx=math.mod(dx-math.pi,2*math.pi)+math.pi
      end
   end
   return(dx)
end

_applyJoints=function(jointHandles,joints)
   for i=1,#jointHandles,1 do
      simSetJointTargetPosition(jointHandles[i],joints[i])
   end
end

generatePathLengths=function(path)
   -- Returns a table that contains a distance along the path for each path point
   local d=0
   local l=#jh
   local pc=#path/l
   local retLengths={0}
   for i=1,pc-1,1 do
      local config1={path[(i-1)*l+1],path[(i-1)*l+2],path[(i-1)*l+3],path[(i-1)*l+4],path[(i-1)*l+5],path[(i-1)*l+6],path[(i-1)*l+7]}
      local config2={path[i*l+1],path[i*l+2],path[i*l+3],path[i*l+4],path[i*l+5],path[i*l+6],path[i*l+7]}
      d=d+getConfigConfigDistance(config1,config2)
      retLengths[i+1]=d
   end
   return retLengths
end


getShiftedMatrix=function(matrix,localShift,dir)
   -- Returns a pose or matrix shifted by vector localShift
   local m={}
   for i=1,12,1 do
      m[i]=matrix[i]
   end
   m[4]=m[4]+dir*(m[1]*localShift[1]+m[2]*localShift[2]+m[3]*localShift[3])
   m[8]=m[8]+dir*(m[5]*localShift[1]+m[6]*localShift[2]+m[7]*localShift[3])
   m[12]=m[12]+dir*(m[9]*localShift[1]+m[10]*localShift[2]+m[11]*localShift[3])
   return m
end

forbidThreadSwitches=function(forbid)
   -- Allows or forbids automatic thread switches.
   -- This can be important for threaded scripts. For instance,
   -- you do not want a switch to happen while you have temporarily
   -- modified the robot configuration, since you would then see
   -- that change in the scene display.
   if forbid then
      forbidLevel=forbidLevel+1
      if forbidLevel==1 then
         simSetThreadAutomaticSwitch(false)
      end
   else
      forbidLevel=forbidLevel-1
      if forbidLevel==0 then
         simSetThreadAutomaticSwitch(true)
      end
   end
end

findCollisionFreeConfig=function(matrix)
   -- Here we search for a robot configuration..
   -- 1. ..that matches the desired pose (matrix)
   -- 2. ..that does not collide in that configuration
   simSetObjectMatrix(ikTarget,-1,matrix)

   -- This robot has 4 joints that have a huge range (i.e. -10'000 - +10'000 degrees)
   -- And since we do not want to search that huge space, we limit the range around the current configuration
   -- We actually do the same during path search
   local cc=getConfig()
   local jointLimitsL={}
   local jointRanges={}
   for i=1,#jh,1 do
      jointLimitsL[i]=cc[i]-360*math.pi/180
      if jointLimitsL[i]<-10000 then jointLimitsL[i]=-10000 end
      jointRanges[i]=720*math.pi/180
      if cc[i]+jointRanges[i]>10000 then jointRanges[i]=10000-cc[i] end
   end
   jointLimitsL[2]=47*math.pi/180
   jointRanges[2]=266*math.pi/180
   jointLimitsL[3]=19*math.pi/180
   jointRanges[3]=322*math.pi/180
   local c=simGetConfigForTipPose(ikGroup,jh,0.65,10,nil,collisionPairs,nil,jointLimitsL,jointRanges)
   return c
end

findSeveralCollisionFreeConfigs=function(matrix,trialCnt,maxConfigs)
   -- Here we search for several robot configurations...
   -- 1. ..that matches the desired pose (matrix)
   -- 2. ..that does not collide in that configuration
   -- 3. ..that does not collide and that can perform the IK linear approach
   simSetObjectMatrix(ikTarget,-1,matrix)
   local cc=getConfig()
   local cs={}
   local l={}
   for i=1,trialCnt,1 do
      local c=findCollisionFreeConfig(matrix)
      if c then
         local dist=getConfigConfigDistance(cc,c)
         local p=0
         local same=false
         for j=1,#l,1 do
            if math.abs(l[j]-dist)<0.001 then
               -- we might have the exact same config. Avoid that
               same=true
               for k=1,#jh,1 do
                  if math.abs(cs[j][k]-c[k])>0.01 then
                     same=false
                     break
                  end
               end
            end
            if same then
               break
            end
         end
         if not same then
            cs[#cs+1]=c
            l[#l+1]=dist
         end
      end
      if #l>=maxConfigs then
         break
      end
   end
   if #cs==0 then
      cs=nil
   end
   return cs
end

getConfig=function()
   -- Returns the current robot configuration
   local config={}
   for i=1,#jh,1 do
      config[i]=simGetJointPosition(jh[i])
   end
   return config
end

setConfig=function(config)
   -- Applies the specified configuration to the robot
   if config then
      for i=1,#jh,1 do
         simSetJointPosition(jh[i],config[i])
      end
   end
end

getConfigConfigDistance=function(config1,config2)
   -- Returns the distance (in configuration space) between two configurations
   local d=0
   for i=1,#jh,1 do
      local dx=(config1[i]-config2[i])*metric[i]
      d=d+dx*dx
   end
   return math.sqrt(d)
end

getPathLength=function(path)
   -- Returns the length of the path in configuration space
   local d=0
   local l=#jh
   local pc=#path/l
   for i=1,pc-1,1 do
      local config1={path[(i-1)*l+1],path[(i-1)*l+2],path[(i-1)*l+3],path[(i-1)*l+4],path[(i-1)*l+5],path[(i-1)*l+6]}
      local config2={path[i*l+1],path[i*l+2],path[i*l+3],path[i*l+4],path[i*l+5],path[i*l+6]}
      d=d+getConfigConfigDistance(config1,config2)
   end
   return d
end

findPath=function(startConfig,goalConfigs,cnt)
   -- Here we do path planning between the specified start and goal configurations. We run the search cnt times,
   -- and return the shortest path, and its length

   -- Following because the robot has "strange" joint limits, e.g. +-10'000, and searching such a large
   -- space would be inefficient for path planning
   local jointLimitsL={}
   local jointLimitsH={}
   for i=1,#jh,1 do
      jointLimitsL[i]=startConfig[i]-360*math.pi/180
      if jointLimitsL[i]<-10000 then jointLimitsL[i]=-10000 end
      jointLimitsH[i]=startConfig[i]+360*math.pi/180
      if jointLimitsH[i]>10000 then jointLimitsH[i]=10000 end
   end
   jointLimitsL[2]=47*math.pi/180
   jointLimitsH[2]=313*math.pi/180
   jointLimitsL[3]=19*math.pi/180
   jointLimitsH[3]=341*math.pi/180

   local task=simExtOMPL_createTask('task')
   simExtOMPL_setAlgorithm(task,OMPLAlgo)
   local jSpaces={}
   for i=1,#jh,1 do
      local proj=i
      if i>3 then proj=0 end
      jSpaces[#jSpaces+1]=simExtOMPL_createStateSpace('j_space'..i,sim_ompl_statespacetype_joint_position,jh[i],{jointLimitsL[i]},{jointLimitsH[i]},proj)
   end

   simExtOMPL_setStateSpace(task,jSpaces)
   simExtOMPL_setCollisionPairs(task,collisionPairs)
   simExtOMPL_setStartState(task,startConfig)
   simExtOMPL_setGoalState(task,goalConfigs[1])

   for i=2,#goalConfigs,1 do
      simExtOMPL_addGoalState(task,goalConfigs[i])
   end
   local path=nil
   local l=999999999999
   --    forbidThreadSwitches(true)
   for i=1,cnt,1 do
      local res,_path=simExtOMPL_compute(task,maxOMPLCalculationTime,-1,200)
      if res>0 and _path then
         local _l=getPathLength(_path)
         if _l<l then
            l=_l
            path=_path
         end
      end
      if path then
         visualizePath(path)
      end
   end
   --    forbidThreadSwitches(false)
   simExtOMPL_destroyTask(task)
   return path,l
end

findShortestPath=function(startConfig,goalConfigs,searchCntPerGoalConfig)
   -- This function will search for several paths between the specified start configuration,
   -- and several of the specified goal configurations. The shortest path will be returned
   local onePath,onePathLength=findPath(startConfig,goalConfigs,searchCntPerGoalConfig)
   return onePath,generatePathLengths(onePath)
end

generateIkPath=function(startConfig,goalPose,steps,ignoreCollisions)
   -- Generates (if possible) a linear, collision free path between a robot config and a target pose
   forbidThreadSwitches(true)
   local currentConfig=getConfig()
   setConfig(startConfig)
   simSetObjectMatrix(ikTarget,-1,goalPose)
   local coll=collisionPairs
   if ignoreCollisions then
      coll=nil
   end
   local c=simGenerateIkPath(ikGroup,jh,steps,coll)
   setConfig(currentConfig)
   forbidThreadSwitches(false)
   if c then
      return c, generatePathLengths(c)
   end
end

executeMotion=function(path,lengths,maxVel,maxAccel,maxJerk)
   dt=simGetSimulationTimeStep()

   -- 1. Make sure we are not going too fast for each individual joint (i.e. calculate a correction factor (velCorrection)):
   jointsUpperVelocityLimits={}
   for j=1,6,1 do
      res,jointsUpperVelocityLimits[j]=simGetObjectFloatParameter(jh[j],sim_jointfloatparam_upper_limit)
   end
   velCorrection=1

   simSetThreadSwitchTiming(200)
   while true do
      posVelAccel={0,0,0}
      targetPosVel={lengths[#lengths],0}
      pos=0
      res=0
      previousQ={path[1],path[2],path[3],path[4],path[5],path[6]}
      local rMax=0
      rmlHandle=simRMLPos(1,0.0001,-1,posVelAccel,{maxVel*velCorrection,maxAccel,maxJerk},{1},targetPosVel)
      while res==0 do
         res,posVelAccel,sync=simRMLStep(rmlHandle,dt)
         if (res>=0) then
            l=posVelAccel[1]
            for i=1,#lengths-1,1 do
               l1=lengths[i]
               l2=lengths[i+1]
               if (l>=l1)and(l<=l2) then
                  t=(l-l1)/(l2-l1)
                  for j=1,6,1 do
                     q=path[6*(i-1)+j]+_getJointPosDifference(path[6*(i-1)+j],path[6*i+j],jt[j]==sim_joint_revolute_subtype)*t
                     dq=_getJointPosDifference(previousQ[j],q,jt[j]==sim_joint_revolute_subtype)
                     previousQ[j]=q
                     r=math.abs(dq/dt)/jointsUpperVelocityLimits[j]
                     if (r>rMax) then
                        rMax=r
                     end
                  end
                  break
               end
            end
         end
      end
      simRMLRemove(rmlHandle)
      if rMax>1.001 then
         velCorrection=velCorrection/rMax
      else
         break
      end
   end
   simSetThreadSwitchTiming(2)

   -- 2. Execute the movement:
   posVelAccel={0,0,0}
   targetPosVel={lengths[#lengths],0}
   pos=0
   res=0
   jointPos={}
   rmlHandle=simRMLPos(1,0.0001,-1,posVelAccel,{maxVel*velCorrection,maxAccel,maxJerk},{1},targetPosVel)
   while res==0 do
      dt=simGetSimulationTimeStep()
      res,posVelAccel,sync=simRMLStep(rmlHandle,dt)
      if (res>=0) then
         l=posVelAccel[1]
         for i=1,#lengths-1,1 do
            l1=lengths[i]
            l2=lengths[i+1]
            if (l>=l1)and(l<=l2) then
               t=(l-l1)/(l2-l1)
               for j=1,6,1 do
                  jointPos[j]=path[6*(i-1)+j]+_getJointPosDifference(path[6*(i-1)+j],path[6*i+j],jt[j]==sim_joint_revolute_subtype)*t
               end
               _applyJoints(jh,jointPos)
               break
            end
         end
      end
      simSwitchThread()
   end
   simRMLRemove(rmlHandle)
end


savePath=function(filename,path,lengths)
   simWriteCustomDataBlock(jacoHandle,filename..'.pathData1',simPackFloatTable(path))
   simWriteCustomDataBlock(jacoHandle,filename..'.pathLength1',simPackFloatTable(lengths))
end

loadPath=function(filename)
   path=simReadCustomDataBlock(jacoHandle,filename..'.pathData1')
   if (not path) then return nil end
   path=simUnpackFloatTable(path)

   lengths=simReadCustomDataBlock(jacoHandle,filename..'.pathLength1')
   if (not lengths) then return nil end
   lengths=simUnpackFloatTable(lengths)
   return path,lengths
end

-- START HERE:
jh={-1,-1,-1,-1,-1,-1}
jt={-1,-1,-1,-1,-1,-1}

for i=1,6,1 do
   jh[i]=simGetObjectHandle('Jaco_joint'..i)
   jt[i]=simGetJointType(jh[i])
end

jacoHandle=simGetObjectHandle('Jaco')
ikTarget=simGetObjectHandle('Jaco_target')
ikTip=simGetObjectHandle('Jaco_tip')
ikGroup=simGetIkGroupHandle('Jaco_ik')

target0=simGetObjectHandle('jacoTarget0')
target1=simGetObjectHandle('jacoTarget1')
target2=simGetObjectHandle('jacoTarget2')
target3=simGetObjectHandle('jacoTarget3')

-- 2 collision pairs: the first for robot self-collision detection, the second for robot-environment collision detection:
collisionPairs={simGetCollectionHandle('Jaco'),simGetCollectionHandle('Jaco'),simGetCollectionHandle('Jaco'),sim_handle_all}
maxVel=10
maxAccel=1
maxJerk=8000
forbidLevel=0
metric={0.2,1,0.8,0.1,0.1,0.1}
ikSteps=20
maxOMPLCalculationTime=4 -- for one calculation. Higher is better, but takes more time
OMPLAlgo=sim_ompl_algorithm_BKPIECE1 -- the OMPL algorithm to use
numberOfOMPLCalculationsPasses=4 -- the number of OMPL calculation runs for a same goal config. The more, the better results, but slower

-- Uncomment following to force not using stored motion data,
-- and to regenerate the motion data:
--simWriteCustomDataBlock(jacoHandle,'',nil)

-- Move close to the first cup (with motion planning):
local m=getShiftedMatrix(simGetObjectMatrix(target1,-1),{-0.05,0,0.1},-1)

displayInfo('searching for several valid goal configurations...')

local configs=findSeveralCollisionFreeConfigs(m,300,5)

displayInfo('searching for several valid paths between the current configuration and found goal configurations...')
path,lengths=findShortestPath(getConfig(),configs,numberOfOMPLCalculationsPasses)
displayInfo(nil)

if path then
   visualizePath(path)
   executeMotion(path,lengths,maxVel,maxAccel,maxJerk)
end

-- Move very close to the first cup (with IK):
local m=getShiftedMatrix(simGetObjectMatrix(target1,-1),{0,0.01,0},-1)

path,lengths=generateIkPath(getConfig(),m,ikSteps,true)

if path then
   executeMotion(path,lengths,maxVel,maxAccel,maxJerk)
end


-- close the hand
simSetIntegerSignal("hand",1)
simWait(1.25)

-- Lift the cup and move closer to the second cup (with IK):
local m=simGetObjectMatrix(target2,-1)
path,lengths=generateIkPath(getConfig(),m,ikSteps,true)
if path then
   executeMotion(path,lengths,maxVel,maxAccel,maxJerk)
end


-- Pour the cup content into the other cup  (with IK):
local m=simGetObjectMatrix(target3,-1)
path,lengths=generateIkPath(getConfig(),m,ikSteps,true)
if path then
   executeMotion(path,lengths,maxVel,maxAccel,maxJerk)
end

-- Move back to configuration before pouring (with IK):
local m=simGetObjectMatrix(target2,-1)
path,lengths=generateIkPath(getConfig(),m,ikSteps,true)
if path then
   executeMotion(path,lengths,maxVel,maxAccel,maxJerk)
end

-- Put the cup back onto the table (with IK):
local m=getShiftedMatrix(simGetObjectMatrix(target1,-1),{0,0.01,0},-1)
path,lengths=generateIkPath(getConfig(),m,ikSteps,true)
if path then
   executeMotion(path,lengths,maxVel,maxAccel,maxJerk)
end



-- open the hand:
simSetIntegerSignal("hand",0)
simWait(1.0)


-- Move a bit back (with IK):
local m=getShiftedMatrix(simGetObjectMatrix(target1,-1),{-0.05,0,0.1},-1)
path,lengths=generateIkPath(getConfig(),m,ikSteps,true)
if path then
   executeMotion(path,lengths,maxVel,maxAccel,maxJerk)
end


-- move back to the initial configuration:
local m=simGetObjectMatrix(target0,-1)
displayInfo('searching for several valid goal configurations...')
local configs=findSeveralCollisionFreeConfigs(m,300,5)
displayInfo('searching for several valid paths between the current configuration and found goal configurations...')
path,lengths=findShortestPath(getConfig(),configs,numberOfOMPLCalculationsPasses)
displayInfo(nil)
if path then
   visualizePath(path)
   executeMotion(path,lengths,maxVel,maxAccel,maxJerk)
end
