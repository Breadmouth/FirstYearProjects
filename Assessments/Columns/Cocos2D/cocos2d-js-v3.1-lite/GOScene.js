function GOScene()
{
    //function runs on creation of GOScene
    this.onEnter = function()
    {
        this._super();
        
        //timer that counts down until next scene change
        this.timer = 0;
        
        //size of the window to help with positioning the sprite
        this.size = cc.director.getWinSize();
        //the game over image
        this.sprite = cc.Sprite.create(gameOver);
        this.sprite.setPosition(this.size.width / 2, this.size.height / 2);
        
        this.addChild(this.sprite, 0);
    };
    this.init = function()
    {
        //init code here
    };
    //update code goes here
    this.update = function()
    {
        //keeping delta time  
        endFrameMillis = startFrameMillis;
        startFrameMillis = Date.now();
        dt = (startFrameMillis - endFrameMillis) / 1000;
        
        //increasing the timer by dt
        this.timer += dt;
        
        //change the scene
        if (this.timer > 2)
        {
            var newScene = HSScene.create();
            newScene.scheduleUpdate();
            cc.director.runScene(newScene);
        }
    };
}

//Simplifies creating a new GOScene
GOScene.create = function()
{
    //extend the GameOver scene from Scene
    if(GOScene.Extended === undefined)
    {
        GOScene.Extended = cc.Scene.extend(new GOScene);
    }
    return new GOScene.Extended();
};

