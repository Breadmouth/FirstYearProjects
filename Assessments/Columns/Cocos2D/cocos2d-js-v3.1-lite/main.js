window.addEventListener('load', Run());

//create the scene and schedule it's update
loadScene = function()
{
    Input.init("gameCanvas"/*, this.scheduler*/);
    
    var newScene = SplashScene.create();
    newScene.scheduleUpdate();
    cc.director.runScene(newScene);
};

//code runs on program startup.
//sets the first scene to SplashScene
function Run()
{   
    //vars that will allow tracking of deltaTime
    startFrameMillis = Date.now();
    endFrameMillis = Date.now();
    dt = 0;

    
    cc.game.onStart = function()
    {
        //preload all the resources (textures, sounds...)
        cc.LoaderScene.preload(g_resources, loadScene, this);
    };
    
    
    cc.game.run("gameCanvas");
 
};      