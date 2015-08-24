function MenuScene()
{   
    this.onEnter = function()
    {
        this._super();
        
        MenuScene.size = cc.director.getWinSize();
        
        //create the title for the MenuScene
        var title = cc.LabelTTF.create("TOTEMS", font, 80);
        title.setPosition(new cc.Point(MenuScene.size.width / 2, MenuScene.size.height / 2 + 140));
        //create 'play' and 'high scores' buttons
        MenuScene.buttonPlay = new cc.MenuItemFont.create("Play", MenuScene.playScene);
        MenuScene.buttonPlay.setPosition(new cc.Point(MenuScene.buttonPlay.getPositionX(),MenuScene.buttonPlay.getPositionY() + 60));
        MenuScene.buttonScores = new cc.MenuItemFont.create("High Scores", MenuScene.scoreScene);

        var menu = cc.Menu.create(MenuScene.buttonPlay, MenuScene.buttonScores);
        
        //add the buttons as children to the scene
        this.addChild(title);
        this.addChild(menu);
        
    };
    this.init = function()
    {
        //init code here
    };
    this.update = function()
    {
        //update code here    
        endFrameMillis = startFrameMillis;
        startFrameMillis = Date.now();
        dt = (startFrameMillis - endFrameMillis) / 1000;

        MenuScene.getInput();
    };
}

//(as touches don't work with menu items) allow touches to work with the menu items
MenuScene.getInput = function()
{
    //ignore all inputs except for taps
    if (Input.getSwipe() === SwipeDirection.UP && Input.justTouched === true)
    {
        Input.justTouched = false;
    }
    if (Input.getSwipe() === SwipeDirection.RIGHT && Input.justTouched === true)
    {
        Input.justTouched = false;
    }
    if (Input.getSwipe() === SwipeDirection.DOWN && Input.justTouched === true)
    {
        Input.justTouched = false;
    }
    if (Input.getSwipe() === SwipeDirection.LEFT && Input.justTouched === true)
    {
        Input.justTouched = false;
    }
    
    if (Input.getSwipe() === SwipeDirection.TAP && Input.justTouched === true)
    {
        //the buttons aren't reacting to touch input, so this will do for now
        
        //if user taps on the button, run the buttons callBack (play game)
        if (Input.beginPoint.x < (MenuScene.size.width / 2) + 160 &&
            Input.beginPoint.x > (MenuScene.size.width / 2) + 70 &&
            Input.beginPoint.y < (MenuScene.size.height / 2) - 20 &&
            Input.beginPoint.y > (MenuScene.size.height / 2) - 60)
        {
            Input.justTouched = false;
            MenuScene.buttonPlay._callback();
        }
    }
    
    if (Input.getSwipe() === SwipeDirection.TAP && Input.justTouched === true)
    {
        //if user taps on the button, run the buttons callBack (show highscores)
        if (Input.beginPoint.x < (MenuScene.size.width / 2) + 210 &&
            Input.beginPoint.x > (MenuScene.size.width / 2) + 20 &&
            Input.beginPoint.y < (MenuScene.size.height / 2) + 40 &&
            Input.beginPoint.y > (MenuScene.size.height / 2) + 0)
        {
            Input.justTouched = false;
            MenuScene.buttonScores._callback();
        }
    }
};

//simplifies creating a MenuScene
MenuScene.create = function()
{
    if(MenuScene.Extended === undefined)
    {
        MenuScene.Extended = cc.Scene.extend(new MenuScene);
    }
    return new MenuScene.Extended();
};

//sets the new scene to PlayScene
MenuScene.playScene = function()
{
    //run the GameScene
    var newScene = GameScene.create();
    newScene.scheduleUpdate();
    cc.director.runScene(newScene); //no screen transitions in the lite version
};

//sets the new scene to the HighScores scene
MenuScene.scoreScene = function()
{
    //run the HSScene
    var newScene = HSScene.create();
    newScene.scheduleUpdate();
    cc.director.runScene(newScene);
};