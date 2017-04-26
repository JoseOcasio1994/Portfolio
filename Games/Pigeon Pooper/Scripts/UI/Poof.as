package UI
{	
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	public class Poof extends Renderable
	{		
		private var destroyTimer:Timer;
		
		public function Poof(argParentClip:MovieClip)
		{
			destroyTimer = new Timer(400);
			
			super(argParentClip, "Assets/Art/Poof.swf");
		}
		
		protected override function LoadComplete() 
		{
			destroyTimer.addEventListener(TimerEvent.TIMER, Destroy);
			destroyTimer.start();
		}

		private function Destroy(e:TimerEvent):void
		{
			destroyTimer.stop();
			destroyTimer.removeEventListener(TimerEvent.TIMER, Destroy);
			AttachToParent(false);
		}
	}
}