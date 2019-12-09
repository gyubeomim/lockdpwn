local input = ""
local output = { }
local directionOutput = { }
local directionOutputCorrespondingIndex = { }

local registeredVector = false
local drawVectors = false
local connectVectors = false

local checkedWelcome = false

-------------------------------------------------------AnimationDrawing-------------------------------------------------------------------------
local StdAccelerationValue_Register_Vector = 1
local debug = false
local letterIndex1 = 1
local MAX_STEP = 100
--

--WELCOME---------------------------------------------------------------------------------------------------------------------------------
local w_letterIndexes  = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
local w_letters ={ "D", "A", "N", "I", "E", "L", "S",      "V", "E", "K", "T", "O", "R",        "F", "R", "A", "M", "E", "W", "O", "R", "K" }
local LETTER_COUNT = 22
local w_MAX_STEP_FIRST = 190
local w_MAX_STEP_SECOND = platform.window:width() + 20
local accelerate = false
local MAX_LETTER_DISTANCE_ACCELERATE = 20
local MAX_LETTER_DISTANCE_NO_ACCELERATE = MAX_LETTER_DISTANCE_ACCELERATE -
                                                w_letterIndexes[1] * MAX_LETTER_DISTANCE_ACCELERATE / w_MAX_STEP_FIRST
local smoothOutDistance = 20
local earlierAccelerationValue = 50 --at least

local StdAccelerationValue = 3 --at accelerate = false
local accelerationValue = 15


local currentLetterIndex
--WELCOME-------------------------------------------------------------------------------------------------------------------------------------------------


--DrawVecs
local stretchFactor = 10
--DrawVecs

--Mouse

local drawCircle = false
local nearestVec = { } --includes stretchFactor
local circleRadius = 25

--Mouse22222

local clickedInCircle = false
local showedPrintings = false

local interactAfterClickInCircle = false
    local baseInteractingVec = {}
    local _interactingVec = {}
local gotInteractingVec = false

--Mouse

function on.timer() --fires automatically

if checkedWelcome then
    slowDownFactor = (StdAccelerationValue_Register_Vector - letterIndex1) / MAX_STEP --random ?!
    letterIndex1 = letterIndex1 + (StdAccelerationValue_Register_Vector - (letterIndex1 * slowDownFactor))
    platform.window:invalidate()
else ---------------------------===DO WELCOME===

    for currentIndexChanger = 1,LETTER_COUNT,1 do
            if not accelerate then --accelerate = false
                            MAX_LETTER_DISTANCE_NO_ACCELERATE = MAX_LETTER_DISTANCE_ACCELERATE -
                                                            w_letterIndexes[1] * MAX_LETTER_DISTANCE_ACCELERATE / w_MAX_STEP_FIRST

                if (currentIndexChanger == 1) or
                    (currentIndexChanger > 1 and w_letterIndexes[currentIndexChanger - 1] - w_letterIndexes[currentIndexChanger] >=
                        MAX_LETTER_DISTANCE_NO_ACCELERATE) then --------------------------------------------------------------------manage letter distance

                           local slowDownFactor = w_letterIndexes[currentIndexChanger] * 0.01315789473

                           if currentIndexChanger < LETTER_COUNT and slowDownFactor >= 2.5 then
                                slowDownFactor = slowDownFactor - 1
                           end

                        w_letterIndexes[currentIndexChanger] = w_letterIndexes[currentIndexChanger] + StdAccelerationValue - slowDownFactor

                        if w_letterIndexes[currentIndexChanger] == w_letterIndexes[LETTER_COUNT] and w_letterIndexes[currentIndexChanger] >
                                    w_MAX_STEP_FIRST - earlierAccelerationValue then
                            accelerate = true
                        end

                end


            else --accelerate == true


                if (currentIndexChanger == 1) or  ----------manage letter distance
                (currentIndexChanger > 1 and w_letterIndexes[currentIndexChanger - 1] - w_letterIndexes[currentIndexChanger] >= MAX_LETTER_DISTANCE_ACCELERATE) then

                    local speedUpFactor = w_letterIndexes[currentIndexChanger] * 0.01315789473

                    w_letterIndexes[currentIndexChanger] = w_letterIndexes[currentIndexChanger] + accelerationValue + (speedUpFactor)
                    if w_letterIndexes[currentIndexChanger] == w_letterIndexes[LETTER_COUNT] and w_letterIndexes[currentIndexChanger] > w_MAX_STEP_SECOND then
                        timer.stop()
                        checkedWelcome = true
                    end

                end
            end
        platform.window:invalidate()
    end
end  ---------------------------===DO WELCOME===

end --endfunc


function DrawTextAnimation(gc)

    if debug then letterIndex1 = MAX_STEP + 1 end

    if letterIndex1 <= MAX_STEP then
        gc:setFont("serif","bi",12)
        gc:setColorRGB(0, 102, 51)
        gc:drawString("Vektor regestriert!", 170 - letterIndex1 ,5,"top")
        timer.start(0.01)
    else
        gc:setColorRGB(0,0,0)
        gc:setFont("serif","r",12)
        timer.stop()
        letterIndex1 = 1
        registeredVector = false
    end

end --endfunc

--===========================================WELCOME MSG=============================================================================================

function DoWelcome(gc)

timer.start(0.01)

--show letters only
for i = 1, LETTER_COUNT, 1 do

    local travelDistance = w_MAX_STEP_FIRST

        if i < LETTER_COUNT then
            travelDistance = travelDistance + smoothOutDistance
        end

   if (w_letterIndexes[i] <= travelDistance and not accelerate) or (accelerate and w_letterIndexes[i] <= w_MAX_STEP_SECOND) then
        gc:drawString(w_letters[i]         , platform.window:width() + 10 - w_letterIndexes[i]                , platform.window:height() / 2 ,"middle")
   end
end
--show letters only

end
--===========================================WELCOME MSG=============================================================================================


-------------------------------------------------------AnimationDrawing-------------------------------------------------------------------------

 --====================================================PAINTING / MAIN FUNC=================================================================
  --====================================================PAINTING / MAIN FUNC=================================================================
 --====================================================PAINTING / MAIN FUNC=================================================================

function on.paint(gc)

    if not checkedWelcome then --welcome msg loading
        gc:setColorRGB(218,165,32)
        gc:setFont("serif","bi",14)
        DoWelcome(gc)
        return
    else
        gc:setColorRGB(0,0,0)
        gc:setFont("serif","r",12)
    end

    --start here

    if interactAfterClickInCircle and gotInteractingVec then --interactAfterClickInCircle: click circle -> type c as input => press enter
        platform.window:invalidate()
        input = ""
        PrintInteractingResult(gc)
        return --pretend more drawings
    end


    if stretchFactor and not clickedInCircle and not interactAfterClickInCircle then --draw stretchFactor
         gc:setFont("serif","r",6)
         gc:drawString("Scaling: "..tostring(stretchFactor),190,5,"top")
         gc:setFont("serif","r",12)
    end


    if string.len(input) > 0 and not clickedInCircle and not interactAfterClickInCircle then --printing help
        PrintHelp(gc)
    end

    if clickedInCircle and showedPrintings then --clicked in circle and got input a,b or c ; after pressing enter

        platform.window:invalidate()

        if input == "a" then
            ShowVectorLenght(gc)
        elseif input == "b" then
            ShowVectorAngleToAxis(gc)
        elseif input == "c" then
            CheckStretchFactor()
            CheckStretchFactor() --refresh checking
            DrawOPVectors(gc)

            interactAfterClickInCircle = true
            baseInteractingVec[1] = nearestVec[1]
            baseInteractingVec[2] = nearestVec[2]

            WaitForInteractingVec(gc)
        elseif input == "" then
            showPrinting = false
        end

        input = ""
    elseif clickedInCircle and not showedPrintings and not interactAfterClickInCircle then --clicked in circle true
        platform.window:invalidate()
        gc:setFont("serif","b",10)
        gc:drawString(input,190,40,"top")
        gc:setFont("serif","r",12)
        DrawOptionsMenuAfterClick(gc)
    end

    if drawCircle and not clickedInCircle and string.len(input) == 0 then --draw circle true
        platform.window:invalidate()
        gc:setPen("thin","dotted")
        gc:setColorRGB(139,0,139) --magenta circle drawing
        gc:drawArc(nearestVec[1] - circleRadius / 2, nearestVec[2] - circleRadius / 2, circleRadius, circleRadius, 0, 360) --draws a circle at vec point
         gc:setColorRGB(0,0,0)
        gc:setPen("thin","smooth")
    end

    if drawVectors and not clickedInCircle then --drw input
        CheckStretchFactor()
        CheckStretchFactor() --refresh checking
        DrawOPVectors(gc)
    end

    if connectVectors then --cnt input
        CheckStretchFactor()
        CheckStretchFactor() --refresh checking
        ConnectVectors(gc)
    end

    if not registeredVector and not clickedInCircle then
        gc:drawString(input,5,5,"top")
    elseif registeredVector then
        DrawTextAnimation(gc)
    end
end
--====================================================PAINTING / MAIN FUNC=================================================================
 --====================================================PAINTING / MAIN FUNC=================================================================
  --====================================================PAINTING / MAIN FUNC=================================================================


-------------------------------------------------------CHAR_IN_KEY-------------------------------------------------------------------------
function on.charIn(char)
    if string.len(input) <= 25 and checkedWelcome and not drawVectors then
        input = input..char
        platform.window:invalidate()
    end
end
-------------------------------------------------------CHAR_IN_KEY-------------------------------------------------------------------------



-------------------------------------------------------BACKSPC_KEY-------------------------------------------------------------------------
function on.backspaceKey()

    if not checkedWelcome then return end

    input = string.usub(input,0, string.len(input) - 1)
    platform.window:invalidate()
end
-------------------------------------------------------BACKSPC_KEY-------------------------------------------------------------------------


-------------------------------------------------------RETURN_KEY-------------------------------------------------------------------------
function on.enterKey()

if showedPrintings and clickedInCircle and not interactAfterClickInCircle then
    platform.window:invalidate()
    drawVectors = true
    input = ""

    --RESET
        showedPrintings = false
        clickedInCircle = false
    --RESET
elseif clickedInCircle and not showedPrintings then
        platform.window:invalidate()
        showedPrintings = true
end

if interactAfterClickInCircle and gotInteractingVec then
    platform.window:invalidate()
    drawVectors = true
    input = ""

    --RESET
        gotInteractingVec = false
        interactAfterClickInCircle = false
        _interactingVec = {}
        baseInteractingVec = {}
        --showedPrintings and clickedInCircle already reseted after getting interacting vec
    --RESET
end

----------------------------------------normal vector input
if input == "" then return end

if input == "drw" then --draw Vecs
    drawVectors = true
    input = ""
    platform.window:invalidate()
    return
elseif input == "cnt" then --connect
    connectVectors = true
    input = ""
    platform.window:invalidate()
    return
elseif not clickedInCircle then --add Vecs
    if string.match(input, "d") then --add directional Vec
            local firstOne = false
            for element in string.gmatch(input, '([^,]+)') do
                if element ~= "d" then
                    if not firstOne then
                        firstOne = true
                        directionOutputCorrespondingIndex[#directionOutputCorrespondingIndex + 1] = element
                    else
                        directionOutput[#directionOutput + 1] = element
                    end
                end
            end
    else --add normal Vec
        for element in string.gmatch(input, '([^,]+)') do
            output[#output + 1] = element
        end
    end

    input = ""
    platform.window:invalidate()
    registeredVector = true
end

end

local screenWidht = platform.window:width()
local screenHeight = platform.window:height()
-------------------------------------------------------RETURN_KEY-------------------------------------------------------------------------


-------------------------------------------------------DrawVecs-------------------------------------------------------------------------

function RotateVecStd(x, y, angle)

local solutions = { 0,0 }
solutions[1] = x * math.cos(angle) - y * math.sin(angle)
solutions[2] = x * math.sin(angle) + y * math.cos(angle)

return solutions

end

function GetVecLenght(x, y)
    return math.sqrt(x*x + y*y)
end

function DrawOPVectors(gc)

local vecX = nil

index = 1
for _, _vec in ipairs(output) do
    vec = tonumber(_vec)
    if not vecX then vecX = vec else
        --x exists
        --vecX => x
        --vec => y
        gc:setPen("medium","smooth")
        gc:drawLine(0, 0, vecX * stretchFactor, vec * stretchFactor)
        DrawSmallArrow(0, 0, vecX * stretchFactor, vec * stretchFactor,   gc)
        gc:setPen("thin","smooth")
            gc:setFont("serif","r",8)
            gc:drawString(index..".".."("..vecX.."|"..vec..")", vecX * stretchFactor / 2 + 5, vec * stretchFactor / 2, "bottom")
            gc:setFont("serif","r",12)
        --gc:setPen("thick","dotted")
        vecX = nil
        index = index + 1
    end
end

DrawDirectionalVectors(gc)

input = ""
drawVectors = false

end --endfunc

function DrawSmallArrow(xStart, yStart, xEnd, yEnd,  gc)

local resultungLenght = 10
local x = xEnd - xStart
local y = yEnd - yStart

local multiplyFactor = resultungLenght / GetVecLenght(x, y)
x = x * multiplyFactor
y = y * multiplyFactor

local rotatedVecs = RotateVecStd(x, y, -405) --array
local rotatedVecs2 = RotateVecStd(x, y, 405) --array
X = 1
Y = 2

gc:setColorRGB(0, 0, 255)
gc:drawLine(xEnd, yEnd, xEnd + rotatedVecs[X], yEnd + rotatedVecs[Y])
gc:drawLine(xEnd, yEnd, xEnd + rotatedVecs2[X], yEnd + rotatedVecs2[Y])
gc:setColorRGB(0, 0, 0)

platform.window:invalidate()

end

function DrawDirectionalVectors(gc)

if #directionOutput < 2 then return end

local correspondingIndexCount = 1
for _, correspondingIndex in ipairs(directionOutputCorrespondingIndex) do
    local realOpVecIndex = correspondingIndex * 2 - 1
    local dirDirVecIndex = correspondingIndexCount * 2 - 1

        dirVecX = directionOutput[dirDirVecIndex] * stretchFactor
        dirVecY = directionOutput[dirDirVecIndex + 1] * stretchFactor
        opVecX = output[realOpVecIndex] * stretchFactor
        opVecY = output[realOpVecIndex + 1] * stretchFactor

        --already smooth
        gc:setColorRGB(0, 255, 0)
        gc:drawLine(opVecX, opVecY, opVecX + dirVecX, opVecY + dirVecY)
        DrawSmallArrow(opVecX, opVecY, opVecX + dirVecX, opVecY + dirVecY, gc)
        gc:setColorRGB(0, 0, 0)

            gc:setFont("serif","i",8)
            gc:drawString("("..dirVecX / stretchFactor.."|"..dirVecY / stretchFactor..")", (opVecX + dirVecX / 2) + 5, (opVecY + dirVecY / 2), "bottom")
            gc:setFont("serif","r",12)

    correspondingIndexCount = correspondingIndexCount + 1
end

end

function CheckStretchFactor()

screenWidth = platform.window:width()
screenHeight = platform.window:height()

--OP VECS
local vecX = nil
local biggestXVec = {}
local biggestYVec = {}
local finalBigVec = {}

for _, _vec in ipairs(output) do
    vec = tonumber(_vec)
    if not vecX then vecX = vec else

            if vecX * stretchFactor > screenWidth or vec * stretchFactor > screenHeight then
                if #biggestXVec == 0 or biggestXVec[1] < vecX then
                    biggestXVec[1] = vecX
                    biggestXVec[2] = vec
                end

                if #biggestYVec == 0 or biggestYVec[2] < vec then
                    biggestYVec[1] = vecX
                    biggestYVec[2] = vec
                end
            end

        vecX = nil
    end
end
--OP VECS

--DIR VECS
if #directionOutput >= 2 then

local correspondingIndexCount = 1
for _, correspondingIndex in ipairs(directionOutputCorrespondingIndex) do
    local realOpVecIndex = correspondingIndex * 2 - 1
    local dirDirVecIndex = correspondingIndexCount * 2 - 1

        dirVecX = directionOutput[dirDirVecIndex] * stretchFactor
        dirVecY = directionOutput[dirDirVecIndex + 1] * stretchFactor
        opVecX = output[realOpVecIndex] * stretchFactor
        opVecY = output[realOpVecIndex + 1] * stretchFactor

        if opVecX + dirVecX > screenWidth or opVecY + dirVecY > screenHeight then ------------------ > overextending op + dir
                if #biggestXVec == 0 or biggestXVec[1] < (opVecX / stretchFactor) + (dirVecX / stretchFactor) then
                    biggestXVec[1] = (opVecX / stretchFactor) + (dirVecX / stretchFactor)
                    biggestXVec[2] = (opVecY / stretchFactor) + (dirVecY / stretchFactor)
                end
                if #biggestYVec == 0 or biggestYVec[2] < (opVecY / stretchFactor) + (dirVecY / stretchFactor) then
                    biggestXVec[1] = (opVecX / stretchFactor) + (dirVecX / stretchFactor)
                    biggestXVec[2] = (opVecY / stretchFactor) + (dirVecY / stretchFactor)
                end
        end

    correspondingIndexCount = correspondingIndexCount + 1
end

end
--DIR VECS






--get highest value being outta screen
if #biggestXVec > 0 and #biggestYVec == 0 then -----take X_VEC
    finalBigVec[1] = biggestXVec[1]
    finalBigVec[2] = biggestXVec[2]
elseif #biggestXVec == 0 and #biggestYVec > 0 then --take Y_VEC
    finalBigVec[1] = biggestYVec[1]
    finalBigVec[2] = biggestYVec[2]
elseif #biggestXVec > 0 and #biggestYVec > 0  then ---both contains smth
    if screenWidth / (biggestXVec[1] * stretchFactor) < screenHeight / (biggestYVec[2] * stretchFactor) then --overextending dist of X_Vec higher (percentage)
        finalBigVec[1] = biggestXVec[1]
        finalBigVec[2] = biggestXVec[2]
    else ------------------------------------------------------------------overextending dist of Y_Vec higher
        finalBigVec[1] = biggestYVec[1]
        finalBigVec[2] = biggestYVec[2]
    end
elseif #biggestXVec == 0 and #biggestYVec == 0 and #output > 0 then --no overextending vectors cotnained
    ExtendStretchFactor()
end

if #finalBigVec == 0 then return end --no overextending vectors

--check
if finalBigVec[1] > finalBigVec[2] then --X biggest component
stretchFactor = screenWidth / finalBigVec[1] -----------------------NEW STRETCH FACTOR
else -------------------------------------Y biggest component
stretchFactor = screenHeight / finalBigVec[2] -----------------------NEW STRETCH FACTOR
end
--check

end --endfunc

function ExtendStretchFactor() --increase factor instead of decreasing

screenWidth = platform.window:width()
screenHeight = platform.window:height()

--OP VECS INCREASE
local vecX = nil
local biggestXVec = {}
local biggestYVec = {}
local finalBigVec = {}

for _, _vec in ipairs(output) do
    vec = tonumber(_vec)
    if not vecX then vecX = vec else

        if #biggestXVec == 0 or biggestXVec[1] < vecX then
            biggestXVec[1] = vecX
            biggestXVec[2] = vec
        end

        if #biggestYVec == 0 or biggestYVec[2] < vec then
            biggestYVec[1] = vecX
            biggestYVec[2] = vec
        end

        vecX = nil
    end
end
--OP VECS INCREASE

--DIR VECS INCREASE

if #directionOutput >= 2 then

local correspondingIndexCount = 1
for _, correspondingIndex in ipairs(directionOutputCorrespondingIndex) do
    local realOpVecIndex = correspondingIndex * 2 - 1
    local dirDirVecIndex = correspondingIndexCount * 2 - 1

        dirVecX = directionOutput[dirDirVecIndex] * stretchFactor
        dirVecY = directionOutput[dirDirVecIndex + 1] * stretchFactor
        opVecX = output[realOpVecIndex] * stretchFactor
        opVecY = output[realOpVecIndex + 1] * stretchFactor

            if #biggestXVec == 0 or biggestXVec[1] < (opVecX / stretchFactor) + (dirVecX / stretchFactor) then
                biggestXVec[1] = (opVecX / stretchFactor) + (dirVecX / stretchFactor)
                biggestXVec[2] = (opVecY / stretchFactor) + (dirVecY / stretchFactor)
            end
            if #biggestYVec == 0 or biggestYVec[2] < (opVecY / stretchFactor) + (dirVecY / stretchFactor) then
                biggestXVec[1] = (opVecX / stretchFactor) + (dirVecX / stretchFactor)
                biggestXVec[2] = (opVecY / stretchFactor) + (dirVecY / stretchFactor)
            end

    correspondingIndexCount = correspondingIndexCount + 1
end

end

--DIR VECS INCREASE

local finalBigVec = { }

--get highest value
---both contains smth 100%
    if  screenWidth / (biggestXVec[1] * stretchFactor) < screenWidth / (biggestYVec[2] * stretchFactor) then -- take lower scaling needed (percentage)
        finalBigVec[1] = biggestXVec[1]
        finalBigVec[2] = biggestXVec[2]
    else ------------------------------------------------------------------overextending dist of Y_Vec higher
        finalBigVec[1] = biggestYVec[1]
        finalBigVec[2] = biggestYVec[2]
    end

if #finalBigVec == 0 then return end --no overextending vectors

--check
if finalBigVec[1] > finalBigVec[2] then --X biggest component
stretchFactor = screenWidth / finalBigVec[1] -----------------------NEW STRETCH FACTOR
else -------------------------------------Y biggest component
stretchFactor = screenHeight / finalBigVec[2] -----------------------NEW STRETCH FACTOR
end
--check

end --endfunc

-------------------------------------------------------DrawVecs-------------------------------------------------------------------------

-------------------------------------------------------ConnectVecs-------------------------------------------------------------------------
function ConnectVectors(gc)

DrawOPVectors(gc)
DrawDirectionalVectors(gc)

if #directionOutput < 2 then return end

local correspondingIndexCount = 1
for _, correspondingIndex in ipairs(directionOutputCorrespondingIndex) do
    local realOpVecIndex = correspondingIndex * 2 - 1
    local dirDirVecIndex = correspondingIndexCount * 2 - 1

        dirVecX = directionOutput[dirDirVecIndex] * stretchFactor
        dirVecY = directionOutput[dirDirVecIndex + 1] * stretchFactor
        opVecX = output[realOpVecIndex] * stretchFactor
        opVecY = output[realOpVecIndex + 1] * stretchFactor

        --already smooth
        gc:setColorRGB(255, 0, 0)
        gc:setPen("thin","dotted")
        gc:drawLine(0, 0, opVecX + dirVecX, opVecY + dirVecY)
        gc:setPen("thin","smooth")
        DrawSmallArrow(0, 0, opVecX + dirVecX, opVecY + dirVecY, gc)
        gc:setColorRGB(0, 0, 0)

    correspondingIndexCount = correspondingIndexCount + 1
end

platform.window:invalidate()
connectVectors = false

end

-------------------------------------------------------ConnectVecs-------------------------------------------------------------------------


-------------------------------------------------------PrintHelp-------------------------------------------------------
function PrintHelp(gc)

gc:setColorRGB(0, 0, 0)
gc:setFont("serif","r",6)

gc:drawString("Hilfe: ", 5, platform.window:height() - 50, "bottom")
gc:drawString("Vektor hinzufügen                     : <X>,<Y>", 5, platform.window:height() - 40, "bottom")
gc:drawString("Ritchtungsvektor hinzufügen      : d,<Stützvektor nummer>,<X>,<Y>", 5, platform.window:height() - 30, "bottom")
gc:drawString("Vektoren zeichnen lassen          : drw", 5, platform.window:height() - 20, "bottom")
gc:drawString("Resultierende Vektoren zeichnen: cnt", 5, platform.window:height() - 10, "bottom")

gc:setFont("serif","r",12)

end
-------------------------------------------------------PrintHelp-------------------------------------------------------








--======================================================Mouse Managing======================================================--

function on.mouseMove(x,y)
    if not checkedWelcome or clickedInCircle or #_interactingVec > 0 then return end

    platform.window:invalidate()
    if #output > 0 then
        drawVectors = true --reverse screen reset
    end
    GetNearestVector(x,y)

end

function GetDistance(x1, y1, x2, y2)

    local resultingX = x2 - x1
    local resultingY = y2 - y1

    return GetVecLenght(resultingX, resultingY)

end




function GetNearestVector(mouseX, mouseY)

nearestVec = {}

X = 1
Y = 2

--OP VECS
local vecX = nil

for _, _vec in ipairs(output) do
    vec = tonumber(_vec)
    if not vecX then vecX = vec else
        vecX = vecX * stretchFactor
        vec = vec * stretchFactor

        local currDistToMouse = GetDistance(mouseX, mouseY, vecX, vec) --vec = Y component

        if #nearestVec == 0 or GetDistance(nearestVec[X], nearestVec[Y], mouseX, mouseY) > currDistToMouse then
            nearestVec[X] = vecX
            nearestVec[Y] = vec
        end

        vecX = nil
    end
end



--DIR VECS

if #directionOutput >= 2 then

    local correspondingIndexCount = 1
    for _, correspondingIndex in ipairs(directionOutputCorrespondingIndex) do
        local realOpVecIndex = correspondingIndex * 2 - 1
        local dirDirVecIndex = correspondingIndexCount * 2 - 1

            dirVecX = directionOutput[dirDirVecIndex] * stretchFactor
            dirVecY = directionOutput[dirDirVecIndex + 1] * stretchFactor
            opVecX = output[realOpVecIndex] * stretchFactor
            opVecY = output[realOpVecIndex + 1] * stretchFactor

            local currDistToMouse_DirVec = GetDistance(mouseX, mouseY, opVecX + dirVecX, opVecY + dirVecY) --vec = Y component

            if #nearestVec == 0 or GetDistance(nearestVec[X], nearestVec[Y], mouseX, mouseY) > currDistToMouse_DirVec then
                nearestVec[X] = opVecX + dirVecX
                nearestVec[Y] = opVecY + dirVecY
            end

        correspondingIndexCount = correspondingIndexCount + 1
    end

end


-------------check near

if #nearestVec > 0 and GetDistance(nearestVec[X], nearestVec[Y], mouseX, mouseY) <= circleRadius then --draw circle
    drawCircle = true
else
    drawCircle = false
end

-------------check near

end --endfunc

--======================================================Mouse Managing 222222222================================================--

function on.mouseDown(x,y)

GetNearestVector(x,y)

if not drawCircle then return end
if interactAfterClickInCircle and gotInteractingVec then return end

if GetDistance(x, y, nearestVec[1], nearestVec[2]) <= circleRadius then

    if not interactAfterClickInCircle then --first click before interacting
        clickedInCircle = true
        platform.window:invalidate()
        input = ""
    elseif #_interactingVec == 0 then --interacting click
        _interactingVec[1] = nearestVec[1]
        _interactingVec[2] = nearestVec[2]
        gotInteractingVec = true
        platform.window:invalidate()
    end
end

end --endfunc

function DrawOptionsMenuAfterClick(gc)

local yStep = 30
local rectWidth = 20
local rectHeight = 20

gc:setColorRGB(0, 0, 0)
gc:setFont("serif","bi",10)

gc:drawString("Länge ", 5, yStep, "bottom")
gc:drawRect(170 - rectWidth / 2, yStep - rectHeight / 2, rectWidth, rectHeight)
gc:drawString("a", 170, yStep + 5, "bottom")

gc:drawString("Winkel zur X-Achse", 5, yStep*2, "bottom")
gc:drawRect(170 - rectWidth / 2, yStep*2 - rectHeight / 2, rectWidth, rectHeight)
gc:drawString("b", 170, yStep*2 + 5, "bottom")

gc:drawString("Interagieren mit..", 5, yStep*3, "bottom")
gc:drawRect(170 - rectWidth / 2, yStep*3 - rectHeight / 2, rectWidth, rectHeight)
gc:drawString("c", 170, yStep*3 + 5, "bottom")

gc:setFont("serif","r",12)

end

--======================================================Mouse 333333333333=================================================--

function ShowVectorLenght(gc)

local lenght = GetVecLenght(nearestVec[1] / stretchFactor, nearestVec[2] / stretchFactor)

gc:setFont("serif","bi",12)
gc:drawString("Länge: "..tostring(lenght), 5, 15, "top")
gc:setFont("serif","bi",12)

end

function AngleBetweenVecs(x,y,x2,y2)
    X = 1
    Y = 2

    local vec1 = { x, y}
    local vec2 = { x2, y2}
    local dotProduct = vec1[X] * vec2[X] + vec1[Y] * vec2[Y]

    local vec1Lenght = GetVecLenght(vec1[X], vec1[Y])
    local vec2Lenght = GetVecLenght(vec2[X], vec2[Y])

    local cosine = dotProduct / (vec1Lenght * vec2Lenght)

    return math.acos(cosine) * (180 / math.pi) --rad to deg
end

function ShowVectorAngleToAxis(gc)

local X_Axis_Vec = { 0, 10 }
local angleBetween = AngleBetweenVecs(nearestVec[1], nearestVec[2], X_Axis_Vec[1], X_Axis_Vec[2])

gc:setFont("serif","bi",12)
gc:drawString("Winkel: "..tostring(angleBetween).."°", 5, 15, "top")
gc:setFont("serif","bi",12)

end

--======================================================Interacting Vec======================================================--

function WaitForInteractingVec(gc)

    gc:setFont("serif","bi",12)
    gc:setColorRGB(218,165,32)
    gc:drawString("Warte auf Vektor..", 170 ,5,"top")
    gc:setFont("serif","r",12)
    gc:setColorRGB(0, 0, 0)

    showedPrintings = false
    clickedInCircle = false
end

function IsOp_Dir_Vec(x, y) --with stretch ; returns op and dir if vec is op + dir vec

X = 1
Y = 2

local xComponent = x * stretchFactor
local yComponent = y * stretchFactor

if #directionOutput >= 2 then

    local correspondingIndexCount = 1
    for _, correspondingIndex in ipairs(directionOutputCorrespondingIndex) do
        local realOpVecIndex = correspondingIndex * 2 - 1
        local dirDirVecIndex = correspondingIndexCount * 2 - 1

            dirVecX = directionOutput[dirDirVecIndex] * stretchFactor
            dirVecY = directionOutput[dirDirVecIndex + 1] * stretchFactor
            opVecX = output[realOpVecIndex]* stretchFactor
            opVecY = output[realOpVecIndex + 1] * stretchFactor

            if opVecX + dirVecX == xComponent and opVecY + dirVecY == yComponent and dirVecX > 0 and dirVecY > 0 then --op + dir = parameter vec
                    local completeVec = { opVecX, opVecY, dirVecX, dirVecY }
                    return completeVec
            end

        correspondingIndexCount = correspondingIndexCount + 1
    end

end

return nil

end --endfunc

function VecsAreCollinear(x, y, x2, y2)

local multiplyFactor_ForX  = x2 / x
local multiplyFactor_ForY = y2 / y

return multiplyFactor_ForX == multiplyFactor_ForY

end






function PrintInteractingResult(gc)

X = 1
Y = 2
Z = 3

local baseVec = { baseInteractingVec[X] / stretchFactor, baseInteractingVec[Y] / stretchFactor, 0 }
local interactingVec = { _interactingVec[X] / stretchFactor, _interactingVec[Y] / stretchFactor, 0 }

local angleBetween = AngleBetweenVecs(baseVec[X], baseVec[Y], nearestVec[X], nearestVec[Y])

gc:setFont("serif","bi",12)
gc:drawString("Richtungsvekt. werden zusammengefasst!", 5, 5, "top")
gc:setColorRGB(218,165,32)
gc:drawString("Winkel zwischen ("..baseVec[X].."|"..baseVec[Y]..") und ("..interactingVec[X].."|"..interactingVec[Y]..")" , 5 ,5+35,"top")
gc:drawString("=> "..angleBetween.."°", 5, 5+35+15, "top")

local vectorProduct_2D_X = baseVec[Y] * interactingVec[Z] - interactingVec[Y] * baseVec[Z]
local vectorProduct_2D_Y = baseVec[Z] * interactingVec[X] - interactingVec[Z] * baseVec[X]
local vectorProduct_2D_Z = baseVec[X] * interactingVec[Y] - interactingVec[X] * baseVec[Y]

local resultingA = math.sqrt(vectorProduct_2D_X*vectorProduct_2D_X + vectorProduct_2D_Y*vectorProduct_2D_Y + vectorProduct_2D_Z*vectorProduct_2D_Z)

gc:drawString("Fläche (Parallelogramm)", 5 ,40+35,"top")
gc:drawString("=> "..resultingA , 5, 40+35+15, "top")

-------------------------------------------------------checking if OP + Dir Vec



local __baseVec = IsOp_Dir_Vec(baseVec[X], baseVec[Y])
local __interactingVec = IsOp_Dir_Vec(interactingVec[X], interactingVec[Y])

if __baseVec and __interactingVec then --both vectors are resulting vecs of op + dir (they are ops btw)

    if not VecsAreCollinear(__baseVec[3], __baseVec[4],   __interactingVec[3], __interactingVec[4]) then --dir vecs will ever face each other

        local k = (__interactingVec[3] * (__interactingVec[2] - __baseVec[2]) - __interactingVec[4] * (__interactingVec[1] - __baseVec[1]) )/
            (__interactingVec[3]* __baseVec[4] - __interactingVec[4] * __baseVec[3])

        local l = (__baseVec[3] * (__interactingVec[2] - __baseVec[2]) - __baseVec[4] * (__interactingVec[1] - __baseVec[1])) /
            (__interactingVec[3] * __baseVec[4] - __interactingVec[4] * __baseVec[3])

            gc:drawString("Veks treffen sich bei:\n("..__baseVec[1] / stretchFactor.."|"..__baseVec[2] / stretchFactor..") + "..k.." * ("..
                                                                        __baseVec[3] / stretchFactor.."|"..__baseVec[4] / stretchFactor..")",5 ,40+35*2,"top")
            gc:drawString("("..__interactingVec[1] / stretchFactor.."|"..__interactingVec[2] / stretchFactor..") + "..l.." * "..
                                                                        "("..__interactingVec[3] / stretchFactor.."|"..__interactingVec[4] / stretchFactor..")",
                                                                             5 ,40+35*2+45,"top")
    else --dir vecs will possibly never face each other
        gc:drawString("Richtungsvektoren sind kollinear", 5 ,40+35*2,"top")

        --check if facing

        local kForX = ((__interactingVec[1] / stretchFactor) - (__baseVec[1] / stretchFactor)) / (__baseVec[3] / stretchFactor)
        local kForY = ((__interactingVec[2] / stretchFactor) - (__baseVec[2] / stretchFactor)) / (__baseVec[4] / stretchFactor)

        if kForX == kForY then --they face
            gc:drawString("Punktprobe positiv", 5 ,40+35*3,"top")
        end
    end
else
    --not 2 dir vecs included
end


--end func from here
gc:setFont("serif","r",12)
gc:setColorRGB(0, 0, 0)
end--endfunc

--======================================================Mouse Managing======================================================--
