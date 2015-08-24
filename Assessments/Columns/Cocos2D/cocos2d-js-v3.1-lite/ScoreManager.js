var Score = {};

Score.scoreValue = 0;
Score.scoreMultiplier = 1;
Score.weather;

//calculates the score from number of blocks matched
Score.addScore = function(matches)
{
    //use the number of blocks matched to increase the score
    Score.scoreValue += (Math.pow(5, matches)) * Score.scoreMultiplier;
};

//displays the score in html on the website
Score.update = function()
{
    //display the score on the website
    document.getElementById("score").innerHTML = Score.scoreValue;  
};

//resets the current score to zero
Score.resetScore = function()
{
    //reset the score and multiplier to 0
    Score.scoreValue = 0;
    Score.scoreMultiplier = 1;
};

//request weather data from web api
Score.getWeather = function()
{
    //request data from the web api
    $.getJSON('http://query.yahooapis.com/v1/public/yql?\q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20%28select%20woeid%20from%20geo.places%281%29%20where%20text%3D%22melbourne%2C%20vic%22%29%20and%20u%3D%22c%22&format=json&callback=',
                {}, function(data, status)
                {
                   if (status === "success")
                   {
                       //convert the temperature to a colour
                       Score.weather = data.query.results.channel.item.condition.temp;
                       Score.numberToColour(Score.weather);
                   }
                });
};

//use a numerical value to determine the background colour
Score.numberToColour = function(value)
{
    //use a numerical value to set the website background
    //the lower the number, the higher the blue value
    //the higher the number, the higher the red value
    if (value < 10)
    {
        document.body.style.background = "#3030b0";
    }
    else if (value < 15)
    {
        document.body.style.background = "#503090";
    }
    else if (value < 20)
    {
        document.body.style.background = "#703070";
    }
    else if(value < 25)
    {
        document.body.style.background = "#903050";
    }
    else if(value < 30)
    {
        document.body.style.background = "#b03030";
    }
    else
    {
        document.body.style.background = "#d03030";
    }
};