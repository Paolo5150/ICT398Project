--AI Scripts must take in and return the same amount of values as the Think function shown here, everything else is at the user's discretion

--Script variables
movementSpeed = 500;
rotationSpeed = 5;
agroDistance = 5000; --Distance the ai will notice and start following the target
maxFollowDistance = 6000; --Distance the ai will stop following the target
attackDistance = 150; --Distance the ai will switch to fighting
fowardMovement = 0;
rightMovement = 0;
rotation = 0;
animation = 0;

--C++ variables
_state = "";
_targetDistance = 0;
_targetRotation = 0;
_targetRotationReverse = 0;
_nodeDistance = 0;
_nodeRotation = 0;
_nodeRotationReverse = 0;
_wanderPosX = -1;
_wanderPosY = -1;
_wanderPosZ = -1;
_terrainMaxX = 0;
_terrainMaxZ = 0;
_timerCurrentTime = 0;
_timerDeltaS = 0;
_lastStateChange = 0;
_randomTimer = 0;
_eventReceived = false;

function PopulateVariables(state, targetDistance, targetRotation, targetRotationReverse, nodeDistance, nodeRotation, nodeRotationReverse, wanderPosX, wanderPosY, wanderPosZ, terrainMaxX, terrainMaxZ, timerCurrentTime, timerDeltaS, lastStateChange, randomTimer, eventReceived)
    _state = state;
    _targetDistance = targetDistance;
    _targetRotation = targetRotation;
    _targetRotationReverse = targetRotationReverse;
    _nodeDistance = nodeDistance;
    _nodeRotation = nodeRotation;
    _nodeRotationReverse = nodeRotationReverse;
    _wanderPosX = wanderPosX;
    _wanderPosY = wanderPosY;
    _wanderPosZ = wanderPosZ;
    _terrainMaxX = terrainMaxX;
    _terrainMaxZ = terrainMaxZ;
    _timerCurrentTime = timerCurrentTime;
    _timerDeltaS = timerDeltaS;
    _lastStateChange = lastStateChange;
    _randomTimer = randomTimer;
    _eventReceived = eventReceived;
end

function RandomWanderPos()
    _wanderPosX = math.random() + math.random(_terrainMaxX - 200, _terrainMaxZ - 200);
    _wanderPosY = math.random() + math.random(_terrainMaxX - 200, _terrainMaxZ - 200);
    _wanderPosZ = math.random() + math.random(_terrainMaxX - 200, _terrainMaxZ - 200);
end

function ClearWanderPos()
    _wanderPosX = -1
    _wanderPosY = -1
    _wanderPosZ = -1
end

--Entry function
--Returns: state, animation, fowardMovement, rightMovement, rotation(left/right), wanderDirection
function Think(state, targetDistance, targetRotation, targetRotationReverse, nodeDistance, nodeRotation, nodeRotationReverse, wanderPosX, wanderPosY, wanderPosZ, terrainMaxX, terrainMaxZ, timerCurrentTime, timerDeltaS, lastStateChange, randomTimer, eventReceived)
    PopulateVariables(state, targetDistance, targetRotation, targetRotationReverse, nodeDistance, nodeRotation, nodeRotationReverse, wanderPosX, wanderPosY, wanderPosZ, terrainMaxX, terrainMaxZ, timerCurrentTime, timerDeltaS, lastStateChange, randomTimer, eventReceived);
    
    if(_eventReceived == true) then
        _state = "Seek";
        Seek();
    end

    if(_state == "Idle") then
        Idle();
    elseif(_state == "Wander") then
        Wander();
    elseif(_state == "Seek") then
        Seek();
    elseif(_state == "Fight") then
        Fight();
    elseif(_state == "Slow") then
        Slow();
    else
        _state = "Idle";
        Idle();
    end

    return _state, animation, fowardMovement, rightMovement, rotation, _wanderPosX, _wanderPosY, _wanderPosZ, _eventReceived;
end

function Idle()
    animation = 14;
    ClearWanderPos()

    rotation = 0;
    fowardMovement = 0;
    rightMovement = 0;

    if(_timerCurrentTime - _randomTimer > 0.5 and _timerCurrentTime - _lastStateChange > 5.0) then
        _randomTimer = _timerCurrentTime;

        if(math.random(1, 100) < 10) then
            _state = "Wander";
            RandomWanderPos()
        end
    end

    if(_targetDistance <= agroDistance) then
        _state = "Seek";
    end
end

function Wander()
    animation = 7;  

    if(_wanderPosX == -1 and _wanderPosY == -1 and _wanderPosZ == -1) then
        RandomWanderPos()
    end

    rotation = _nodeRotationReverse * rotationSpeed * _timerDeltaS;
    fowardMovement = -(movementSpeed * _timerDeltaS);
    rightMovement = 0;

    if(_timerCurrentTime - _randomTimer > 0.5 and _timerCurrentTime - _lastStateChange > 5.0) then
        _randomTimer = _timerCurrentTime;

        if(math.random(1, 100) < 10) then
            --_state = "Idle"; --Enable this to make spider randomly stop
        end
    end

    if(_nodeDistance < 100) then
        _state = "Idle";
    end

    if(_targetDistance <= agroDistance) then
        _state = "Seek";
    end
end

function Seek()
    animation = 7;
    ClearWanderPos()

    if(_targetDistance <= attackDistance + 200) then
        rotation = _targetRotationReverse * rotationSpeed * _timerDeltaS;
        fowardMovement = -(movementSpeed * _timerDeltaS);
        rightMovement = 0;
    else
        rotation = _nodeRotationReverse * rotationSpeed * _timerDeltaS;
        fowardMovement = -(movementSpeed * _timerDeltaS);
        rightMovement = 0;
    end

    if(_targetDistance >= maxFollowDistance and _eventReceived == false) then
        _state = "Wander";
    end

    if(_targetDistance <= attackDistance) then
        _state = "Fight";
        if(_eventReceived == true) then
            Fight()
        end
    end
end

function Fight()
    animation = 0;
    ClearWanderPos()
    if(_eventReceived == true) then
        _eventReceived = false;
    end

    rotation = _targetRotationReverse * rotationSpeed * _timerDeltaS;
    fowardMovement = 0;
    rightMovement = 0;

    if(_targetDistance > attackDistance) then
        _state = "Seek";
    end
end

function Slow()
    animation = 14;
    ClearWanderPos()

    rotation = _targetRotationReverse * rotationSpeed * _timerDeltaS;
    fowardMovement = 0;
    rightMovement = 0;
end