function HSScene()
{
    this.onEnter = function()
    {
        this._super();
        
        HSScene.store = window['localStorage'];
        HSScene.highscores = [];  
        HSScene.highscores[0] = 0;
        HSScene.highscores[1] = 0; 
        HSScene.highscores[2] = 0; 
        HSScene.highscores[3] = 0; 
        HSScene.highscores[4] = 0; 
        
        var size = cc.director.getWinSize();
        
        this.timer = 0;
        
        //load the scores from persistent storage
        HSScene.loadScores();
        //add the newest score to the array of scores
        HSScene.addScore(Score.scoreValue);
        //sort the scores using a bubble sort
        HSScene.sortScores();
        //save the top 5 scores in the highscore array to persistent storage
        HSScene.saveScores();
        
        //draw the scores to the canvas as labels
        title = cc.LabelTTF.create("HIGH SCORES", font, 40);
        highscore1 = cc.LabelTTF.create(HSScene.highscores[0].toString(), font, 20);
        highscore2 = cc.LabelTTF.create(HSScene.highscores[1].toString(), font, 20);
        highscore3 = cc.LabelTTF.create(HSScene.highscores[2].toString(), font, 20);
        highscore4 = cc.LabelTTF.create(HSScene.highscores[3].toString(), font, 20);
        highscore5 = cc.LabelTTF.create(HSScene.highscores[4].toString(), font, 20);
        
        this.addChild(title);
        this.addChild(highscore1);
        this.addChild(highscore2);
        this.addChild(highscore3);
        this.addChild(highscore4);
        this.addChild(highscore5);        
        
        title.setPosition(new cc.Point(size.width / 2, size.height / 2 + 200));
        highscore1.setPosition(new cc.Point(size.width / 2, size.height / 2 + 100));
        highscore2.setPosition(new cc.Point(size.width / 2, size.height / 2 + 50));
        highscore3.setPosition(new cc.Point(size.width / 2, size.height / 2));
        highscore4.setPosition(new cc.Point(size.width / 2, size.height / 2 - 50));
        highscore5.setPosition(new cc.Point(size.width / 2, size.height / 2 - 100));
        
        Score.resetScore();
        
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
        
        if (this.timer > 5)
        {
            var newScene = MenuScene.create();
            newScene.scheduleUpdate();
            cc.director.runScene(newScene);
        }
        
    };
}

//simplifies creating a new HSScene
HSScene.create = function()
{
    if(HSScene.Extended === undefined)
    {
        HSScene.Extended = cc.Scene.extend(new HSScene);
    }
    return new HSScene.Extended();
};

//loads scors from persistent storage
HSScene.loadScores = function()
{
    //load highscore1 from persistent storage
    HSScene.highscores[0] = JSON.parse(HSScene.store.getItem("score1"));
    //load highscore2 from persistent storage
    HSScene.highscores[1] = JSON.parse(HSScene.store.getItem("score2"));
    //etc
    HSScene.highscores[2] = JSON.parse(HSScene.store.getItem("score3"));
    HSScene.highscores[3] = JSON.parse(HSScene.store.getItem("score4"));
    HSScene.highscores[4] = JSON.parse(HSScene.store.getItem("score5"));
};

//bubble sort
HSScene.sortScores = function()
{
    //run sort algorithm enough times to ensure all scores have been sorted correctly
    for (i = 0; i < HSScene.highscores.length - 1; ++i)
    {
        //for every score from back of array to the front
        for (j = HSScene.highscores.length - 1; j > 0; --j)
        {
            //if the current score is greater than the next score..
            if (HSScene.highscores[j] > HSScene.highscores[j - 1] || 
               (HSScene.highscores[j - 1] === null && HSScene.highscores[j] !== null))
            {
                //swap the scores
                temp = HSScene.highscores[j];
                HSScene.highscores[j] = HSScene.highscores[j - 1];
                HSScene.highscores[j - 1] = temp;
            }
        }
    }
};

//saves scores to persistent storage
HSScene.saveScores = function()
{
    //if the first highscore is not null or undefined
    if (HSScene.highscores[0] !== null && HSScene.highscores[0] !== undefined)
    {
        //save it to persistent storage
        HSScene.store.setItem("score1", JSON.stringify(HSScene.highscores[0]));
        if (HSScene.highscores[1] !== null && HSScene.highscores[1] !== undefined)
        {
            HSScene.store.setItem("score2", JSON.stringify(HSScene.highscores[1]));
            if (HSScene.highscores[2] !== null && HSScene.highscores[2] !== undefined)
            {
                HSScene.store.setItem("score3", JSON.stringify(HSScene.highscores[2]));
                if (HSScene.highscores[3] !== null && HSScene.highscores[3] !== undefined)
                {
                    HSScene.store.setItem("score4", JSON.stringify(HSScene.highscores[3]));
                    if (HSScene.highscores[4] !== null && HSScene.highscores[4] !== undefined)
                    {
                        HSScene.store.setItem("score5", JSON.stringify(HSScene.highscores[4]));
                    }
                    else
                    {
                       HSScene.store.setItem("score5", '0'); 
                    }
                }
                else 
                {
                    HSScene.store.setItem("score4", '0');
                    HSScene.store.setItem("score5", '0');
                }
            }
            else 
            {
                HSScene.store.setItem("score3", '0');
                HSScene.store.setItem("score4", '0');
                HSScene.store.setItem("score5", '0');
            }
        }
        else
        {
            HSScene.store.setItem("score2", '0');
            HSScene.store.setItem("score3", '0');
            HSScene.store.setItem("score4", '0');
            HSScene.store.setItem("score5", '0'); 
        }
    }
    else
    {
        //otherwise save all remaining scores to persistent as 0 
        HSScene.store.setItem("score1", '0');
        HSScene.store.setItem("score2", '0');
        HSScene.store.setItem("score3", '0');
        HSScene.store.setItem("score4", '0');
        HSScene.store.setItem("score5", '0');
    }
};

//adds a new score to the highscores array
HSScene.addScore = function(score)
{
    HSScene.highscores.push(score);
};