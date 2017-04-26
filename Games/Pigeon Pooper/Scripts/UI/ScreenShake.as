package UI
{	
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	
	public class ScreenShake extends MovieClip
	{
		//Screenshake
		private static var shakeMaxDuration		:Number = 0.11;
		private static var shakeCurDuration		:Number = 0;
		private static var minorMagnitude		:Number = 1.5;
		private static var majorMagnitude		:Number = 3;
		private static var shakeMagnitude		:Number = 1.7;
		private static var shakeEndX			:Number;
		private static var shakeEndY			:Number;
		private static var shakenOff			:Boolean = false;
		private static var shakeCount			:int;
		
		public function ScreenShake ()
		{			
			shakeEndX = MainManager.NonUIRootLayer.x;
			shakeEndY = MainManager.NonUIRootLayer.y;
		}
		
		public static function DoShake (doPause:Boolean)
		{			
			if (doPause)
			{
				shakeMagnitude = majorMagnitude;
				MainManager.QuickPause();
			}
			else
			{
				shakeMagnitude = minorMagnitude;
			}
			shakeCount = 2;
			MakeAShake();
		}
		
		public function MainLoop ()
		{
			if (shakeCount > 0)
			{
				MakeAShake ();
				shakeCount--;
			}
			else
			{
				MainManager.NonUIRootLayer.x = shakeEndX;
				MainManager.NonUIRootLayer.y = shakeEndY;
			}
		}
		
		static function MakeAShake ()
		{
			if (!shakenOff)
			{
				MainManager.NonUIRootLayer.x += Math.random()* shakeMagnitude;
				MainManager.NonUIRootLayer.y += Math.random()* shakeMagnitude;
				shakenOff = true;
			}
			else
			{
				MainManager.NonUIRootLayer.x = shakeEndX;
				MainManager.NonUIRootLayer.y = shakeEndY;
				shakenOff = false;
			}
		}
	}
}