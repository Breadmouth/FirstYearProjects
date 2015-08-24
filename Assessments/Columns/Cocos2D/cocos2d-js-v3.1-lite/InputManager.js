var Keys = 
{
     W : 87,
     S : 83,
     A : 65,
     D : 68          
};

//possible states for keys
var KeyState = 
{
    UP          : 0,
    DOWN        : 1,
    PRESSED     : 2,
    RELEASED    : 3
};

//possible states for touches
var SwipeDirection =
{
    UP      : 0,
    DOWN    : 1,
    LEFT    : 2,
    RIGHT   : 3,
    TAP     : 4,
    DEFAULT : 5
};

var Input = {};

Input.keyStates = [];
Input.swipeDir;
Input.justTouched = false;

//swipe begin point
Input.beginPoint = {x:0, y:0};
//swipe end point
Input.endPoint = {x:0, y:0};

//set state of current key to pressed
Input.onKeyDown = function(evt)
{
    Input.keyStates[evt.keyCode] = KeyState.PRESSED;
};

//set state of current key to released
Input.onKeyUp = function(evt)
{
    Input.keyStates[evt.keyCode] = KeyState.RELEASED;
};

//set all pressed keys to down, set all released keys to up
Input.update = function()
{
    //for all keys in the keystate array
    for (var i in this.keyStates)
    {
        var s = this.keyStates[i];
        
        if (s === KeyState.PRESSED)
        {
            //if key is pressed set state to down
            this.keyStates[i] = KeyState.DOWN;
        }
        else if (s === KeyState.RELEASED)
        {
            //if key is released set state to up
            this.keyStates[i] = KeyState.UP;
        }
    }
};

//get the canvas and add input event listeners
Input.init = function(elementId/* ,scheduler*/)
{
    var canvas = document.getElementById(elementId);
    if (canvas === null)
    {
        canvas = window;
    }

    //event listeners for keys
    canvas.addEventListener('keydown', function(evt) {Input.onKeyDown(evt);}, false);
    canvas.addEventListener('keyup', function(evt) {Input.onKeyUp(evt);}, false);
    
    //event listeners for touches
    canvas.addEventListener('touchstart', function(evt) {Input.onTouchStart(evt);}, false);
    canvas.addEventListener('touchmove', function(evt) {Input.onTouchMove(evt);}, false);
    canvas.addEventListener('touchend', function(evt) {Input.onTouchEnd(evt);}, false);
    
//    canvas.addEventListener('load', Input.resizeCanvas(), false);
//    canvas.addEventListener('resize', Input.resizeCanvas(), false);
};

//Input.resizeCanvas = function()
//{
//    var size = director.getWinSize();
//    canvas.style.width = size.width * 0.7;
//    canvas.style.height = size.height * 0.7;
//};

//returns the state of the current key
Input.getKey = function(key)
{
    if (Input.keyStates[key] !== undefined)
    {
        //returns the state of the key
        return Input.keyStates[key];
        
    }
    return KeyState.UP;
};

//returns the direction of the latest swipe
Input.getSwipe = function()
{
    //returns the direction/state of the latest swipe
    return Input.swipeDir;
};

//sets the begin point of a swipe
Input.onTouchStart = function(evt)
{
    //prevent default behaviour
    evt.stopPropagation();
    evt.preventDefault();
    //set the begin point of the swipe
    Input.beginPoint.x = evt.changedTouches[0].pageX;
    Input.beginPoint.y = evt.changedTouches[0].pageY;
};

//prevents default behaviour for touch movement
Input.onTouchMove = function(evt)
{
    evt.preventDefault();
};

//sets the end point of a swipe and calculates the swipe direction
Input.onTouchEnd = function(evt)
{
    //prevent default behaviour
    evt.stopPropagation();
    evt.preventDefault();
    //set end point of the swipe
    Input.endPoint.x = evt.changedTouches[0].pageX;
    Input.endPoint.y = evt.changedTouches[0].pageY;
    
    //determine what kind of touch it was
    if (Input.justTouched !== true)
    {
        if (Math.abs(Input.endPoint.x - Input.beginPoint.x) < 50 && Math.abs(Input.endPoint.y - Input.beginPoint.y) < 50)
        {
            Input.swipeDir = SwipeDirection.TAP;
        }
        else if (Math.abs(Input.endPoint.x - Input.beginPoint.x) > Math.abs(Input.endPoint.y - Input.beginPoint.y)
                && (Input.endPoint.x - Input.beginPoint.x) > 0)
        {
            Input.swipeDir = SwipeDirection.RIGHT;
        }
        else if (Math.abs(Input.endPoint.x - Input.beginPoint.x) > Math.abs(Input.endPoint.y - Input.beginPoint.y)
                && (Input.endPoint.x - Input.beginPoint.x) < 0)
        {
            Input.swipeDir = SwipeDirection.LEFT;
        }
        else if (Math.abs(Input.endPoint.x - Input.beginPoint.x) < Math.abs(Input.endPoint.y - Input.beginPoint.y)
                && (Input.endPoint.y - Input.beginPoint.y) > 0)
        {
            Input.swipeDir = SwipeDirection.DOWN;
        }
        else if (Math.abs(Input.endPoint.x - Input.beginPoint.x) < Math.abs(Input.endPoint.y - Input.beginPoint.y)
                && (Input.endPoint.y - Input.beginPoint.y) < 0)
        {
            Input.swipeDir = SwipeDirection.UP;
        }
        else
        {
            Input.swipeDir = SwipeDirection.DEFAULT;
        }

        Input.justTouched = true;
    }
};