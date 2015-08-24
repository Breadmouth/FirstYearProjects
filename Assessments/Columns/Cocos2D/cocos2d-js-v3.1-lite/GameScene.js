function GameScene()
{
    fallSpeed = 1;
    matchCount = 0;
    
    //used in place of a 2d array (simply because I didn't know how to make a 2d array at the time)
    grid =
    {
        c1:[],
        c2:[],
        c3:[],
        c4:[],
        c5:[],
        c6:[],
        c7:[]
    };  
    
    //array containing the blocks currently falling from the top of screen
    totem = [];
    //array containing the next set of blocks to fall
    nextTotem = [];
    
    clock = 0; 
    
    this.onEnter = function()
    {
        this._super();
        
        //background music
        cc.audioEngine.playMusic(bgMusic, true);
        cc.audioEngine.setMusicVolume(0.1);
        
    };
    this.init = function()
    {
        //init code here
    };
    this.update = function()
    {
        //update code here   
        if (matchCount > 5 && fallSpeed > 0.3)
        {
            matchCount = 0;
            fallSpeed -= 0.1;
            Score.scoreMultiplier++;
        }
        
        endFrameMillis = startFrameMillis;
        startFrameMillis = Date.now();
        dt = (startFrameMillis - endFrameMillis) / 1000;
        
        clock += dt;
        if (clock > fallSpeed)
        {
            //move blocks down
            GameScene.moveTotem(this);
            //check for colour matches
            GameScene.checkMatches();
            clock = 0;
        }
        //clear and refill the grid
        GameScene.updateGrid();
        //update blocks that need to fall down a space
        GameScene.updateBlocks(dt);  

        //get keyboard and touch input
        GameScene.getInput();  
        
        //update Input
        Input.update();
        //update Score
        Score.update();
        
        //Remove blocks that have been marked for delete
        GameScene.removeBlocks(this, dt);
    };
}

//simplifies creating a new GameScene
GameScene.create = function()
{
    if(GameScene.Extended === undefined)
    {
        GameScene.Extended = cc.Scene.extend(new GameScene);
    }
    return new GameScene.Extended();
};

//the base class for Blocks
function BaseBlock()
{
    //colour of the block, to be used for matching purposes
    this.colour = "";
    
    //texture of the block
    this.sprite = cc.Sprite.create(block);
    
    //set the block to alive
    this.sprite.alive = true;
    
    //blocks draw from the bottom left to simplify positions
    this.sprite.setAnchorPoint(new cc.Point(0,0));
    
    //inceasing the texture size from 1px to 100px
    this.sprite.setScale(100);
    
    //falling var determines whether the block is currently falling or if it is 
    //stationary
    this.falling = true;
    
    //states that the current block is a part of the totem
    this.totem = true;
    
    //timer for the breaking animation
    this.animTime = fallSpeed - 0.1;
}

//clears the grid and resets all important variables
GameScene.clearGrid = function()
{ 
    //reset all the variables
    grid.c1 = [];
    grid.c2 = [];
    grid.c3 = [];
    grid.c4 = [];
    grid.c5 = [];
    grid.c6 = [];
    grid.c7 = [];

    totem = [];
    nextTotem = [];
    
    fallSpeed = 1;
    matchCount = 0;
    
    clock = 0;
    
    cc.audioEngine.stopMusic();
    
    //Score.resetScore();
};

//moves the column/totem according to keyboard or touch input
GameScene.getInput = function()
{
    if (totem[2] !== undefined)
    {
        //find which column the totem is in and determine what toems are to the 
        //left or right of it
        var left;
        var right;
        if (totem[2].sprite.getPositionX() === 0)
        {
            left = undefined;
            right = grid.c2;
        }
        else if (totem[2].sprite.getPositionX() === 100)
        {
            left = grid.c1;
            right = grid.c3;
        }
        else if (totem[2].sprite.getPositionX() === 200)
        {
            left = grid.c2;
            right = grid.c4;
        }
        else if (totem[2].sprite.getPositionX() === 300)
        {
            left = grid.c3;
            right = grid.c5;
        }
        else if (totem[2].sprite.getPositionX() === 400)
        {
            left = grid.c4;
            right = grid.c6;
        }
        else if (totem[2].sprite.getPositionX() === 500)
        {
            left = grid.c5;
            right = grid.c7;
        }
        else if (totem[2].sprite.getPositionX() === 600)
        {
            left = grid.c6;
            right = undefined;
        }

        //check for upward swipe
        if (Input.getSwipe() === SwipeDirection.UP && Input.justTouched === true)
        {
            //rotate the blocks upwards
            var temp = totem[0];
            totem[0] = totem[1];
            totem[0].sprite.setPositionY(totem[0].sprite.getPositionY() + 100);
            totem[1] = totem[2];
            totem[1].sprite.setPositionY(totem[1].sprite.getPositionY() + 100);
            totem[2] = temp;
            totem[2].sprite.setPositionY(totem[2].sprite.getPositionY() - 200);
            cc.audioEngine.playEffect(swipe, false);
            Input.justTouched = false;
        }
        //check for downwardward swipe
        else if (Input.getSwipe() === SwipeDirection.DOWN && Input.justTouched === true)
        {
            //rotate the blocks downward
            var temp = totem[0];
            totem[0] = totem[2];
            totem[0].sprite.setPositionY(totem[0].sprite.getPositionY() + 200);
            totem[2] = totem[1];
            totem[2].sprite.setPositionY(totem[2].sprite.getPositionY() - 100);
            totem[1] = temp;
            totem[1].sprite.setPositionY(totem[1].sprite.getPositionY() - 100);
            cc.audioEngine.playEffect(swipe, false);
            Input.justTouched = false;
        }
        //check for leftward swipe
        else if (Input.getSwipe() === SwipeDirection.LEFT && Input.justTouched === true)
        {
            //move the totem to the left
            if (totem[2].sprite.getPositionX() !== 0 && left !== undefined &&
                left[totem[2].sprite.getPositionY() / 100] === undefined)
            {
                totem[0].sprite.setPositionX(totem[0].sprite.getPositionX() - 100);
                totem[1].sprite.setPositionX(totem[1].sprite.getPositionX() - 100);
                totem[2].sprite.setPositionX(totem[2].sprite.getPositionX() - 100);
            }
            Input.justTouched = false;
        }
        //check for rightward swipe
        else if (Input.getSwipe() === SwipeDirection.RIGHT && Input.justTouched === true)
        {
            //move the totem to the right
            if (totem[2].sprite.getPositionX() !== 600 && right !== undefined &&
                right[totem[2].sprite.getPositionY() / 100] === undefined)
            {
                totem[0].sprite.setPositionX(totem[0].sprite.getPositionX() + 100);
                totem[1].sprite.setPositionX(totem[1].sprite.getPositionX() + 100);
                totem[2].sprite.setPositionX(totem[2].sprite.getPositionX() + 100);
            }
            Input.justTouched = false;
        }
        //check for a tap and disregard it
        else if (Input.getSwipe() === SwipeDirection.TAP && Input.justTouched === true)
        {
            Input.justTouched = false;
        }

        //if up key is pressed
        if (Input.getKey(Keys.W) === KeyState.PRESSED)
        {
            //rotate the blocks upwards
            var temp = totem[0];
            totem[0] = totem[1];
            totem[0].sprite.setPositionY(totem[0].sprite.getPositionY() + 100);
            totem[1] = totem[2];
            totem[1].sprite.setPositionY(totem[1].sprite.getPositionY() + 100);
            totem[2] = temp;
            totem[2].sprite.setPositionY(totem[2].sprite.getPositionY() - 200);
            cc.audioEngine.playEffect(swipe, false);
        }
        //if down key is pressed
        else if (Input.getKey(Keys.S) === KeyState.PRESSED)
        {
            //rotate the blocks downward
            var temp = totem[0];
            totem[0] = totem[2];
            totem[0].sprite.setPositionY(totem[0].sprite.getPositionY() + 200);
            totem[2] = totem[1];
            totem[2].sprite.setPositionY(totem[2].sprite.getPositionY() - 100);
            totem[1] = temp;
            totem[1].sprite.setPositionY(totem[1].sprite.getPositionY() - 100);
            cc.audioEngine.playEffect(swipe, false);
        }
        //if left key pressed
        else if (Input.getKey(Keys.A) === KeyState.PRESSED)
        {
            //move the totem to the left
            if (totem[2].sprite.getPositionX() !== 0 && left !== undefined &&
                left[totem[2].sprite.getPositionY() / 100] === undefined)
            {
                totem[0].sprite.setPositionX(totem[0].sprite.getPositionX() - 100);
                totem[1].sprite.setPositionX(totem[1].sprite.getPositionX() - 100);
                totem[2].sprite.setPositionX(totem[2].sprite.getPositionX() - 100);
            }
        }
        //if right key pressed
        else if (Input.getKey(Keys.D) === KeyState.PRESSED)
        {
            //move the totem to the right
            if (totem[2].sprite.getPositionX() !== 600 && right !== undefined &&
                right[totem[2].sprite.getPositionY() / 100] === undefined)
            {
                totem[0].sprite.setPositionX(totem[0].sprite.getPositionX() + 100);
                totem[1].sprite.setPositionX(totem[1].sprite.getPositionX() + 100);
                totem[2].sprite.setPositionX(totem[2].sprite.getPositionX() + 100);
            }
        }
    }
};

//loops through the grid removing blocks that have fallen down a space
GameScene.updateGrid = function()
{
    //clear the grid
    //
    //loop throught the first column removing blocks that have fallen down a 
    //space (totem blocks)
    for (j = grid.c1.length - 1; j >= 0; j--)
    {
        if (grid.c1[j] !== undefined && grid.c1[j].falling === true)
            grid.c1.pop();
    }
    //loop throught the second column removing blocks that have fallen down a 
    //space (totem blocks)   
    for (j = grid.c2.length - 1; j >= 0; j--)
    {
        if (grid.c2[j] !== undefined && grid.c2[j].falling === true)
            grid.c2.pop();
    }
    //loop throught the third column removing blocks that have fallen down a 
    //space (totem blocks)
    for (j = grid.c3.length - 1; j >= 0; j--)
    {
        if (grid.c3[j] !== undefined && grid.c3[j].falling === true)
            grid.c3.pop();
    }
    //loop throught the fourth column removing blocks that have fallen down a 
    //space (totem blocks)
    for (j = grid.c4.length - 1; j >= 0; j--)
    {
        if (grid.c4[j] !== undefined && grid.c4[j].falling === true)
            grid.c4.pop();
    }
    //loop throught the fifth column removing blocks that have fallen down a 
    //space (totem blocks)
    for (j = grid.c5.length - 1; j >= 0; j--)
    {
        if (grid.c5[j] !== undefined && grid.c5[j].falling === true)
            grid.c5.pop();
    }
    //loop throught the sixth column removing blocks that have fallen down a 
    //space (totem blocks)
    for (j = grid.c6.length - 1; j >= 0; j--)
    {
        if (grid.c6[j] !== undefined && grid.c6[j].falling === true)
            grid.c6.pop();
    }
    //loop throught the seventh column removing blocks that have fallen down a 
    //space (totem blocks)
    for (j = grid.c7.length - 1; j >= 0; j--)
    {
        if (grid.c7[j] !== undefined && grid.c7[j].falling === true)
            grid.c7.pop();
    }

    //refill the grid 
    
    //check if a new totem exists
    if (totem.length > 0)
    {
        //loop through the totem blocks
        for (i = 0; i < 3; i++)
        {
            //if totem block is in first column...
            if (totem[i].sprite.getPositionX() === 0)
            {
                //add totem to the grid in the first column
                grid.c1[totem[i].sprite.getPositionY() / 100] = totem[i];
            }
            //if totem block is in second column...
            else if(totem[i].sprite.getPositionX() === 100)
            {
                //add totem to the grid in the second column
                grid.c2[totem[i].sprite.getPositionY() / 100] = totem[i];
            }
            //if totem block is in third column...
            else if(totem[i].sprite.getPositionX() === 200)
            {
                //add totem to the grid in the third column
                grid.c3[totem[i].sprite.getPositionY() / 100] = totem[i];
            }
            //if totem block is in fourth column...
            else if(totem[i].sprite.getPositionX() === 300)
            {
                //add totem to the grid in the fourth column
                grid.c4[totem[i].sprite.getPositionY() / 100] = totem[i];
            }
            //if totem block is in fifth column...
            else if(totem[i].sprite.getPositionX() === 400)
            {
                //add totem to the grid in the fifth column
                grid.c5[totem[i].sprite.getPositionY() / 100] = totem[i];
            }
            //if totem block is in sixth column...
            else if(totem[i].sprite.getPositionX() === 500)
            {
                //add totem to the grid in the sixth column
                grid.c6[totem[i].sprite.getPositionY() / 100] = totem[i];
            }
            //if totem block is in seventh column...
            else if(totem[i].sprite.getPositionX() === 600)
            {
                //add totem to the grid in the seventh column
                grid.c7[totem[i].sprite.getPositionY() / 100] = totem[i];
            }
        }
    }
};

//moves the column/totem down a space
GameScene.moveTotem = function(scene)
{
    //if a totem exists...
    if (totem.length > 0)
    {
        //check which column the totem is in
        var temp;
        if (totem[2].sprite.getPositionX() === 0)
        {
            temp = grid.c1;
        }
        else if (totem[2].sprite.getPositionX() === 100)
        {
            temp = grid.c2;
        }
        else if (totem[2].sprite.getPositionX() === 200)
        {
            temp = grid.c3;
        }
        else if (totem[2].sprite.getPositionX() === 300)
        {
            temp = grid.c4;
        }
        else if (totem[2].sprite.getPositionX() === 400)
        {
            temp = grid.c5;
        }
        else if (totem[2].sprite.getPositionX() === 500)
        {
            temp = grid.c6;
        }
        else if (totem[2].sprite.getPositionX() === 600)
        {
            temp = grid.c7;
        }
        
        //check if there is room below the totem to fall
        if (totem[2].sprite.getPositionY() !== 0 &&
            temp[(totem[2].sprite.getPositionY() / 100) - 1] === undefined)
        {
            totem[0].sprite.setPositionY(totem[0].sprite.getPositionY() - 100);
            totem[1].sprite.setPositionY(totem[1].sprite.getPositionY() - 100);
            totem[2].sprite.setPositionY(totem[2].sprite.getPositionY() - 100);
            if (totem[2].sprite.getPositionY() === 0 || 
                temp[(totem[2].sprite.getPositionY() / 100) - 1] !== undefined)
            {
                cc.audioEngine.playEffect(thud, false);
            }
        }
        //the totem has landed, set the blocks to stationary and create a new totem
        else if (totem[2].sprite.getPositionY() > 800)
        {
            GameScene.clearGrid();
            totem = [];
            
            var newScene = GOScene.create();
            newScene.scheduleUpdate();
            cc.director.runScene(newScene);
        }
        else
        {
            //set the totem to landed and create a new totem
            totem[0].falling = false;
            totem[1].falling = false;
            totem[2].falling = false;
            totem[0].totem = false;
            totem[1].totem = false;
            totem[2].totem = false;
            totem.pop();
            totem.pop();
            totem.pop();
            GameScene.createTotem(scene);
        }
    }
    //create a totem
    else
    {
        GameScene.createTotem(scene);
    }
};

//loops through all blocks that aren't in the totem and moves them down a space
//if there is room to fall into
 GameScene.updateBlocks = function(dt)
 {
    for (j = 0; j < 7; j++)
    {
        switch (j)
        {
            case 0:
                //for every block in the column
                for (i = grid.c1.length - 1; i >= 0; i--)
                {
                    //if the block exists and isnt part of the totem
                    if (grid.c1[i] !== undefined && grid.c1[i].totem === false)
                    {
                        //if the block is dead and still animating 
                        if (grid.c1[i].sprite.alive !== true && grid.c1[i].animTime > 0)
                        {
                            //turn the block purple to signify a match
                            grid.c1[i].animTime -= dt;
                            grid.c1[i].sprite.setColor(cc.color(255,0,255,255));
                        }
                        //if there is room to fall into
                        if (grid.c1[i].sprite.getPositionY() !== 0 &&
                            grid.c1[i - 1] === undefined)
                        {
                            //move the b lock down a spot
                            grid.c1[i].falling = true;
                            grid.c1[i - 1] = grid.c1[i];
                            grid.c1[i - 1].sprite.setPositionY(grid.c1[i - 1].sprite.getPositionY() - 100);
                            grid.c1[i] = undefined;
                            if (grid.c1[i - 1].sprite.getPositionY() === 0 ||
                                grid.c1[i - 1] !== undefined)
                            {
                                cc.audioEngine.playEffect(thud, false);
                            }
                        }
                        //the block has landed
                        else
                        {
                            grid.c1[i].falling = false;
                        }
                     }
                }
                break;
            case 1:
                for (i = grid.c2.length - 1; i >= 0; i--)
                {
                     if (grid.c2[i] !== undefined && grid.c2[i].totem === false)
                     {
                         if (grid.c2[i].sprite.alive !== true && grid.c2[i].animTime > 0)
                        {
                            grid.c2[i].animTime -= dt;
                            grid.c2[i].sprite.setColor(cc.color(255,0,255, 255));
                        }
                        if (grid.c2[i].sprite.getPositionY() !== 0 &&
                            grid.c2[i - 1] === undefined)
                        {
                            grid.c2[i].falling = true;
                            grid.c2[i - 1] = grid.c2[i];
                            grid.c2[i - 1].sprite.setPositionY(grid.c2[i - 1].sprite.getPositionY() - 100);
                            grid.c2[i] = undefined;
                            if (grid.c2[i - 1].sprite.getPositionY() === 0 ||
                                grid.c2[i - 1] !== undefined)
                            {
                                cc.audioEngine.playEffect(thud, false);
                            }
                        }
                        //the block has landed
                        else
                        {
                            grid.c2[i].falling = false;
                        }
                     }
                }                
                break;
            case 2:
                for (i = grid.c3.length - 1; i >= 0; i--)
                {
                     if (grid.c3[i] !== undefined && grid.c3[i].totem === false)
                     {
                         if (grid.c3[i].sprite.alive !== true && grid.c3[i].animTime > 0)
                        {
                            grid.c3[i].animTime -= dt;
                            grid.c3[i].sprite.setColor(cc.color(255,0,255, 255));
                        }
                         if (grid.c3[i].sprite.getPositionY() !== 0 &&
                            grid.c3[i - 1] === undefined)
                        {
                            grid.c3[i].falling = true;
                            grid.c3[i - 1] = grid.c3[i];
                            grid.c3[i - 1].sprite.setPositionY(grid.c3[i - 1].sprite.getPositionY() - 100);
                            grid.c3[i] = undefined;
                            if (grid.c3[i - 1].sprite.getPositionY() === 0 ||
                                grid.c3[i - 1] !== undefined)
                            {
                                cc.audioEngine.playEffect(thud, false);
                            }
                        }
                        //the block has landed
                        else
                        {
                            grid.c3[i].falling = false;   
                        }
                     }
                }  
                break;
            case 3:
                for (i = grid.c4.length - 1; i >= 0; i--)
                {
                     if (grid.c4[i] !== undefined && grid.c4[i].totem === false)
                     {
                         if (grid.c4[i].sprite.alive !== true && grid.c4[i].animTime > 0)
                        {
                            grid.c4[i].animTime -= dt;
                            grid.c4[i].sprite.setColor(cc.color(255,0,255, 255));
                        }
                        if (grid.c4[i].sprite.getPositionY() !== 0 &&
                            grid.c4[i - 1] === undefined)
                        {
                            grid.c4[i].falling = true;
                            grid.c4[i - 1] = grid.c4[i];
                            grid.c4[i - 1].sprite.setPositionY(grid.c4[i - 1].sprite.getPositionY() - 100);
                            grid.c4[i] = undefined;
                            if (grid.c4[i - 1].sprite.getPositionY() === 0 ||
                                grid.c4[i - 1] !== undefined)
                            {
                                cc.audioEngine.playEffect(thud, false);
                            }
                        }
                        //the block has landed
                        else
                        {
                            grid.c4[i].falling = false;
                        }
                     }
                }  
                break;
            case 4:
                for (i = grid.c5.length - 1; i >= 0; i--)
                {
                     if (grid.c5[i] !== undefined && grid.c5[i].totem === false)
                     {
                         if (grid.c5[i].sprite.alive !== true && grid.c5[i].animTime > 0)
                        {
                            grid.c5[i].animTime -= dt;
                            grid.c5[i].sprite.setColor(cc.color(255,0,255, 255));
                        }
                        if (grid.c5[i].sprite.getPositionY() !== 0 &&
                            grid.c5[i - 1] === undefined)
                        {
                            grid.c5[i].falling = true;
                            grid.c5[i - 1] = grid.c5[i];
                            grid.c5[i - 1].sprite.setPositionY(grid.c5[i - 1].sprite.getPositionY() - 100);
                            grid.c5[i] = undefined;
                            if (grid.c5[i - 1].sprite.getPositionY() === 0 ||
                                grid.c5[i - 1] !== undefined)
                            {
                                cc.audioEngine.playEffect(thud, false);
                            }
                        }
                        //the block has landed
                        else
                        {
                            grid.c5[i].falling = false;
                        }
                     }
                }  
                break;
            case 5:
                for (i = grid.c6.length - 1; i >= 0; i--)
                {
                     if (grid.c6[i] !== undefined && grid.c6[i].totem === false)
                     {
                         if (grid.c6[i].sprite.alive !== true && grid.c6[i].animTime > 0)
                        {
                            grid.c6[i].animTime -= dt;
                            grid.c6[i].sprite.setColor(cc.color(255,0,255, 255));
                        }
                        if (grid.c6[i].sprite.getPositionY() !== 0 &&
                            grid.c6[i - 1] === undefined)
                        {
                            grid.c6[i].falling = true;
                            grid.c6[i - 1] = grid.c6[i];
                            grid.c6[i - 1].sprite.setPositionY(grid.c6[i - 1].sprite.getPositionY() - 100);
                            grid.c6[i] = undefined;
                            if (grid.c6[i - 1].sprite.getPositionY() === 0 ||
                                grid.c6[i - 1] !== undefined)
                            {
                                cc.audioEngine.playEffect(thud, false);
                            }
                        }
                        //the block has landed
                        else
                        {
                            grid.c6[i].falling = false;
                        }
                     }
                }  
                break;
            case 6:
                for (i = grid.c7.length - 1; i >= 0; i--)
                {
                     if (grid.c7[i] !== undefined && grid.c7[i].totem === false)
                     {
                         if (grid.c7[i].sprite.alive !== true && grid.c7[i].animTime > 0)
                        {
                            grid.c7[i].animTime -= dt;
                            grid.c7[i].sprite.setColor(cc.color(255,0,255, 255));
                        }
                        if (grid.c7[i].sprite.getPositionY() !== 0 &&
                            grid.c7[i - 1] === undefined)
                        {
                            grid.c7[i].falling = true;
                            grid.c7[i - 1] = grid.c7[i];
                            grid.c7[i - 1].sprite.setPositionY(grid.c7[i].sprite.getPositionY() - 100);
                            grid.c7[i] = undefined;
                            if (grid.c7[i - 1].sprite.getPositionY() === 0 ||
                                grid.c7[i - 1] !== undefined)
                            {
                                cc.audioEngine.playEffect(thud, false);
                            }
                        }
                        //the block has landed
                        else
                        {
                            grid.c7[i].falling = false;
                        }
                     }
                }  
                break;
        }
    }
    
    
 };

//checks for matches between all blocks that aren't in the totem
GameScene.checkMatches = function()
{
    //sotr all of the blocks in allBlocks to simplify matching
    var allBlocks = [];
    for (j = 0; j < 7; j++)
    {
        var currentColumn;
        switch (j)
        {
            case 0:
                currentColumn = grid.c1;
                break;
            case 1:
                currentColumn = grid.c2;
                break;
            case 2:
                currentColumn = grid.c3;
                break;
            case 3:
                currentColumn = grid.c4;
                break;
            case 4:
                currentColumn = grid.c5;
                break;
            case 5:
                currentColumn = grid.c6;
                break;
            case 6:
                currentColumn = grid.c7;
                break;
        }
        //add all the block to allBlocks
        for (i = currentColumn.length - 1; i >= 0; i--)
        {
             var currentBlock = currentColumn[i];
             if (currentBlock !== undefined)
             {
                allBlocks[allBlocks.length] = currentBlock;
             }
        }
    }
    
    var currentMatches = [];
    var confirmedMatches = [];
    var direction = undefined;
    var chain = false;
    var tempBlock;

    //recursive function to check close matches
    var checkSurrounds = function(x, array)
    {
        for (y = 0; y < array.length; y++)
        {
            //if a match of at least 2 has already been found then continue
            //looking in the same direction for another match
            if (direction !== undefined && x !== y)
            {
                //check if a match exists in the direction
                var tempDir = cc.p(array[y].sprite.getPositionX() - array[x].sprite.getPositionX(),array[y].sprite.getPositionY() - array[x].sprite.getPositionY());
                if (tempDir.x === direction.x && tempDir.y === direction.y && array[x].colour === array[y].colour &&
                    array[x].falling !== true && array[y].falling !== true)
                {
                    //chain signifies that a match of 3 or more has been made
                    chain = true;
                    //recall the recursive function
                    tempBlock = checkSurrounds(y, array);
                    currentMatches[currentMatches.length] = tempBlock;
                    
                    //return the current block
                    return array[x];
                } 
            }
        }       
        direction = undefined;
        //return the current block
        return array[x];
    };
    
    //check the matches between blocks in allBlocks
    for (i = 0; i < allBlocks.length; i++)
    {
        //call the recursive function for the current block
        for (j = 0; j < allBlocks.length; j++)
        {
            if ((allBlocks[i].sprite.getPositionX() - allBlocks[j].sprite.getPositionX() === -100       ||
                    allBlocks[i].sprite.getPositionX() - allBlocks[j].sprite.getPositionX() === 100     ||
                    allBlocks[i].sprite.getPositionX() - allBlocks[j].sprite.getPositionX() === 0)      &&
                    (allBlocks[i].sprite.getPositionY() - allBlocks[j].sprite.getPositionY() === 100    ||
                    allBlocks[i].sprite.getPositionY() - allBlocks[j].sprite.getPositionY() === -100    ||
                    allBlocks[i].sprite.getPositionY() - allBlocks[j].sprite.getPositionY() === 0)      &&
                    allBlocks[i].colour === allBlocks[j].colour && i !== j &&
                    allBlocks[i].falling !== true && allBlocks[j].falling !== true)
            {
                //set the direction that the match was in
                direction = cc.p(allBlocks[j].sprite.getPositionX() - allBlocks[i].sprite.getPositionX(),
                                 allBlocks[j].sprite.getPositionY() - allBlocks[i].sprite.getPositionY());
                
                currentMatches[currentMatches.length] = allBlocks[i];
                
                chain = false;
                
                //recall the recursive function and add the result in the current matches array
                tempBlock = checkSurrounds(j, allBlocks);
                currentMatches[currentMatches.length] = tempBlock;
                
                //reset the direction
                direction = undefined;
            }
            //if no match of 3 was made for this block...
            if (chain === false)
            {
                //remove all the blocks from the current matches array
                for (k = currentMatches.length - 1; k >= 0; k--)
                {
                    currentMatches.pop();
                }
            }
            //else pushh all the blocks in currentmatches into confirmedMatches
            for (k = 0; k < currentMatches.length; k++)
            {
                confirmedMatches.push(currentMatches[k]);
            }
            chain = false;

            }
    }
    
    var tempScoreMult = 0;
    
    //loop through the confirmed matches increasing the score and marking matched blocks as dead
    if (confirmedMatches.length > 2)
    {
        for (i = 0; i < confirmedMatches.length; i++)
        {
            if (confirmedMatches[i] !== 0 && confirmedMatches[i] !== undefined && 
                confirmedMatches[i].sprite.alive !== false)
            {
                confirmedMatches[i].sprite.alive = false;
                matchCount++;
                tempScoreMult++;
            }
        }
        Score.addScore(tempScoreMult);
        cc.audioEngine.playEffect(yay, false);
    }
};

//sets the current totem to next totem, then creates a new next totem
GameScene.createTotem = function(scene)
{ 
    if (nextTotem.length > 0)
    {
        totem[0] = nextTotem[0];
        totem[1] = nextTotem[1];
        totem[2] = nextTotem[2];

        totem[0].sprite.setPosition(300, 1100);
        totem[1].sprite.setPosition(300, 1000);
        totem[2].sprite.setPosition(300, 900);
    }
    //add a new block to the nexttotem
    nextTotem[0] = new BaseBlock();
    //give the block a random colour
    var x = Math.floor((Math.random() * 5) + 1);
    if (x === 1)
    {
        nextTotem[0].colour = "green";
        nextTotem[0].sprite.setColor(cc.color(0,255,0,255));
    }
    else if (x === 2)
    {
        nextTotem[0].colour = "red";
        nextTotem[0].sprite.setColor(cc.color(255,0,0,255));
    }
    else if (x === 3)
    {
        nextTotem[0].colour = "blue";
        nextTotem[0].sprite.setColor(cc.color(0,0,255,255));
    }
    else if (x === 4)
    {
        nextTotem[0].colour = "white";
        nextTotem[0].sprite.setColor(cc.color(255,255,255,255));
    }
    else
    {
        nextTotem[0].colour = "yellow";
        nextTotem[0].sprite.setColor(cc.color(255,255,0,255));
    }
    nextTotem[0].sprite.setPosition(800,800);

    //add a new block to the nexttotem
    nextTotem[1] = new BaseBlock();
    //give the block a random colour
    var x = Math.floor((Math.random() * 5) + 1);
    if (x === 1)
    {
        nextTotem[1].colour = "green";
        nextTotem[1].sprite.setColor(cc.color(0,255,0,255));
    }
    else if (x === 2)
    {
        nextTotem[1].colour = "red";
        nextTotem[1].sprite.setColor(cc.color(255,0,0,255));
    }
    else if (x === 3)
    {
        nextTotem[1].colour = "blue";
        nextTotem[1].sprite.setColor(cc.color(0,0,255,255));
    }
    else if (x === 4)
    {
        nextTotem[1].colour = "white";
        nextTotem[1].sprite.setColor(cc.color(255,255,255,255));
    }
    else
    {
        nextTotem[1].colour = "yellow";
        nextTotem[1].sprite.setColor(cc.color(255,255,0,255));
    }
    nextTotem[1].sprite.setPosition(800,700);

    //add a new block to the nextTotem
    nextTotem[2] = new BaseBlock();
    //give the block a random colour
    var x = Math.floor((Math.random() * 5) + 1);
    if (x === 1)
    {
        nextTotem[2].colour = "green";
        nextTotem[2].sprite.setColor(cc.color(0,255,0,255));
    }
    else if (x === 2)
    {
        nextTotem[2].colour = "red";
        nextTotem[2].sprite.setColor(cc.color(255,0,0,255));
    }
    else if (x === 3)
    {
        nextTotem[2].colour = "blue";
        nextTotem[2].sprite.setColor(cc.color(0,0,255,255));
    }
    else if (x === 4)
    {
        nextTotem[2].colour = "white";
        nextTotem[2].sprite.setColor(cc.color(255,255,255,255));
    }
    else
    {
        nextTotem[2].colour = "yellow";
        nextTotem[2].sprite.setColor(cc.color(255,255,0,255));
    }
    nextTotem[2].sprite.setPosition(800,600);

    //add he nextTotem to the grid
    if (totem.length > 0)
    {
        grid.c4[11] = totem[2];
        grid.c4[10] = totem[1];
        grid.c4[9] = totem[0];
    }

    //add the blocks to the scene to be drawn
    for(var block in nextTotem)
    {
        scene.addChild(nextTotem[block].sprite, 0);
    }
};
    
//loops through all blocks removing any that have been flagged for delete
GameScene.removeBlocks = function(scene)
{ 
    for (j = 0; j < 7; j++)
    {
        switch (j)
        {
            case 0:
                //loop through all the blocks in the column removing any blocks that are marked for delete
                for (i = grid.c1.length - 1; i >= 0; i--)
                {
                     if (grid.c1[i] !== undefined && 
                         grid.c1[i].sprite.alive === false &&
                         grid.c1[i].animTime <= 0)
                     {
                         scene.removeChild(grid.c1[i].sprite);
                        grid.c1[i] = undefined;
                     }
                }
                break;
            case 1:
                for (i = grid.c2.length - 1; i >= 0; i--)
                {
                     if (grid.c2[i] !== undefined && 
                         grid.c2[i].sprite.alive === false
                         && grid.c2[i].animTime <= 0)
                     {
                         scene.removeChild(grid.c2[i].sprite);
                        grid.c2[i] = undefined;
                     }
                }
                break;
            case 2:
                for (i = grid.c3.length - 1; i >= 0; i--)
                {
                     if (grid.c3[i] !== undefined && 
                         grid.c3[i].sprite.alive === false &&
                         grid.c3[i].animTime <= 0)
                     {
                         scene.removeChild(grid.c3[i].sprite);
                        grid.c3[i] = undefined;
                     }
                }
                break;
            case 3:
                for (i = grid.c4.length - 1; i >= 0; i--)
                {
                     if (grid.c4[i] !== undefined && 
                         grid.c4[i].sprite.alive === false &&
                         grid.c4[i].animTime <= 0)
                     {
                         scene.removeChild(grid.c4[i].sprite);
                        grid.c4[i] = undefined;
                     }
                }
                break;
            case 4:
                for (i = grid.c5.length - 1; i >= 0; i--)
                {
                     if (grid.c5[i] !== undefined && 
                         grid.c5[i].sprite.alive === false &&
                         grid.c5[i].animTime <= 0)
                     {
                         scene.removeChild(grid.c5[i].sprite);
                        grid.c5[i] = undefined;
                     }
                }
                break;
            case 5:
                for (i = grid.c6.length - 1; i >= 0; i--)
                {
                     if (grid.c6[i] !== undefined && 
                         grid.c6[i].sprite.alive === false &&
                         grid.c6[i].animTime <= 0)
                     {
                         scene.removeChild(grid.c6[i].sprite);
                        grid.c6[i] = undefined;
                     }
                }
                break;
            case 6:
                for (i = grid.c7.length - 1; i >= 0; i--)
                {
                     if (grid.c7[i] !== undefined && 
                         grid.c7[i].sprite.alive === false &&
                         grid.c7[i].animTime <= 0)
                     {
                         scene.removeChild(grid.c7[i].sprite);
                        grid.c7[i] = undefined;
                     }
                }
                break;
        }
    }

};