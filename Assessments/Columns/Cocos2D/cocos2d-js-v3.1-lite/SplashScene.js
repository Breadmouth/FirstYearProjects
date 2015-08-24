function SplashScene()
{
    this.onEnter = function()
    {
        this._super();
        
        this.timer = 0;
        
        this.size = cc.director.getWinSize();
        //create the splashscreen sprite
        this.sprite = cc.Sprite.create(splashScreen);
        this.sprite.setPosition(this.size.width / 2, this.size.height / 2);
        
        this.addChild(this.sprite, 0);
        
        Score.getWeather();
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
        
        this.timer += dt;
        
        if (this.timer > 2)
        {
            var newScene = MenuScene.create();
            newScene.scheduleUpdate();
            cc.director.runScene(newScene);
        }
    };
}

//simplifies creating a Splashscene
SplashScene.create = function()
{
    if(SplashScene.Extended === undefined)
    {
        SplashScene.Extended = cc.Scene.extend(new SplashScene);
    }
    return new SplashScene.Extended();
};