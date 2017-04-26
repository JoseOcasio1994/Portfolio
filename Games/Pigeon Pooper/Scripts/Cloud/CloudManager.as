package Cloud
{	
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	
	public class CloudManager extends MovieClip
	{
		private var cloudTimer:Timer;
		private var clouds:Array = new Array;
		
		public function CloudManager ()
		{			
			cloudTimer 	= new Timer(5000);				
		}
		
		public function Start ()
		{
			cloudTimer.addEventListener(TimerEvent.TIMER, CreateCloud);
			cloudTimer.start();
			CreateCloud(null);
		}
		
		public function CleanUp ()
		{
			cloudTimer.removeEventListener(TimerEvent.TIMER, CreateCloud);
			cloudTimer.reset();
			cloudTimer.stop();
			for (var i:int = clouds.length - 1; i >= 0; i--)
			{
				clouds[i].CleanUp();
				clouds[i] = null;
				clouds.splice(i, 1);
			}
			clouds = new Array;
		}
		
		public function MainLoop ()
		{
			for (var i:int = 0; i < clouds.length; i++)
			{
				clouds[i].MainLoop();
			}
		}
		
		function CreateCloud(timerEvent:TimerEvent):void
		{
			var randomNumber:Number = Math.floor(Math.random() * 2);
			var cloud:Cloud;
			
			cloud = new Cloud(MainManager.CloudLayer);			
			clouds.push(cloud);
		}
	}
}